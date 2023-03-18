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
# include <Siv3D/TCPClient.hpp>
# include <Siv3D/AsyncTask.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/PseudoThread/PseudoThread.hpp>

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
		class ClientSession : public std::enable_shared_from_this<ClientSession>
		{
		private:

			asio::ip::tcp::socket m_socket;

			TCPError m_error = TCPError::OK;

			bool m_isActive = false;

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

				m_error = TCPError::OK;
			}

			void close()
			{
				if (!m_isActive)
				{
					return;
				}

				if (m_error != TCPError::EoF)
				{
					m_socket.shutdown(asio::socket_base::shutdown_type::shutdown_both);
				}

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

				if (m_isActive)
				{
					LOG_TRACE(U"Session closed");
				}

				m_isSending = false;
				m_isActive = false;
			}

			bool isActive() const
			{
				return m_isActive;
			}

			TCPError getError() const
			{
				return m_error;
			}

			size_t available()
			{
				std::lock_guard lock{ m_mutexReceivedBuffer };

				return m_receivedBuffer.size();
			}

			void startReceive()
			{
				asio::async_read(m_socket, m_streamBuffer, asio::transfer_at_least(1),
					std::bind(&ClientSession::onReceive, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
			}

			void onReceive(const asio::error_code& error, size_t, const std::shared_ptr<ClientSession>&)
			{
				if (error)
				{
					if (error != asio::error::eof)
					{
						LOG_FAIL(U"TCPClient: onReceive failed: {}"_fmt(Unicode::Widen(error.message())));

						m_error = TCPError::Error;
					}
					else
					{
						LOG_INFO(U"TCPClient: EOF");

						m_error = TCPError::EoF;
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
						LOG_FAIL(U"TCPClient: onReceive exceeded the maximum buffer size");

						m_error = TCPError::NoBufferSpaceAvailable;

						m_streamBuffer.consume(m_streamBuffer.size());

						close();

						return;
					}

					m_receivedBuffer.insert(m_receivedBuffer.end(), data, data + size);
				}

				m_streamBuffer.consume(m_streamBuffer.size());

				startReceive();
			}

			void onSend(const asio::error_code& error, size_t, const std::shared_ptr<ClientSession>&)
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
					LOG_FAIL(U"TCPClient: send failed: {}"_fmt(Unicode::Widen(error.message())));

					m_error = TCPError::Error;

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
					std::lock_guard lock{ m_mutexReceivedBuffer };

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

				if (size == 0)
				{
					return true;
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

	class TCPClient::TCPClientDetail
	{
	private:

		std::shared_ptr<asio::io_service> m_io_service;

		std::unique_ptr<asio::io_service::work> m_work;

		std::unique_ptr<asio::ip::tcp::acceptor> m_acceptor;

		PseudoThread m_io_service_thread;

		std::shared_ptr<detail::ClientSession> m_session;

		TCPError m_error = TCPError::OK;

		bool m_isConnected = false;

		bool m_waitingConnection = false;

		void onConnect(const asio::error_code& error);

		bool onRun(); 

	public:

		TCPClientDetail();

		~TCPClientDetail();

		bool connect(const IPv4Address& ip, uint16 port);

		void cancelConnect();

		bool isConnected() const;

		void disconnect();

		uint16 port() const;

		bool hasError() const;

		TCPError getError() const;

		size_t available();

		bool skip(size_t size);

		bool lookahead(void* dst, size_t size) const;

		bool read(void* dst, size_t size);

		bool send(const void* data, size_t size);
	};
}
