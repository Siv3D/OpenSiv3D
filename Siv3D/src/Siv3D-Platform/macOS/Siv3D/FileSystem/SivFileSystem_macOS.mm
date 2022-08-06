//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <sys/stat.h>
# include <mach-o/dyld.h>
# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FileSystem.hpp>
# define BOOST_FILESYSTEM_NO_DEPRECATED
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
		static std::string MacOS_FullPath(const char* _path)
		{
			@autoreleasepool
			{
				NSString* path = [NSString stringWithUTF8String:_path];
				NSURL* file = [NSURL fileURLWithPath:path];
				NSURL* absolutePath = [file absoluteURL];
				NSString* str = [absolutePath path];
				return std::string([str UTF8String], [str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
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
						fs::copy_file(current, destination / current.filename(), fs::copy_options::overwrite_existing);
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
			
			FilePath fullpath = Unicode::FromUTF8(fs::weakly_canonical(detail::ToPath(path)).string());
			
			if (detail::IsDirectory(fullpath) && (not fullpath.ends_with(U'/')))
			{
				fullpath.push_back(U'/');
			}
			
			return fullpath;
		}
	
		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			if (not path) SIV3D_UNLIKELY
			{
				return Platform::NativeFilePath();
			}
			
			const FilePath fullpath = FullPath(path);
			
			return detail::MacOS_FullPath(fullpath.toUTF8().c_str());
		}
	
		FilePath VolumePath(const FilePathView)
		{
			// [Siv3D ToDo]
			return U"/";
		}

		FilePath PathAppend(const FilePathView lhs, const FilePathView rhs)
		{
			if (not rhs)
			{
				if (not lhs)
				{
					return{};
				}
				
				if (lhs.ends_with(U'/') || lhs.ends_with(U'\\'))
				{
					return FilePath{ lhs }.replace(U'\\', U'/');
				}
				else
				{
					return FilePath{ lhs + U'/' }.replace(U'\\', U'/');
				}
			}
			
			return FilePath{ Unicode::FromUTF8((detail::ToPath(lhs) / detail::ToPath(rhs)).string<std::string>()) }.replace(U'\\', U'/');
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
	
		// http://stackoverflow.com/questions/5772992/get-relative-path-from-two-absolute-paths
		FilePath RelativePath(const FilePathView _path, const FilePathView _start)
		{
			if (_path.isEmpty() || _start.isEmpty())
			{
				return FilePath();
			}

			const FilePath path = FullPath(_path);
			const FilePath start = FullPath(_start);

			if (!IsDirectory(start))
			{
				return path;
			}

			if (path == start)
			{
				return U"./";
			}

			fs::path p(path.toWstr()), base(start.toWstr());
			fs::path from_path, from_base, output;
			fs::path::iterator path_it = p.begin(), path_end = p.end();
			fs::path::iterator base_it = base.begin(), base_end = base.end();

			const std::string _dot(1, '.');
			const std::string _dots(2, '.');
			const std::string _sep(1, '/');

			for (;;)
			{
				if ((path_it == path_end) || (base_it == base_end) || (*path_it != *base_it))
				{
					for (; base_it != base_end; ++base_it)
					{
						if (*base_it == _dot)
							continue;
						else if (*base_it == _sep)
							continue;

						output /= "../";
					}

					fs::path::iterator path_it_start = path_it;

					for (; path_it != path_end; ++path_it)
					{
						if (path_it != path_it_start)
							output /= "/";

						if (*path_it == _dot)
							continue;

						if (*path_it == _sep)
							continue;

						output /= *path_it;
					}

					break;
				}

				from_path /= fs::path(*path_it);
				from_base /= fs::path(*base_it);

				++path_it;
				++base_it;
			}

			return Unicode::Widen(output.string()).replace(U'\\', U'/');
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
				const fs::copy_options option = (copyOption == CopyOption::OverwriteExisting)
					? fs::copy_options::overwrite_existing
					: fs::copy_options::none;
				
				boost::system::error_code ec;
				
				if (not fs::copy_file(detail::ToPath(from), detail::ToPath(to), option, ec))
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
			
			if (not allowUndo)
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
	
		bool RemoveContents(const FilePathView path, const AllowUndo allowUndo)
		{
			if (not IsDirectory(path))
			{
				return false;
			}

			if (not Remove(path, allowUndo))
			{
				return false;
			}

			return CreateDirectories(path);
		}

		bool Rename(const FilePathView from, const FilePathView to)
		{
			if ((not from) || (not to))
			{
				return false;
			}

			if (IsResourcePath(from) || IsResourcePath(to))
			{
				return false;
			}

			boost::system::error_code ec;
			fs::rename(fs::path(Unicode::ToWstring(from)), fs::path(Unicode::ToWstring(to)), ec);

			return (ec.value() == 0);
		}
	}
}
