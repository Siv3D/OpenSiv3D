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
	{

	}

	TCPServer::CTCPServer::~CTCPServer()
	{

	}

	void TCPServer::CTCPServer::start(const uint16 port)
	{
		m_server.start("127.0.0.1", port);
	}
}
