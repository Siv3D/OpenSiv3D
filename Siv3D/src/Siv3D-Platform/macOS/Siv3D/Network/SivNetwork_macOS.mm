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
# import <Foundation/Foundation.h>
# import <SystemConfiguration/SystemConfiguration.h>

namespace s3d
{
	namespace Network
	{
		bool IsConnected()
		{
			SCNetworkReachabilityFlags flags;
			SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithName(NULL, "www.example.com");
			const BOOL result = SCNetworkReachabilityGetFlags(reachability, &flags);
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
