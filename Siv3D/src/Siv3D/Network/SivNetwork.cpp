//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Network.hpp>
# define _WINSOCK_DEPRECATED_NO_WARNINGS
# define _WIN32_WINNT _WIN32_WINNT_WIN10
# include <ThirdParty/asio/asio.hpp>

namespace s3d
{
	namespace Network
	{
		Array<IPv4Address> EnumerateIPV4Addresses()
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
