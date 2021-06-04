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

# include <sys/stat.h>
# include <mach-o/dyld.h>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include <boost/filesystem.hpp>
# import  <Foundation/Foundation.h>

namespace s3d
{
	namespace fs = boost::filesystem;

	namespace detail
	{
		[[nodiscard]]
		static fs::path ToPath(const FilePathView path)
		{
			return fs::path(path.toWstr());
		}
	
		[[nodiscard]]
		static bool GetStat(const FilePathView path, struct stat& s)
		{
			return (::stat(FilePath(path).replaced(U'\\', U'/').narrow().c_str(), &s) == 0);
		}
	
		[[nodiscard]]
		static bool Exists(const FilePathView path)
		{
			struct stat s;
			return GetStat(path, s);
		}
	
		[[nodiscard]]
		static bool IsRegular(const FilePathView path)
		{
			struct stat s;
			if (!GetStat(path, s))
			{
				return false;
			}

			return S_ISREG(s.st_mode);
		}
	
		[[nodiscard]]
		static bool IsDirectory(const FilePathView path)
		{
			struct stat s;
			if (!GetStat(path, s))
			{
				return false;
			}
			
			return S_ISDIR(s.st_mode);
		}

		[[nodiscard]]
		static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
		{
			for (auto& ch : path)
			{
				if (ch == U'\\')
				{
					ch = U'/';
				}
			}
			
			if (!path.ends_with(U'/') && (skipDirectoryCheck || IsDirectory(path)))
			{
				path.push_back(U'/');
			}
			
			return path;
		}
	
		[[nodiscard]]
		static DateTime ToDateTime(const ::timespec& tv)
		{
			::tm lt;
			::localtime_r(&tv.tv_sec, &lt);
			return{ (1900 + lt.tm_year),
					(1 + lt.tm_mon),
					(lt.tm_mday),
					lt.tm_hour,
					lt.tm_min,
					lt.tm_sec,
					static_cast<int32>(tv.tv_nsec / (1'000'000))};
		}
		
		[[nodiscard]]
		static String ToUniqueFileName(const uint64 value)
		{
			constexpr char32 hex[] = U"0123456789abcdef";
			
			String name(19, U'-');
			
			for (size_t i = 0; i < 16; ++i)
			{
				name[i + (i / 4)] = hex[(value >> (i * 4)) & 0xF];
			}
			
			return name;
		}
	
