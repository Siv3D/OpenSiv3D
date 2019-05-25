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
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <ifaddrs.h>
# include <string>
# import  <Foundation/Foundation.h>

namespace s3d
{
    std::string macOS_GetPrivateIPv4()
    {
        NSString* result = @"";
        struct ifaddrs* interfaces = nullptr;
        
        if (getifaddrs(&interfaces) == 0)
        {
            for (struct ifaddrs* tmp = interfaces; tmp;)
            {
                if (tmp->ifa_addr->sa_family == AF_INET)
                {
                    result = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)tmp->ifa_addr)->sin_addr)];
                }
                
                tmp = tmp->ifa_next;
            }
            
            freeifaddrs(interfaces);
        }
        
        return [result UTF8String];
    }
}
