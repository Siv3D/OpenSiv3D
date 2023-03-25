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
# include <SystemConfiguration/SystemConfiguration.h>

namespace s3d
{
	namespace Network
	{
		bool IsConnected()
		{
			const char* hostName = "www.example.com";
			
			SCNetworkReachabilityFlags flags;
			SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithName(NULL, hostName);
			const bool result = SCNetworkReachabilityGetFlags(reachability, &flags);
			CFRelease(reachability);

			if (not result)
			{
				return false;
			}

			const bool isReachable = ((flags & kSCNetworkFlagsReachable) != 0);
			const bool needsConnection = ((flags & kSCNetworkFlagsConnectionRequired) != 0);
			return (isReachable && (not needsConnection));
		}
	}
}
