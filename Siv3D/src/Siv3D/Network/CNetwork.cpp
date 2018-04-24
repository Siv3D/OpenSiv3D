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
	# define _WINSOCK_DEPRECATED_NO_WARNINGS
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

	Optional<IPv4> CNetwork::getMachineIP() const
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		char name[255];

		if (::gethostname(name, sizeof(name)) != 0)
		{
			return none;
		}

		const PHOSTENT hostinfo = ::gethostbyname(name);

		if (!hostinfo)
		{
			return none;
		}

		if (hostinfo->h_addr_list[0])
		{
			const in_addr ip = *(in_addr*)hostinfo->h_addr_list[0];

			if (const IPv4 machineIP = IPv4(ip.S_un.S_addr); machineIP.asUint8[0] != 127)
			{
				return machineIP;
			}
		}

	# endif

		return none;
	}
}
