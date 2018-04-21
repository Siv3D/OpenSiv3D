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
# include "../../ThirdParty/tacopie/tacopie"

namespace s3d
{
	class TCPServer::CTCPServer
	{
	private:

		tacopie::tcp_server m_server;

		Array<uint8> m_receivedBuffer;

	public:

		CTCPServer();

		~CTCPServer();

		void start(uint16 port);
	};
}
