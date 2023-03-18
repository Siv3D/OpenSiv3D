//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/TCPServer.hpp>
# include <Siv3D/AsyncTask.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>

# define _WINSOCK_DEPRECATED_NO_WARNINGS
# ifndef _WIN32_WINNT
#	define	_WIN32_WINNT _WIN32_WINNT_WIN8
# endif
# ifndef NTDDI_VERSION
#	define	NTDDI_VERSION NTDDI_WIN8
# endif
# define  ASIO_STANDALONE
# include <asio/asio.hpp>

namespace s3d
{
	namespace detail
	{
		class ServerSession : public std::enable_shared_from_this<ServerSession>
		{
		private:

			asio::ip::tcp::socket m_socket;

			TCPSessionID m_id = 0;

			bool m_isActive = false;

			bool m_eof = false;

			asio::streambuf m_streamBuffer;

			// 受信	
			static constexpr size_t maxBufferSize = 32 * 1024 * 1024;

			std::mutex m_mutexReceivedBuffer;

			Array<Byte> m_receivedBuffer;


			// 送信
			std::mutex m_mutexSendingBuffer;

			Array<Array<Byte>> m_sendingBuffer;

			bool m_isSending = false;


			void send_internal()
			{
				m_isSending = true;

				asio::async_write(m_socket, asio::buffer(m_sendingBuffer.front().data(), m_sendingBuffer.front().size()),
					std::bind(&ServerSession::onSend, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
			}

		public:

			ServerSession(asio::io_service& io_service)
				: m_socket(io_service)
			{

			}

			~ServerSession()
			{
				close();
			}

			void close()
			{
				if (m_id == 0)
				{
					return;
				}

				//if (m_eof)
				//{
				//	m_socket.shutdown(asio::socket_base::shutdown_type::shutdown_both);
				//}

				m_socket.close();

				if (!m_isSending)
				{
					std::lock_guard lock{ m_mutexSendingBuffer };
					m_sendingBuffer.clear();
				}

				{
					std::lock_guard lock{ m_mutexReceivedBuffer };
					m_receivedBuffer.clear();
					m_streamBuffer.consume(m_streamBuffer.size());
				}

				m_isSending = false;
				m_isActive = false;
				m_eof = false;

				if (m_id)
				{
					LOG_TRACE(U"Session [{}] closed"_fmt(m_id));
				}

				m_id = 0;
			}

			void init(const TCPSessionID id)
			{
				m_id = id;

				m_isActive = true;

				LOG_TRACE(U"Session [{}] created"_fmt(id));
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
				std::lock_guard lock{ m_mutexReceivedBuffer };

				return m_receivedBuffer.size();
			}

			void startReceive()
			{
				asio::async_read(m_socket, m_streamBuffer, asio::transfer_at_least(1),
					std::bind(&ServerSession::onReceive, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
			}

			void onReceive(const asio::error_code& error, size_t, const std::shared_ptr<ServerSession>&)
			{
				if (error)
				{
					if (error != asio::error::eof)
					{
						LOG_FAIL(U"TCPServer: onReceive failed: {}"_fmt(Unicode::Widen(error.message())));
					}
					else
					{
						LOG_INFO(U"TCPServer: EOF");

						m_eof = true;
					}

					m_streamBuffer.consume(m_streamBuffer.size());

					close();

					return;
				}

				const Byte* data = asio::buffer_cast<const Byte*>(m_streamBuffer.data());
				const size_t size = m_streamBuffer.size();

				{
					std::lock_guard lock{ m_mutexReceivedBuffer };

					if (m_receivedBuffer.size() + size > maxBufferSize)
					{
						LOG_FAIL(U"TCPServer: onReceive exceeded the maximum buffer size");

						m_streamBuffer.consume(m_streamBuffer.size());

						close();

						return;
					}

					m_receivedBuffer.insert(m_receivedBuffer.end(), data, data + size);
				}

				m_streamBuffer.consume(m_streamBuffer.size());

				startReceive();
			}

			void onSend(const asio::error_code& error, size_t, const std::shared_ptr<ServerSession>&)
			{
				m_isSending = false;

				if (!m_isActive)
				{
					std::lock_guard lock{ m_mutexSendingBuffer };
					m_sendingBuffer.clear();
					return;
				}

				if (error)
				{
					LOG_FAIL(U"TCPServer: send failed: {}"_fmt(Unicode::Widen(error.message())));

					close();

					return;
				}

				{
					std::lock_guard lock{ m_mutexSendingBuffer };

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

				if (size == 0)
				{
					return true;
				}

				{
					std::lock_guard lock{ m_mutexReceivedBuffer };

					if (size > m_receivedBuffer.size())
					{
						return false;
					}

					m_receivedBuffer.pop_front_N(size);
				}

				return true;
			}

			bool lookahead(void* dst, const size_t size)
			{
				if (!m_isActive)
				{
					return false;
				}

				if (size == 0)
				{
					return true;
				}

				{
					std::lock_guard lock{ m_mutexReceivedBuffer };

					if (m_receivedBuffer.size() < size)
					{
						return false;
					}

					std::memcpy(dst, m_receivedBuffer.data(), size);
				}

				return true;
			}

			bool read(void* dst, const size_t size)
			{
				if (!m_isActive)
				{
					return false;
				}

				if (size == 0)
				{
					return true;
				}

				{
					std::lock_guard<std::mutex> lock{ m_mutexReceivedBuffer };

					if (m_receivedBuffer.size() < size)
					{
						return false;
					}

					std::memcpy(dst, m_receivedBuffer.data(), size);

					m_receivedBuffer.pop_front_N(size);
				}

				return true;
			}

			bool send(const void* data, const size_t size)
			{
				if (!m_isActive)
				{
					return false;
				}

				{
					std::lock_guard lock{ m_mutexSendingBuffer };

					m_sendingBuffer.emplace_back(static_cast<const Byte*>(data), static_cast<const Byte*>(data) + size);

					if (!m_isSending)
					{
						send_internal();
					}
				}

				return true;
			}
		};
	}

	class TCPServer::TCPServerDetail
	{
	private:

		std::shared_ptr<asio::io_service> m_io_service;

		std::unique_ptr<asio::io_service::work> m_work;

		std::unique_ptr<asio::ip::tcp::acceptor> m_acceptor;

		AsyncTask<void> m_io_service_thread;

		Array<std::pair<TCPSessionID, std::shared_ptr<detail::ServerSession>>> m_sessions;

		std::atomic<TCPSessionID> m_currentTCPSessionID = 0;

		uint16 m_port = 0;

		bool m_accepting = false;

		bool m_allowMulti = false;

		void onAccept(const asio::error_code& error, const std::shared_ptr<detail::ServerSession>& session);

		void updateSession();

	public:

		TCPServerDetail();

		~TCPServerDetail();

		void startAccept(uint16 port);

		void startAcceptMulti(uint16 port);

		void cancelAccept();

		bool isAccepting() const;

		void disconnect();

		bool hasSession();

		bool hasSession(TCPSessionID id);

		size_t num_sessions();

		Array<TCPSessionID> getSessionIDs();

		uint16 port() const;

		size_t available(const Optional<TCPSessionID>& id);

		bool skip(size_t size, const Optional<TCPSessionID>& id);

		bool lookahead(void* dst, size_t size, const Optional<TCPSessionID>& id) const;

		bool read(void* dst, size_t size, const Optional<TCPSessionID>& id);

		bool send(const void* data, size_t size, const Optional<TCPSessionID>& id);
	};
}
