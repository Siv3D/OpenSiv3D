//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/TCPServer.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/ConcurrentTask.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/Logger.hpp>

# define _WINSOCK_DEPRECATED_NO_WARNINGS
# ifndef _WIN32_WINNT
#	define	_WIN32_WINNT _WIN32_WINNT_WIN8
# endif
# ifndef NTDDI_VERSION
#	define	NTDDI_VERSION NTDDI_WIN8
# endif
# define  ASIO_STANDALONE
# include "../../ThirdParty/asio/asio.hpp"


namespace s3d
{
	namespace detail
	{
		class Session
		{
		private:

			asio::ip::tcp::socket m_socket;

			SessionID m_id = 0;

			bool m_isActive = false;

			asio::streambuf m_buffer;

			// 受信	
			static constexpr size_t maxBufferSize = 32 * 1024 * 1024;

			std::mutex m_mutexReceivedBuffer;

			Array<uint8> m_receivedBuffer;


			// 送信
			std::mutex m_mutexSendingBuffer;

			Array<Array<uint8>> m_sendingBuffer;

			bool m_isSending = false;

			void send_internal()
			{
				m_isSending = true;

				asio::async_write(m_socket, asio::buffer(m_sendingBuffer.front().data(), m_sendingBuffer.front().size()),
					std::bind(&Session::onSend, this, std::placeholders::_1, std::placeholders::_2));
			}

		public:

			Session(asio::io_service& io_service)
				: m_socket(io_service)
			{

			}

			~Session()
			{
				close();
			}

			void close()
			{
				if (m_id == 0)
				{
					return;
				}

				m_socket.close();

				if (!m_isSending)
				{
					std::lock_guard<std::mutex> lock(m_mutexSendingBuffer);
					m_sendingBuffer.clear();
				}

				{
					std::lock_guard<std::mutex> lock(m_mutexReceivedBuffer);
					m_receivedBuffer.clear();
					m_buffer.consume(m_buffer.size());
				}

				m_isSending = false;
				m_isActive = false;

				if (m_id)
				{
					LOG_DEBUG(U"Session [{}] closed"_fmt(m_id));
				}

				m_id = 0;
			}

			void init(const SessionID id)
			{
				m_id = id;

				m_isActive = true;

				LOG_DEBUG(U"Session [{}] created"_fmt(id));
			}

			asio::ip::tcp::socket& socket()
			{
				return m_socket;
			}

			bool isActive() const
			{
				return m_isActive;
			}

			size_t available()
			{
				std::lock_guard<std::mutex> lock(m_mutexReceivedBuffer);

				return m_receivedBuffer.size();
			}

			void startReceive()
			{
				asio::async_read(m_socket, m_buffer, asio::transfer_at_least(1),
					std::bind(&Session::onReceive, this, std::placeholders::_1, std::placeholders::_2));
			}

			void onReceive(const asio::error_code& error, size_t)
			{
				if (error)
				{
					if (error != asio::error::eof)
					{
						LOG_FAIL(U"TCPServer: onReceive failed: {}"_fmt(Unicode::Widen(error.message())));
					}
					else
					{
						LOG_DEBUG(U"TCPServer: EOF");
					}

					m_buffer.consume(m_buffer.size());

					close();

					return;
				}

				const uint8* data = asio::buffer_cast<const uint8*>(m_buffer.data());
				const size_t size = m_buffer.size();

				{
					std::lock_guard<std::mutex> lock(m_mutexReceivedBuffer);

					if (m_receivedBuffer.size() + size > maxBufferSize)
					{
						LOG_FAIL(U"TCPServer: onReceive exceeded the maximum buffer size");

						m_buffer.consume(m_buffer.size());

						close();

						return;
					}

					m_receivedBuffer.insert(m_receivedBuffer.end(), data, data + size);
				}

				m_buffer.consume(m_buffer.size());

				startReceive();
			}

			void onSend(const asio::error_code& error, size_t)
			{
				m_isSending = false;

				if (!m_isActive)
				{
					std::lock_guard<std::mutex> lock(m_mutexSendingBuffer);
					m_sendingBuffer.clear();
				}

				if (error)
				{
					LOG_FAIL(U"TCPServer: send failed: {}"_fmt(Unicode::Widen(error.message())));

					return;
				}

				{
					std::lock_guard<std::mutex> lock(m_mutexSendingBuffer);

					if (!m_sendingBuffer.empty())
					{
						m_sendingBuffer.erase(m_sendingBuffer.begin());
					}

					if (!m_sendingBuffer.empty())
					{
						send_internal();
					}
				}
			}

			bool skip(const size_t size)
			{
				if (!m_isActive)
				{
					return false;
				}

				std::lock_guard<std::mutex> lock(m_mutexReceivedBuffer);

				if (size > m_receivedBuffer.size())
				{
					return false;
				}

				m_receivedBuffer.erase(m_receivedBuffer.begin(), m_receivedBuffer.begin() + size);

				return true;
			}

			bool lookahead(void* dst, const size_t size)
			{
				if (!m_isActive)
				{
					return false;
				}

				std::lock_guard<std::mutex> lock(m_mutexReceivedBuffer);

				if (m_receivedBuffer.size() < size)
				{
					return false;
				}

				::memcpy(dst, m_receivedBuffer.data(), size);

				return true;
			}

			bool read(void* dst, const size_t size)
			{
				if (!m_isActive)
				{
					return false;
				}

				std::lock_guard<std::mutex> lock(m_mutexReceivedBuffer);

				if (m_receivedBuffer.size() < size)
				{
					return false;
				}

				::memcpy(dst, m_receivedBuffer.data(), size);

				m_receivedBuffer.erase(m_receivedBuffer.begin(), m_receivedBuffer.begin() + size);

				return true;
			}

			bool send(const void* data, const size_t size)
			{
				if (!m_isActive)
				{
					return false;
				}

				std::lock_guard<std::mutex> lock(m_mutexSendingBuffer);

				m_sendingBuffer.emplace_back(static_cast<const unsigned char*>(data), static_cast<const unsigned char*>(data) + size);

				if (!m_isSending)
				{
					send_internal();
				}

				return true;
			}
		};
	}

	class TCPServer::CTCPServer
	{
	private:

		std::shared_ptr<asio::io_service> m_io_service;

		std::unique_ptr<asio::io_service::work> m_work;

		std::unique_ptr<asio::ip::tcp::acceptor> m_acceptor;

		std::future<void> m_io_service_thread;

		Array<std::pair<SessionID, std::shared_ptr<detail::Session>>> m_sessions;

		std::atomic<SessionID> m_currentSessionID = 0;

		uint16 m_port = 0;

		bool m_accepting = false;

		bool m_allowMulti = false;

		void onAccept(const asio::error_code& error, const std::shared_ptr<detail::Session>& session);

		void updateSession();

	public:

		CTCPServer();

		~CTCPServer();

		void startAccept(uint16 port);

		void startAcceptMulti(uint16 port);

		void cancelAccept();

		bool isAccepting() const;

		void disconnect();

		bool hasSession();

		bool hasSession(SessionID id);

		size_t num_sessions();

		Array<SessionID> getSessionIDs();

		uint16 port() const;

		size_t available(const Optional<SessionID>& id);

		bool skip(size_t size, const Optional<SessionID>& id);

		bool lookahead(void* dst, size_t size, const Optional<SessionID>& id) const;

		bool read(void* dst, size_t size, const Optional<SessionID>& id);

		bool send(const void* data, size_t size, const Optional<SessionID>& id);
	};
}
