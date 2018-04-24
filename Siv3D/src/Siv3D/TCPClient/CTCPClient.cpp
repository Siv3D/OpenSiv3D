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

# include <Siv3D/IPv4.hpp>
# include "CTCPClient.hpp"

namespace s3d
{
	TCPClient::CTCPClient::CTCPClient()
	//	: m_io_service(std::make_shared<asio::io_service>())
	{

	}

	TCPClient::CTCPClient::~CTCPClient()
	{
		disconnect();
	}

	bool TCPClient::CTCPClient::connect(const IPv4& ip, uint16 port)
	{
		if (!m_work)
		{
			m_io_service = std::make_shared<asio::io_service>();

			m_work = std::make_unique<asio::io_service::work>(*m_io_service);

			m_io_service_thread = std::async([=] { m_io_service->run(); });
		}

		if (m_isConnected)
		{
			return false;
		}

		if (m_waitingConnection)
		{
			return false;
		}

		m_session = std::make_shared<detail::ClientSession>(*m_io_service);

		m_waitingConnection = true;

		LOG_TEST(U"async_connect");

		m_session->socket().async_connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(ip.toStr().narrow()), port),
			std::bind(&CTCPClient::onConnect, this, std::placeholders::_1));

		return true;
	}

	void TCPClient::CTCPClient::cancelConnect()
	{
		if (!m_session || !m_waitingConnection)
		{
			return;
		}

		m_session->socket().shutdown(asio::socket_base::shutdown_type::shutdown_both);

		m_session->socket().close();

		m_waitingConnection = false;
	}

	bool TCPClient::CTCPClient::isConnected() const
	{
		return m_isConnected;
	}

	void TCPClient::CTCPClient::disconnect()
	{
		if (!m_session)
		{
			return;
		}

		cancelConnect();

		m_session->close();

		m_session.reset();

		m_waitingConnection = false;
		
		m_error = NetworkError::OK;
		
		m_isConnected = false;

		if (m_work)
		{
			m_work.reset();

			m_io_service->stop();

			m_io_service_thread.wait();

			m_io_service->restart();

			m_io_service.reset();
		}
	}

	uint16 TCPClient::CTCPClient::port() const
	{
		if (m_session && m_isConnected)
		{
			return m_session->socket().remote_endpoint().port();
		}
		else
		{
			return 0;
		}
	}

	bool TCPClient::CTCPClient::hasError() const
	{
		return getError() != NetworkError::OK;
	}

	NetworkError TCPClient::CTCPClient::getError() const
	{
		if (!m_session || (m_error != NetworkError::OK))
		{
			return m_error;
		}

		return m_session->getError();
	}

	void TCPClient::CTCPClient::onConnect(const asio::error_code& error)
	{
		if (error)
		{
			if (error == asio::error::connection_refused)
			{
				LOG_FAIL(U"TCPClient: Connection refused: [error: {}] {}"_fmt(error.value(), Unicode::Widen(error.message())));

				m_error = NetworkError::ConnectionRefused;
			}
			else
			{
				LOG_FAIL(U"TCPClient: connect failed: {}"_fmt(Unicode::Widen(error.message())));

				m_error = NetworkError::Error;
			}

			cancelConnect();

			return;
		}

		LOG_INFO(U"TCPClient: accepted: remote {}<{}> local {}<{}>"_fmt(
			Unicode::WidenAscii(m_session->socket().remote_endpoint().address().to_string()),
			m_session->socket().remote_endpoint().port(),
			Unicode::WidenAscii(m_session->socket().local_endpoint().address().to_string()),
			m_session->socket().local_endpoint().port()));

		m_waitingConnection = false;

		m_isConnected = true;

		m_session->init();

		m_session->startReceive();
	}

	size_t TCPClient::CTCPClient::available()
	{
		if (!m_session)
		{
			return 0;
		}

		return m_session->available();
	}

	bool TCPClient::CTCPClient::skip(const size_t size)
	{
		if (!m_session)
		{
			return false;
		}

		return m_session->skip(size);
	}

	bool TCPClient::CTCPClient::lookahead(void* dst, const size_t size) const
	{
		if (!m_session)
		{
			return false;
		}

		return m_session->lookahead(dst, size);
	}

	bool TCPClient::CTCPClient::read(void* dst, const size_t size)
	{
		if (!m_session)
		{
			return false;
		}

		return m_session->read(dst, size);
	}

	bool TCPClient::CTCPClient::send(const void* data, const size_t size)
	{
		if (!m_session)
		{
			return false;
		}

		return m_session->send(data, size);
	}
}
