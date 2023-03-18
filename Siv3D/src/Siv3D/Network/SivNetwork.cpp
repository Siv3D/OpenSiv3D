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

# include <Siv3D/Network.hpp>

# if SIV3D_PLATFORM(WINDOWS) || SIV3D_PLATFORM(MACOS) 

# define _WINSOCK_DEPRECATED_NO_WARNINGS
# ifndef _WIN32_WINNT
#	define	_WIN32_WINNT _WIN32_WINNT_WIN8
# endif
# ifndef NTDDI_VERSION
#	define	NTDDI_VERSION NTDDI_WIN8
# endif
# define  ASIO_STANDALONE
# include <ThirdParty/asio/asio.hpp>

namespace s3d
{
	namespace Network
	{
		Array<IPv4Address> EnumerateIPv4Addresses()
		{
			asio::io_service io_service;
			asio::ip::tcp::resolver resolver{ io_service };
			asio::ip::tcp::resolver::query query{ asio::ip::host_name(), "" };

			Array<IPv4Address> results;

			for (asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
				it != asio::ip::tcp::resolver::iterator{}; ++it)
			{
				const asio::ip::address address = it->endpoint().address();

				if (address.is_v4())
				{
					results.emplace_back(address.to_v4().to_string());
				}
			}

			return results;
		}
	}
}

# else

# include <sys/types.h>
# include <ifaddrs.h>
# include <arpa/inet.h>

namespace s3d
{
	namespace Network
	{
		Array<IPv4Address> EnumerateIPv4Addresses()
		{
			Array<IPv4Address> results;

			std::string ip;
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
						ip = inet_ntoa(sa->sin_addr);
						results << IPv4Address(ip);
					}
				}

				freeifaddrs(ifaddr);
			}

			return results;
		}
	}
}

# endif
