//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# import  <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static bool MacOS_OpenURLInBrowser(const char* _url)
		{
			@autoreleasepool
			{
				NSString* url = [NSString stringWithUTF8String:_url];
				NSURL* ns_url = [NSURL URLWithString:url];
				const bool result = [[NSWorkspace sharedWorkspace]
									openURLs:@[ns_url]
									withAppBundleIdentifier:nil
									options:NSWorkspaceLaunchDefault
									additionalEventParamDescriptor:nil
									launchIdentifiers:nil];
				return result;
			}
		}
	
		[[nodiscard]]
		static bool MacOS_OpenHTMLInBrowser(const char* _path)
		{
			@autoreleasepool
			{
				NSString* path = [NSString stringWithUTF8String:_path];
				const bool result = [[NSWorkspace sharedWorkspace]
									openFile:path];
				return result;
			}
			
		}
	}

	namespace System
	{
		bool LaunchBrowser(const FilePathView _url)
		{
			const bool isWebPage = _url.starts_with(U"http://")
				|| _url.starts_with(U"https://");

			if (isWebPage)
			{
				return detail::MacOS_OpenURLInBrowser(_url.narrow().c_str());
			}
			else
			{
				const String extension = FileSystem::Extension(_url);
				const bool isHTML = (extension == U"html") || (extension == U"htm");

				if (!isHTML)
				{
					return false;
				}

				return detail::MacOS_OpenHTMLInBrowser(FileSystem::FullPath(_url).narrow().c_str());
			}
		}
	}
}
