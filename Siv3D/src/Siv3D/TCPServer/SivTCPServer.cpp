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

# include <Siv3D/TCPServer.hpp>
# include "CTCPServer.hpp"

namespace s3d
{
	TCPServer::TCPServer()
		: pImpl(std::make_shared<CTCPServer>())
	{

	}

	TCPServer::~TCPServer()
	{

	}

	void TCPServer::start(const uint16 port)
	{
		pImpl->start(port);
	}
}
