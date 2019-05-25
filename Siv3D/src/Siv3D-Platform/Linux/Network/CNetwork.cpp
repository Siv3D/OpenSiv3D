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

# include <sys/types.h>
# include <ifaddrs.h>
# include <arpa/inet.h>

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include "CNetwork.hpp"

namespace s3d
{
	namespace detail
	{
		std::string Linux_GetPrivateIPv4()
		{
			std::string result = "";
			struct ifaddrs* ifaddr = nullptr;
			struct ifaddrs* ifa = nullptr;

			if (getifaddrs(&ifaddr) == 0)
			{
				for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
				{
					if (ifa->ifa_addr == NULL)
					{
						continue;
					}

					if (ifa->ifa_addr->sa_family == AF_INET)
					{
						struct sockaddr_in* sa = (struct sockaddr_in *)ifa->ifa_addr;
						result = inet_ntoa(sa->sin_addr);
					}
				}

				freeifaddrs(ifaddr);
			}

			return result;
		}
	}
    
	CNetwork::CNetwork()
	{

	}

	CNetwork::~CNetwork()
	{
		LOG_TRACE(U"CNetwork::~CNetwork()");
	}

	void CNetwork::init()
	{
		LOG_TRACE(U"CNetwork::init()");

		LOG_INFO(U"ℹ️ CNetwork initialized");
	}

	Optional<IPv4> CNetwork::getMachineIP() const
	{
        const String ip = Unicode::WidenAscii(detail::Linux_GetPrivateIPv4());
        
        if (!ip.isEmpty() && !ip.starts_with(U"127"))
        {
            return IPv4(ip);
        }

		return none;
	}
}
