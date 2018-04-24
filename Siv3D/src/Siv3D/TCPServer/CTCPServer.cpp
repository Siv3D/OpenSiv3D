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

# include "CTCPServer.hpp"

namespace s3d
{
	TCPServer::CTCPServer::CTCPServer()
		: m_io_service(std::make_shared<asio::io_service>())
	{

	}

	TCPServer::CTCPServer::~CTCPServer()
	{
		disconnect();
	}

	void TCPServer::CTCPServer::startAccept(const uint16 port)
	{
		if (m_accepting)
		{
			cancelAccept();
		}

		m_accepting = true;

		m_allowMulti = false;

		m_port = port;

		if (!m_work)
		{
			m_io_service->restart();

			m_work = std::make_unique<asio::io_service::work>(*m_io_service);

			m_io_service_thread = std::async([=] { m_io_service->run(); });
		}

		m_acceptor = std::make_unique<asio::ip::tcp::acceptor>(*m_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

		std::shared_ptr<detail::Session> newSession = std::make_shared<detail::Session>(*m_io_service);

		m_acceptor->async_accept(newSession->socket(),
			std::bind(&CTCPServer::onAccept, this, std::placeholders::_1, newSession));
	}

	void TCPServer::CTCPServer::startAcceptMulti(const uint16 port)
	{
		if (m_accepting)
		{
			cancelAccept();
		}

		m_accepting = true;

		m_allowMulti = true;

		m_port = port;

		if (!m_work)
		{
			m_io_service->restart();

			m_work = std::make_unique<asio::io_service::work>(*m_io_service);

			m_io_service_thread = std::async([=] { m_io_service->run(); });
		}

		m_acceptor = std::make_unique<asio::ip::tcp::acceptor>(*m_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

		std::shared_ptr<detail::Session> newSession = std::make_shared<detail::Session>(*m_io_service);

		m_acceptor->async_accept(newSession->socket(),
			std::bind(&CTCPServer::onAccept, this, std::placeholders::_1, newSession));
	}

	void TCPServer::CTCPServer::cancelAccept()
	{
		m_accepting = false;

		if (m_acceptor)
		{
			m_acceptor->close();
		}
	}

	bool TCPServer::CTCPServer::isAccepting() const
	{
		return m_accepting;
	}

	void TCPServer::CTCPServer::disconnect()
	{
		cancelAccept();

		for (auto& session : m_sessions)
		{
			session.second->close();
		}

		m_sessions.clear();

		if (m_work)
		{
			m_work.reset();

			m_io_service_thread.wait();
		}
	}

	bool TCPServer::CTCPServer::hasSession()
	{
		updateSession();

		return m_sessions.any([](const auto& session) { return session.second->isActive(); });
	}

	bool TCPServer::CTCPServer::hasSession(const SessionID id)
	{
		updateSession();

		return m_sessions.includes_if([=](const auto& session) { return session.first == id; });
	}

	size_t TCPServer::CTCPServer::num_sessions()
	{
		updateSession();

		return m_sessions.count_if([](const auto& session) { return session.second->isActive(); });
	}

	Array<SessionID> TCPServer::CTCPServer::getSessionIDs()
	{
		updateSession();

		return m_sessions.map([](const auto& session) { return session.first; });
	}

	uint16 TCPServer::CTCPServer::port() const
	{
		return m_port;
	}

	size_t TCPServer::CTCPServer::available(const Optional<SessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return 0;
		}

		const SessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->available();
			}
		}

		return 0;
	}

	bool TCPServer::CTCPServer::skip(const size_t size, const Optional<SessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const SessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->skip(size);
			}
		}

		return false;
	}

	bool TCPServer::CTCPServer::lookahead(void* dst, const size_t size, const Optional<SessionID>& id) const
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const SessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->lookahead(dst, size);
			}
		}

		return false;
	}

	bool TCPServer::CTCPServer::read(void* dst, const size_t size, const Optional<SessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const SessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->read(dst, size);
			}
		}

		return false;
	}

	bool TCPServer::CTCPServer::send(const void* data, const size_t size, const Optional<SessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const SessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->send(data, size);
			}
		}

		return false;
	}

	void TCPServer::CTCPServer::onAccept(const asio::error_code& error, const std::shared_ptr<detail::Session>& session)
	{
		updateSession();

		if (!m_accepting)
		{
			return;
		}

		if (error)
		{
			LOG_FAIL(U"TCPServer: accept failed: {}"_fmt(Unicode::Widen(error.message())));

			cancelAccept();

			return;
		}

		const SessionID id = ++m_currentSessionID;

		session->init(id);

		LOG_INFO(U"TCPServer: accepted: remote {}<{}> local {}<{}>"_fmt(
			Unicode::WidenAscii(session->socket().remote_endpoint().address().to_string()),
			session->socket().remote_endpoint().port(),
			Unicode::WidenAscii(session->socket().local_endpoint().address().to_string()),
			session->socket().local_endpoint().port()));

		m_sessions.push_back({ id, session });

		LOG_DEBUG(U"TCPServer session [{}] created"_fmt(id));

		m_sessions.back().second->startReceive();

		if (m_allowMulti)
		{
			std::shared_ptr<detail::Session> newSession = std::make_shared<detail::Session>(*m_io_service);

			m_acceptor->async_accept(newSession->socket(),
				std::bind(&CTCPServer::onAccept, this, std::placeholders::_1, newSession));
		}
		else
		{
			cancelAccept();
		}
	}

	void TCPServer::CTCPServer::updateSession()
	{
		m_sessions.remove_if([](const auto& session) { return !session.second->isActive(); });
	}
}