		[[nodiscard]]
		static std::string MacOS_FullPath(const char* _path, bool isRelative)
		{
			@autoreleasepool
			{
				NSString* path = [NSString stringWithUTF8String:_path];
				
				if (isRelative)
				{
					NSURL* bundle = [[NSBundle mainBundle] bundleURL];
					NSURL* file = [NSURL fileURLWithPath:path relativeToURL:bundle];
					NSURL* absolutePath = [file absoluteURL];
					NSString* str = [absolutePath path];
					return std::string([str UTF8String], [str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
				}
				else
				{
					NSURL* file = [NSURL fileURLWithPath:path];
					NSURL* absolutePath = [file absoluteURL];
					NSString* str = [absolutePath path];
					return std::string([str UTF8String], [str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
				}
			}
		}
	
		[[nodiscard]]
		static std::string MacOS_CurrentPath()
		{
			@autoreleasepool
			{
				if (NSString* current = [[NSFileManager defaultManager] currentDirectoryPath]) // requires permission
				{
					return [current UTF8String];
				}
				else
				{
					NSDictionary* env = [[NSProcessInfo processInfo] environment];
					
					if (NSString* current = env[@"PWD"])
					{
						return [current UTF8String];
					}
				}
			
				return "";
			}
		}
	
		[[nodiscard]]
		static bool MacOS_ChangeCurrentDirectory(const char* _path)
		{
			@autoreleasepool
			{
				NSString* path = [NSString stringWithUTF8String:_path];
				return ([[NSFileManager defaultManager] changeCurrentDirectoryPath:path] == YES);
			}
		}
	
		[[nodiscard]]
		static std::string MacOS_SpecialFolder(const SpecialFolder folder)
		{
			@autoreleasepool
			{
				const NSSearchPathDirectory folders[] = {
					NSDesktopDirectory,
					NSDocumentDirectory,
					NSCachesDirectory,
					NSPicturesDirectory,
					NSMusicDirectory,
					NSMoviesDirectory,
					NSLibraryDirectory, // (dummy)
					NSLibraryDirectory, // (dummy)
					NSLibraryDirectory, // (dummy)
					NSLibraryDirectory, // (dummy)
					NSApplicationDirectory,
				};
				
				NSArray* paths = NSSearchPathForDirectoriesInDomains(folders[FromEnum(folder)], NSUserDomainMask, YES);
				
				NSString* directory = [paths objectAtIndex:0];
				
				// NSCachesDirectory
				if (folder == SpecialFolder::LocalAppData)
				{
					NSString* bundleID = [[NSBundle mainBundle] bundleIdentifier];
					directory = [directory stringByAppendingString:@"/Siv3DApp/"];
					directory = [directory stringByAppendingString:bundleID];
				}
				else if (folder == SpecialFolder::SystemFonts)
				{
					directory = @"/System/Library/Fonts";
				}
				else if (folder == SpecialFolder::LocalFonts)
				{
					directory = @"/Library/Fonts";
				}
				else if (folder == SpecialFolder::UserFonts)
				{
					directory = [directory stringByAppendingString:@"/Fonts"];
				}
				else if (folder == SpecialFolder::UserProfile)
				{
					directory = NSHomeDirectory();
				}
				
				return [directory UTF8String];
			}
		}
	
		[[nodiscard]]
		static bool CopyDirectory(const fs::path& source, const fs::path& destination)
		{
			try
			{
				if (!fs::exists(source) || !fs::is_directory(source) )
				{
					return false;
				}
				
				if (!fs::exists(destination))
				{
					if (!fs::create_directory(destination))
					{
						return false;
					}
				}
			}
			catch (fs::filesystem_error&)
			{
				return false;
			}
			
			for (fs::directory_iterator file(source); file != fs::directory_iterator(); ++file)
			{
				try
				{
					fs::path current(file->path());
					
					if (fs::is_directory(current))
					{
						if (!CopyDirectory(current, destination / current.filename()))
						{
							return false;
						}
					}
					else
					{
						fs::copy_file(current, destination / current.filename(), fs::copy_option::overwrite_if_exists);
					}
				}
				catch (const fs::filesystem_error&)
				{
					return false;
				}
			}
			
			return true;
		}
	
		[[nodiscard]]
		static bool MacOS_TrashFile(const std::string_view path, const bool isDirectory)
		{
			@autoreleasepool
			{
				NSURL* url = (CFBridgingRelease(CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8*)path.data(), path.size(), isDirectory)));
				
				const bool result = [[NSFileManager defaultManager] trashItemAtURL: url
																  resultingItemURL: nil
																			 error: nil];
				
				return result;
			}
		}
	
		namespace init
		{
			[[nodiscard]]
			static FilePath ParentPath(FilePath path, size_t n)
			{
				if (path.count(U'/') <= n)
				{
					return FilePath(U"NN");
				}

				while (path)
				{
					if (path.back() == U'/')
					{
						if (n == 0)
						{
							break;
						}
						
						--n;
					}
					
					path.pop_back();
				}
				
				return path;
			}
		
			const static FilePath g_initialPath = []()
			{
				char path_str[4096];
				uint32_t bufferSize = sizeof(path_str);

				if (_NSGetExecutablePath(path_str, &bufferSize) != 0)
				{
					return FilePath{};
				}

				const String path = Unicode::Widen(path_str);

				FilePath modulePath = ParentPath(path, 2);

				if (modulePath.ends_with(U'/'))
				{
					modulePath.pop_back();
				}
				
				FilePath initialPath = ParentPath(path, 3);
				
				::chdir(initialPath.narrow().c_str());

				return initialPath;
			}();
		
			const static FilePath g_modulePath = []()
			{
				char path_str[4096];
				uint32_t bufferSize = sizeof(path_str);

				if (_NSGetExecutablePath(path_str, &bufferSize) != 0)
				{
					return FilePath{};
				}

				const String path = Unicode::Widen(path_str);

				FilePath modulePath = ParentPath(path, 2);

				if (modulePath.ends_with(U'/'))
				{
					modulePath.pop_back();
				}

				return modulePath;
			}();

			const static std::array<FilePath, 11> g_specialFolderPaths = []()
			{
				std::array<FilePath, 11> specialFolderPaths;

				for (int32 i = 0; i < static_cast<int32>(specialFolderPaths.size()); ++i)
				{
					specialFolderPaths[i] = Unicode::Widen(detail::MacOS_SpecialFolder(ToEnum<SpecialFolder>(i))) << U'/';
				}

				return specialFolderPaths;
			}();

			const static Array<FilePath> g_resourceFilePaths = []()
			{
				const FilePath resourcePath = FileSystem::ModulePath() + U"/Contents/Resources/";

				Array<FilePath> paths = FileSystem::DirectoryContents(resourcePath, Recursive::Yes);

				paths.remove_if(FileSystem::IsDirectory);
				
				paths.remove(resourcePath + U"icon.icns");

				paths.sort();
				
				return paths;
			}();

			const Array<FilePath>& GetResourceFilePaths() noexcept
			{
				return g_resourceFilePaths;
			}			
			
			//static bool g_isSandBoxed;
		}
	}

	namespace FileSystem
	{
		bool IsResourcePath(const FilePathView path) noexcept
		{
			const FilePath resourceDirectory = FileSystem::ModulePath() + U"/Contents/Resources/";

			return FullPath(path).starts_with(resourceDirectory);
		}
	
		bool Exists(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}

			return detail::Exists(path);
		}

		bool IsDirectory(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}

			return detail::IsDirectory(path);
		}

