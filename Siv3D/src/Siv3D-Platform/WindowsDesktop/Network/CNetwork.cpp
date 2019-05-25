//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# define NOMINMAX
# define _WINSOCK_DEPRECATED_NO_WARNINGS
# include <Winsock2.h>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include "CNetwork.hpp"

namespace s3d
{
	CNetwork::CNetwork()
	{

	}

	CNetwork::~CNetwork()
	{
		LOG_TRACE(U"CNetwork::~CNetwork()");

		::WSACleanup();
	}

	void CNetwork::init()
	{
		LOG_TRACE(U"CNetwork::init()");

		WSADATA wsaData = {};

		const int err = ::WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (err != 0)
		{
			throw EngineError(U"WSAStartup() failed");
		}

		LOG_INFO(U"ℹ️ CNetwork initialized");
	}

	Optional<IPv4> CNetwork::getMachineIP() const
	{
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

		return none;
	}
}
