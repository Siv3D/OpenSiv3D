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
# include <Siv3D/TCPClient.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/ConcurrentTask.hpp>
# include <Siv3D/Network.hpp>
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
		class ClientSession : public std::enable_shared_from_this<ClientSession>
		{
		private:

			asio::ip::tcp::socket m_socket;

			NetworkError m_error = NetworkError::OK;

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
					std::bind(&ClientSession::onSend, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
			}

		public:

			ClientSession(asio::io_service& io_service)
				: m_socket(io_service)
			{

			}

			asio::ip::tcp::socket& socket()
			{
				return m_socket;
			}

			void init()
			{
				m_isActive = true;

				m_error = NetworkError::OK;
			}

			void close()
			{
				if (!m_isActive)
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

				if (m_isActive)
				{
					LOG_DEBUG(U"Session closed");
				}

				m_isSending = false;
				m_isActive = false;
			}

			bool isActive() const
			{
				return m_isActive;
			}

			NetworkError getError() const
			{
				return m_error;
			}

			size_t available()
			{
				std::lock_guard<std::mutex> lock(m_mutexReceivedBuffer);

				return m_receivedBuffer.size();
			}

			void startReceive()
			{
				asio::async_read(m_socket, m_buffer, asio::transfer_at_least(1),
					std::bind(&ClientSession::onReceive, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
			}

			void onReceive(const asio::error_code& error, size_t, const std::shared_ptr<ClientSession>&)
			{
				if (error)
				{
					if (error != asio::error::eof)
					{
						LOG_FAIL(U"TCPClient: onReceive failed: {}"_fmt(Unicode::Widen(error.message())));

						m_error = NetworkError::Error;
					}
					else
					{
						LOG_INFO(U"TCPClient: EOF");

						m_error = NetworkError::EoF;
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
						LOG_FAIL(U"TCPClient: onReceive exceeded the maximum buffer size");

						m_error = NetworkError::NoBufferSpaceAvailable;

						m_buffer.consume(m_buffer.size());

						close();

						return;
					}

					m_receivedBuffer.insert(m_receivedBuffer.end(), data, data + size);
				}

				m_buffer.consume(m_buffer.size());

				startReceive();
			}

			void onSend(const asio::error_code& error, size_t, const std::shared_ptr<ClientSession>&)
			{
				m_isSending = false;

				if (!m_isActive)
				{
					std::lock_guard<std::mutex> lock(m_mutexSendingBuffer);
					m_sendingBuffer.clear();
				}

				if (error)
				{
					LOG_FAIL(U"TCPClient: send failed: {}"_fmt(Unicode::Widen(error.message())));

					m_error = NetworkError::Error;

					close();

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

	class TCPClient::CTCPClient
	{
	private:

		std::shared_ptr<asio::io_service> m_io_service;

		std::unique_ptr<asio::io_service::work> m_work;

		std::unique_ptr<asio::ip::tcp::acceptor> m_acceptor;

		std::future<void> m_io_service_thread;

		std::shared_ptr<detail::ClientSession> m_session;

		NetworkError m_error = NetworkError::OK;

		bool m_isConnected = false;

		bool m_waitingConnection = false;

		void onConnect(const asio::error_code& error);

	public:

		CTCPClient();

		~CTCPClient();

		bool connect(const IPv4& ip, uint16 port);

		void cancelConnect();

		bool isConnected() const;

		void disconnect();

		uint16 port() const;

		bool hasError() const;

		NetworkError getError() const;

		size_t available();

		bool skip(size_t size);

		bool lookahead(void* dst, size_t size) const;

		bool read(void* dst, size_t size);

		bool send(const void* data, size_t size);
	};
}