		bool IsFile(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}

			return detail::IsRegular(path);
		}

		bool IsResource(const FilePathView path)
		{
			return IsResourcePath(path)
				&& detail::Exists(path);
		}

		FilePath FullPath(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return FilePath();
			}
			
			const bool isDirectory = path.ends_with(U'/');
			
			FilePath src;
			bool isRelative = false;
			
			if (path.starts_with(U"/Users/"))
			{
				src = path;
			}
			else
			{
				src = (U"../" + path);
				isRelative = true;
			}
			
			FilePath result = Unicode::Widen(detail::MacOS_FullPath(src.toUTF8().c_str(), isRelative));
			
			if (result.starts_with(U"file://"))
			{
				result.erase(result.begin(), result.begin() + 7);
			}
			
			if ((isDirectory || IsDirectory(result)) && !result.ends_with(U'/'))
			{
				result.push_back(U'/');
			}
			
			return result;
		}
	
		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return Platform::NativeFilePath();
			}
			
			FilePath src;
			bool isRelative = false;
			
			if (path.starts_with(U"/Users/"))
			{
				src = path;
			}
			else
			{
				src = U"../" + path;
				isRelative = true;
			}
			
			return detail::MacOS_FullPath(src.toUTF8().c_str(), isRelative);
		}
	
		FilePath VolumePath(const FilePathView)
		{
			// [Siv3D ToDo]
			return U"/";
		}
	
		bool IsEmptyDirectory(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return false;
			}
			
			const FilePath src(path);
			struct stat s;
			if (!detail::GetStat(src, s))
			{
				return false;
			}
			
			if (S_ISREG(s.st_mode))
			{
				return false;
			}
			else if (S_ISDIR(s.st_mode))
			{
				return fs::directory_iterator(detail::ToPath(src)) == fs::directory_iterator();
			}
			else
			{
				// [Siv3D ToDo]
				return false;
			}
		}
	
		int64 Size(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return 0;
			}

			const FilePath fullPath = FullPath(path);
			
			struct stat s;
			if (!detail::GetStat(fullPath, s))
			{
				return 0;
			}

			if (S_ISREG(s.st_mode))
			{
				return s.st_size;
			}
			else if (S_ISDIR(s.st_mode))
			{
				int64 result = 0;

				for (const auto& v : fs::recursive_directory_iterator(path.narrow()))
				{
					struct stat s;
					
					if (::stat(v.path().c_str(), &s) != 0 || S_ISDIR(s.st_mode))
					{
						continue;
					}

					result += s.st_size;
				}
				
				return result;
			}
			else
			{
				return 0;
			}
		}

		int64 FileSize(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return 0;
			}
			
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return 0;
			}
			
			if (!S_ISREG(s.st_mode))
			{
				return 0;
			}
			
			return s.st_size;
		}
	
		Optional<DateTime> CreationTime(const FilePathView path)
		{
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return none;
			}
			
			return detail::ToDateTime(s.st_birthtimespec);
		}

		Optional<DateTime> WriteTime(const FilePathView path)
		{
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return none;
			}
			
			return detail::ToDateTime(s.st_mtimespec);
		}
		
		Optional<DateTime> AccessTime(const FilePathView path)
		{
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return none;
			}
			
			return detail::ToDateTime(s.st_atimespec);
		}
	
		Array<FilePath> DirectoryContents(const FilePathView path, const Recursive recursive)
		{
			Array<FilePath> paths;
			
			if (path.isEmpty() || !IsDirectory(path))
			{
				return paths;
			}
			
			if (recursive)
			{
				for (const auto& v : fs::recursive_directory_iterator(path.narrow()))
				{
					paths.push_back(FullPath(Unicode::Widen(v.path().string())));
				}
			}
			else
			{
				for (const auto& v : fs::directory_iterator(path.narrow()))
				{
					paths.push_back(FullPath(Unicode::Widen(v.path().string())));
				}
			}
			
			return paths;
		}
	
		const FilePath& InitialDirectory() noexcept
		{
			return detail::init::g_initialPath;
		}

		const FilePath& ModulePath() noexcept
		{
			return detail::init::g_modulePath;
		}

		FilePath CurrentDirectory()
		{
			return detail::NormalizePath(Unicode::Widen(detail::MacOS_CurrentPath()));
		}
	
		bool ChangeCurrentDirectory(const FilePathView path)
		{
			if (!IsDirectory(path))
			{
				return false;
			}
			
			return detail::MacOS_ChangeCurrentDirectory(path.narrow().c_str());
		}

		const FilePath& GetFolderPath(const SpecialFolder folder)
		{
			assert(FromEnum(folder) < static_cast<int32>(std::size(detail::init::g_specialFolderPaths)));

			return detail::init::g_specialFolderPaths[FromEnum(folder)];
		}
	
		FilePath TemporaryDirectoryPath()
		{
			return (GetFolderPath(SpecialFolder::LocalAppData) + U"Temp/");
		}

		FilePath UniqueFilePath(const FilePathView directory)
		{
			HardwareRNG rng;
			UniformDistribution<uint64> ud(0, UINT64_MAX);
			
			FilePath directoryPath(directory);
			
			if ((not directoryPath.isEmpty())
				&& (not directoryPath.ends_with(U'/')))
			{
				directoryPath.push_back(U'/');
			}
			
			for (uint64 n = ud(rng);; ++n)
			{
				const FilePath path = directoryPath + detail::ToUniqueFileName(n) + U".tmp";
				
				if (not Exists(path))
				{
					return path;
				}
			}
		}
		
		bool CreateDirectories(const FilePathView path)
		{
			if (not path)
			{
				return false;
			}

			try
			{
				fs::create_directories(detail::ToPath(path));
				return true;
			}
			catch (const fs::filesystem_error&)
			{
				return false;
			}
		}

		bool CreateParentDirectories(const FilePathView path)
		{
			if (not path)
			{
				return false;
			}

			const FilePath parentDirectory = ParentPath(FullPath(path));
			
			if (not Exists(parentDirectory))
			{
				return CreateDirectories(parentDirectory);
			}
			
			return true;
		}
	
		bool Copy(const FilePathView from, const FilePathView to, const CopyOption copyOption)
		{
			if ((not from) || (not to))
			{
				return false;
			}

			if (IsResourcePath(from) || IsResourcePath(to))
			{
				return false;
			}
			
			if (detail::Exists(to))
			{
				if (copyOption == CopyOption::Default)
				{
					return false;
				}
				else if (copyOption == CopyOption::SkipExisting)
				{
					return true;
				}
			}

			CreateParentDirectories(to);

			if (IsFile(from))
			{
				const fs::copy_option option = (copyOption == CopyOption::OverwriteExisting)
					? fs::copy_option::overwrite_if_exists
					: fs::copy_option::fail_if_exists;
				
				try
				{
					fs::copy_file(detail::ToPath(from), detail::ToPath(to), option);
				}
				catch (const fs::filesystem_error&)
				{
					return false;
				}
			}
			else
			{
				return detail::CopyDirectory(detail::ToPath(from), detail::ToPath(to));
			}
			
			return true;
		}
	
		bool Remove(const FilePathView path, const AllowUndo allowUndo)
		{
			if (not path)
			{
				return false;
			}
			
			if (!allowUndo)
			{
				try
				{
					fs::remove_all(detail::ToPath(path));
					return true;
				}
				catch (const fs::filesystem_error&)
				{
					return false;
				}
			}

			return detail::MacOS_TrashFile(path.narrow(), IsDirectory(path));
		}
	
	}
}
