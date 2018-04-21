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

namespace s3d
{
	class TCPClient::CTCPClient
	{
	private:


	public:

		CTCPClient();

		~CTCPClient();

		bool open();
	};
}
