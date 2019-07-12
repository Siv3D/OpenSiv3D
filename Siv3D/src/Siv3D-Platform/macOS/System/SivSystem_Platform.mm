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

# include <unistd.h>
# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# import <Cocoa/Cocoa.h>

namespace s3d
{
	static bool macOS_LaunchBrowser(const char* url)
	{
		NSString* str = [NSString stringWithCString:url encoding:NSUTF8StringEncoding];
		NSURL* ns_url = [NSURL URLWithString:str];
		
		const bool result = [[NSWorkspace sharedWorkspace]
							 openURLs:@[ns_url]
							 withAppBundleIdentifier:nil
							 options:NSWorkspaceLaunchDefault
							 additionalEventParamDescriptor:nil
							 launchIdentifiers:nil];
		
		return result;
	}
	
	namespace System
	{
		void Sleep(int32 milliseconds)
		{
			if (milliseconds < 0)
			{
				return;
			}
			
			::usleep(static_cast<uint32>(milliseconds) * 1000);
		}
		
		bool LaunchBrowser(const FilePath& _url)
		{
			const bool isWebPage = _url.starts_with(U"http://") || _url.starts_with(U"https://");
			FilePath url = _url;
			
			if (!isWebPage)
			{
				const String extension = FileSystem::Extension(_url);
				
				if (extension != U"html" && extension != U"htm")
				{
					return false;
				}
				
				url.insert(0, U"file://");
			}
			
			return macOS_LaunchBrowser(url.narrow().c_str());
		}
	}
}
