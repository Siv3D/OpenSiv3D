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

# include <Siv3D/TCPClient.hpp>
# include "CTCPClient.hpp"

namespace s3d
{
	TCPClient::TCPClient()
		: pImpl(std::make_shared<CTCPClient>())
	{

	}

	TCPClient::~TCPClient()
	{

	}

	bool TCPClient::open()
	{
		return pImpl->open();
	}
}
