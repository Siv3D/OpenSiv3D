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

# include <Siv3D/Common.hpp>
# include <Siv3D/Network.hpp>
# include <ifaddrs.h>
# include <net/if.h>

namespace s3d
{
	namespace Network
	{
		bool IsConnected()
		{
			struct ifaddrs* ifaddr;
			if (getifaddrs(&ifaddr) == -1)
			{
				return false;
			}

			bool result = false;
			for (struct ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
			{
				if (ifa->ifa_addr == nullptr)
				{
					continue;
				}

				const int family = ifa->ifa_addr->sa_family;

				if (((family == AF_INET )|| (family == AF_INET6))
					&& (not (ifa->ifa_flags & IFF_LOOPBACK)))
				{
					result = true;
					break;
				}
			}

			freeifaddrs(ifaddr);
			return result;
		}
	}
}
