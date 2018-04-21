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

# include "CNetwork.hpp"
# include <Siv3D/Logger.hpp>

# if defined(SIV3D_TARGET_WINDOWS)
	# include <Winsock2.h>
# endif

namespace s3d
{
	CNetwork::CNetwork()
	{

	}

	CNetwork::~CNetwork()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		::WSACleanup();

	# endif
	}

	bool CNetwork::init()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		WSADATA wsaData = {};

		const int err = ::WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (err != 0)
		{
			return false;
		}

	# endif

		LOG_INFO(U"ℹ️ Network initialized");

		return true;
	}
}
