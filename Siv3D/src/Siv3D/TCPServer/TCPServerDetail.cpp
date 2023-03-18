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

# include "TCPServerDetail.hpp"

namespace s3d
{
	TCPServer::TCPServerDetail::TCPServerDetail()
		: m_io_service(std::make_shared<asio::io_service>())
	{

	}

	TCPServer::TCPServerDetail::~TCPServerDetail()
	{
		disconnect();
	}

	void TCPServer::TCPServerDetail::startAccept(const uint16 port)
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
			m_work = std::make_unique<asio::io_service::work>(*m_io_service);

			m_io_service_thread = Async([this] { m_io_service->run(); });
		}

		m_acceptor = std::make_unique<asio::ip::tcp::acceptor>(*m_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

		std::shared_ptr<detail::ServerSession> newSession = std::make_shared<detail::ServerSession>(*m_io_service);

		m_acceptor->async_accept(newSession->socket(),
			std::bind(&TCPServerDetail::onAccept, this, std::placeholders::_1, newSession));
	}

	void TCPServer::TCPServerDetail::startAcceptMulti(const uint16 port)
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
			m_work = std::make_unique<asio::io_service::work>(*m_io_service);

			m_io_service_thread = Async([this] { m_io_service->run(); });
		}

		m_acceptor = std::make_unique<asio::ip::tcp::acceptor>(*m_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

		std::shared_ptr<detail::ServerSession> newSession = std::make_shared<detail::ServerSession>(*m_io_service);

		m_acceptor->async_accept(newSession->socket(),
			std::bind(&TCPServerDetail::onAccept, this, std::placeholders::_1, newSession));
	}

	void TCPServer::TCPServerDetail::cancelAccept()
	{
		m_accepting = false;

		if (m_acceptor)
		{
			m_acceptor->close();
		}
	}

	bool TCPServer::TCPServerDetail::isAccepting() const
	{
		return m_accepting;
	}

	void TCPServer::TCPServerDetail::disconnect()
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

			m_io_service->stop();

			m_io_service_thread.wait();

			m_io_service->restart();
		}
	}

	bool TCPServer::TCPServerDetail::hasSession()
	{
		updateSession();

		return m_sessions.any([](const auto& session) { return session.second->isActive(); });
	}

	bool TCPServer::TCPServerDetail::hasSession(const TCPSessionID id)
	{
		updateSession();

		return m_sessions.contains_if([=](const auto& session) { return session.first == id; });
	}

	size_t TCPServer::TCPServerDetail::num_sessions()
	{
		updateSession();

		return m_sessions.count_if([](const auto& session) { return session.second->isActive(); });
	}

	Array<TCPSessionID> TCPServer::TCPServerDetail::getSessionIDs()
	{
		updateSession();

		return m_sessions.map([](const auto& session) { return session.first; });
	}

	uint16 TCPServer::TCPServerDetail::port() const
	{
		return m_port;
	}

	size_t TCPServer::TCPServerDetail::available(const Optional<TCPSessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return 0;
		}

		const TCPSessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->available();
			}
		}

		return 0;
	}

	bool TCPServer::TCPServerDetail::skip(const size_t size, const Optional<TCPSessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const TCPSessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->skip(size);
			}
		}

		return false;
	}

	bool TCPServer::TCPServerDetail::lookahead(void* dst, const size_t size, const Optional<TCPSessionID>& id) const
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const TCPSessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->lookahead(dst, size);
			}
		}

		return false;
	}

	bool TCPServer::TCPServerDetail::read(void* dst, const size_t size, const Optional<TCPSessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const TCPSessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->read(dst, size);
			}
		}

		return false;
	}

	bool TCPServer::TCPServerDetail::send(const void* data, const size_t size, const Optional<TCPSessionID>& id)
	{
		if (m_sessions.isEmpty())
		{
			return false;
		}

		const TCPSessionID sessionID = id.value_or(m_sessions.front().first);

		for (auto& session : m_sessions)
		{
			if (session.first == sessionID)
			{
				return session.second->send(data, size);
			}
		}

		return false;
	}

	void TCPServer::TCPServerDetail::onAccept(const asio::error_code& error, const std::shared_ptr<detail::ServerSession>& session)
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

		const TCPSessionID id = ++m_currentTCPSessionID;

		session->init(id);

		{
			const auto& socket = session->socket();

			LOG_INFO(U"TCPServer: accepted: remote {}<{}> local {}<{}>"_fmt(
				Unicode::WidenAscii(socket.remote_endpoint().address().to_string()),
				socket.remote_endpoint().port(),
				Unicode::WidenAscii(socket.local_endpoint().address().to_string()),
				socket.local_endpoint().port()));
		}

		m_sessions.push_back({ id, session });

		LOG_TRACE(U"TCPServer session [{}] created"_fmt(id));

		m_sessions.back().second->startReceive();

		if (m_allowMulti)
		{
			std::shared_ptr<detail::ServerSession> newSession = std::make_shared<detail::ServerSession>(*m_io_service);

			m_acceptor->async_accept(newSession->socket(),
				std::bind(&TCPServerDetail::onAccept, this, std::placeholders::_1, newSession));
		}
		else
		{
			cancelAccept();
		}
	}

	void TCPServer::TCPServerDetail::updateSession()
	{
		m_sessions.remove_if([](const auto& session) { return !session.second->isActive(); });
	}
}
