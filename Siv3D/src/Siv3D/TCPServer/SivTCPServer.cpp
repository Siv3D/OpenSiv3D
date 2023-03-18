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

# include <Siv3D/TCPServer.hpp>
# include <Siv3D/TCPServer/TCPServerDetail.hpp>

namespace s3d
{
	TCPServer::TCPServer()
		: pImpl{ std::make_shared<TCPServerDetail>() } {}
	
	TCPServer::~TCPServer() {}

	void TCPServer::startAccept(const uint16 port)
	{
		pImpl->startAccept(port);
	}

	void TCPServer::startAcceptMulti(const uint16 port)
	{
		pImpl->startAcceptMulti(port);
	}

	void TCPServer::cancelAccept()
	{
		pImpl->cancelAccept();
	}

	bool TCPServer::isAccepting() const
	{
		return pImpl->isAccepting();
	}

	void TCPServer::disconnect()
	{
		return pImpl->disconnect();
	}

	bool TCPServer::hasSession() const
	{
		return pImpl->hasSession();
	}

	bool TCPServer::hasSession(const TCPSessionID id) const
	{
		return pImpl->hasSession(id);
	}

	size_t TCPServer::num_sessions() const
	{
		return pImpl->num_sessions();
	}

	Array<TCPSessionID> TCPServer::getSessionIDs() const
	{
		return pImpl->getSessionIDs();
	}

	uint16 TCPServer::port() const
	{
		return pImpl->port();
	}

	size_t TCPServer::available(const Optional<TCPSessionID>& id)
	{
		return pImpl->available(id);
	}

	bool TCPServer::skip(const size_t size, const Optional<TCPSessionID>& id)
	{
		return pImpl->skip(size, id);
	}

	bool TCPServer::lookahead(void* dst, const size_t size, const Optional<TCPSessionID>& id) const
	{
		return pImpl->lookahead(dst, size, id);
	}

	bool TCPServer::read(void* dst, const size_t size, const Optional<TCPSessionID>& id)
	{
		return pImpl->read(dst, size, id);
	}

	bool TCPServer::send(const void* data, const size_t size, const Optional<TCPSessionID>& id)
	{
		return pImpl->send(data, size, id);
	}
}
