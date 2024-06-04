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
# include <Siv3D/Unicode.hpp>
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
		
		[[nodiscard]]
		static bool IsRunningInXcode_impl()
		{
			return (std::getenv("__XCODE_BUILT_PRODUCTS_DIR_PATHS") != nullptr);
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
	
		String ComputerName()
		{
			@autoreleasepool
			{
				NSString *localizedName = [[NSHost currentHost] localizedName];
				
				if (localizedName)
				{
					return Unicode::Widen(std::string([localizedName UTF8String]));
				}
				else
				{
					return{};
				}
			}
		}
	
		String UserName()
		{
			@autoreleasepool
			{
				NSString *userName = NSUserName();
				return Unicode::Widen(std::string([userName UTF8String]));
			}
		}
	
		String FullUserName()
		{
			@autoreleasepool
			{
				NSString *fullUserName = NSFullUserName();
				return Unicode::Widen(std::string([fullUserName UTF8String]));
			}
		}

		String DefaultLocale()
		{
			@autoreleasepool
			{
				CFLocaleRef locale = CFLocaleCopyCurrent();
				
				CFStringRef languageCodeStr = (CFStringRef)CFLocaleGetValue(locale, kCFLocaleLanguageCode);
				NSString *nsLanguageCode = (__bridge NSString*)languageCodeStr;
				std::string languageCode([nsLanguageCode UTF8String]);
				
				CFStringRef countryCodeStr = (CFStringRef)CFLocaleGetValue(locale, kCFLocaleCountryCode);
				NSString *nsCountryCode = (__bridge NSString*)countryCodeStr;
				std::string countryCode([nsCountryCode UTF8String]);
				
				CFRelease(locale);
				
				if (languageCode.empty())
				{
					return U"en-US";
				}
				else
				{
					return (Unicode::WidenAscii(languageCode) + U"-" + Unicode::Widen(countryCode));
				}
			}
		}

		String DefaultLanguage()
		{
			@autoreleasepool
			{
				NSArray<NSString*>* preferredLanguages = [NSLocale preferredLanguages];
				
				if (0 < preferredLanguages.count)
				{
					NSString *language = preferredLanguages[0];
					return Unicode::WidenAscii(std::string([language UTF8String]));
				}
				else
				{
					// Fallback to a default value if preferredLanguages is empty
					return U"en-US";
				}
			}
		}
	
		bool LaunchFile(const FilePathView fileName)
		{
			const std::string command = ("open '" + FileSystem::NativePath(fileName) + "'");

			return (std::system(command.c_str()) == 0);
		}

		bool LaunchFileWithTextEditor(const FilePathView fileName)
		{
			const std::string command = ("open -t '" + FileSystem::NativePath(fileName) + "'");

			return (std::system(command.c_str()) == 0);
		}

		bool IsRunningInVisualStudio()
		{
			return false;
		}

		bool IsRunningInXcode()
		{
			static const bool result = detail::IsRunningInXcode_impl();

			return result;
		}
	}
}
