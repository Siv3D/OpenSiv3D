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

				if (not isHTML)
				{
					return false;
				}

				return detail::MacOS_OpenHTMLInBrowser(FileSystem::FullPath(_url).narrow().c_str());
			}
		}
	
		bool ShowInFileManager(const FilePathView path)
		{
			const FilePath fullPath = FileSystem::FullPath(path);
			
			if (not FileSystem::Exists(fullPath))
			{
				return false;
			}
			
			const std::string pathUTF8 = "file:" + fullPath.toUTF8();
			
			@autoreleasepool
			{
				NSString* url = [NSString stringWithUTF8String:pathUTF8.c_str()];
				NSURL* ns_url = [NSURL URLWithString:url];
				NSArray *fileURLs = [NSArray arrayWithObjects:ns_url, nil];
				[[NSWorkspace sharedWorkspace] activateFileViewerSelectingURLs:fileURLs];
			}
			
			return true;
		}
	}
}
