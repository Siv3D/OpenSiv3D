//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Fwd.hpp>

# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Shlobj.h>
# include <filesystem>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace fs = std::experimental::filesystem;

	namespace detail
	{
		inline bool IsResourcePath(const FilePath& path)
		{	
			return path.starts_with(L'/');
		}

		inline bool IsNotFound(const fs::file_status& status)
		{
			return status.type() == fs::file_type::not_found;
		}

		inline bool IsRegular(const fs::file_status& status)
		{
			return status.type() == fs::file_type::regular;
		}

		inline bool IsDirectory(const fs::file_status& status)
		{
			return status.type() == fs::file_type::directory;
		}

		inline bool ResourceExists(const FilePath& path)
		{
			return ::FindResourceW(::GetModuleHandleW(nullptr), (L'#' + path.substr(1)).c_str(), L"FILE") != nullptr;
		}

		static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
		{
			for (auto& ch : path)
			{
				if (ch == L'\\')
				{
					ch = L'/';
				}
			}

			if (!path.ends_with(L'/')
				&& (skipDirectoryCheck || IsDirectory(fs::status(fs::path(path.str())))))
			{
				path.push_back(L'/');
			}

			return path;
		}

		static int64 DirectorySizeRecursive(FilePath directory)
		{
			WIN32_FIND_DATAW data;
			HANDLE sh = ::FindFirstFileW((directory + L'*').c_str(), &data);

			if (sh == INVALID_HANDLE_VALUE)
			{
				return 0;
			}

			int64 result = 0;

			do
			{
				if (!(data.cFileName[0] == L'.' && data.cFileName[1] == L'\0')
					&& !(data.cFileName[0] == L'.' && data.cFileName[1] == L'.' && data.cFileName[2] == L'\0'))
				{
					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						result += DirectorySizeRecursive((directory + data.cFileName) + L'/');
					}
					else
					{
						result += (static_cast<uint64>(data.nFileSizeHigh) << 32) + data.nFileSizeLow;
					}
				}

			}
			while (::FindNextFileW(sh, &data));

			::FindClose(sh);

			return result;
		}

		static DateTime FiletimeToTime(FILETIME& in)
		{
			SYSTEMTIME systemtime;
			::FileTimeToLocalFileTime(&in, &in);
			::FileTimeToSystemTime(&in, &systemtime);

			return{ systemtime.wYear, systemtime.wMonth, systemtime.wDay,
				systemtime.wHour, systemtime.wMinute, systemtime.wSecond, systemtime.wMilliseconds };
		}

		static void DirectoryContentsRecursive(FilePath directory, Array<FilePath>& paths, bool recursive = true)
		{
			WIN32_FIND_DATAW data;
			HANDLE sh = ::FindFirstFileW((directory + L'*').c_str(), &data);

			if (sh == INVALID_HANDLE_VALUE)
			{
				return;
			}

			do
			{
				if (!(data.cFileName[0] == L'.' && data.cFileName[1] == L'\0')
					&& !(data.cFileName[0] == L'.' && data.cFileName[1] == L'.' && data.cFileName[2] == L'\0'))
				{
					paths.push_back(directory + data.cFileName);

					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						paths.back().push_back(L'/');

						if (recursive)
						{
							DirectoryContentsRecursive(paths.back(), paths, true);
						}
					}
				}

			}
			while (::FindNextFileW(sh, &data));

			::FindClose(sh);
		}

		static bool Remove(const FilePath& path, const bool allowUndo)
		{
			const String from = (path + L'\0').replaced(L'/', L'\\');

			SHFILEOPSTRUCTW fileOption{};
			fileOption.wFunc	= FO_DELETE;
			fileOption.pFrom	= from.c_str();
			fileOption.fFlags	= FOF_NOERRORUI | FOF_SILENT | FOF_NOCONFIRMATION
								  | (allowUndo ? FOF_ALLOWUNDO : 0);

			return ::SHFileOperationW(&fileOption) == 0 && !fileOption.fAnyOperationsAborted;
		}

		namespace init
		{
			const static FilePath g_initialPath = NormalizePath(fs::current_path().wstring());

			static FilePath g_modulePath = FilePath();

			void SetModulePath()
			{
				wchar result[1024];
				const DWORD length = ::GetModuleFileNameW(nullptr, result, _countof(result));

				if (length == 0 || length >= _countof(result))
				{
					return;
				}
				
				g_modulePath.assign(result, result + length).replace(L'\\', L'/');
			}
		}
	}

	namespace FileSystem
	{
		bool Exists(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return !detail::IsNotFound(fs::status(fs::path(path.str())));
		}

		bool IsDirectory(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			return detail::IsDirectory(fs::status(fs::path(path.str())));
		}

		bool IsFile(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return detail::ResourceExists(path);
			}

			return detail::IsRegular(fs::status(fs::path(path.str())));
		}

		bool IsResource(const FilePath& path)
		{
			return detail::IsResourcePath(path) && detail::ResourceExists(path);
		}

		FilePath FullPath(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if (detail::IsResourcePath(path))
			{
				return path;
			}

			wchar result[1024];
			wchar* pFilePart = nullptr;
			const DWORD length = ::GetFullPathNameW(path.c_str(), _countof(result), result, &pFilePart);

			if (length == 0)
			{
				// [Siv3D*TODO]
				return FilePath();
			}
			else if (length > std::size(result))
			{
				// [Siv3D*TODO]
				return FilePath();
			}

			const bool isDirectory = (pFilePart == nullptr);

			return detail::NormalizePath(FilePath(result, length), isDirectory);
		}

		FilePath VolumePath(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if (detail::IsResourcePath(path))
			{
				return FilePath();
			}

			wchar result[MAX_PATH];

			if (::GetVolumePathNameW(path.c_str(), result, _countof(result)) != 0)
			{
				// [Siv3D*TODO]
				return FilePath();
			}

			return FilePath(result).replaced(L'\\', L'/');
		}

		bool IsEmpty(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				HMODULE module = ::GetModuleHandleW(nullptr);

				if (HRSRC hrs = ::FindResourceW(module, (L'#' + path.substr(1)).c_str(), L"FILE"))
				{
					return ::SizeofResource(module, hrs) == 0;
				}
				else
				{
					return false;
				}
			}

			const auto fpath = fs::path(path.str());
			const auto status = fs::status(fpath);

			if (detail::IsNotFound(status))
			{
				// [Siv3D*TODO]
				return false;
			}
			else if (detail::IsRegular(status))
			{
				::WIN32_FILE_ATTRIBUTE_DATA fad;

				if (::GetFileAttributesExW(path.c_str(), ::GetFileExInfoStandard, &fad) == 0)
				{
					// [Siv3D*TODO]
					return false;
				}

				return fad.nFileSizeHigh == 0 && fad.nFileSizeLow == 0;	
			}
			else if (detail::IsDirectory(status))
			{
				return fs::directory_iterator(fpath) == fs::directory_iterator();
			}
			else
			{
				// [Siv3D*TODO]
				return false;
			}
		}

		int64 Size(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return 0;
			}

			if (detail::IsResourcePath(path))
			{
				return FileSize(path);
			}

			const auto fpath = fs::path(path.str());
			const auto status = fs::status(fpath);

			if (detail::IsRegular(status))
			{
				::WIN32_FILE_ATTRIBUTE_DATA fad;

				if (::GetFileAttributesExW(path.replaced(L'/', L'\\').c_str(), ::GetFileExInfoStandard, &fad) == 0)
				{
					// [Siv3D*TODO]
					return 0;
				}

				return (static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow;
			}
			else if (detail::IsDirectory(status))
			{
				return detail::DirectorySizeRecursive(FullPath(path));
			}
			else
			{
				// [Siv3D*TODO]
				return 0;
			}
		}

		int64 FileSize(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return 0;
			}

			if (detail::IsResourcePath(path))
			{
				HMODULE module = ::GetModuleHandleW(nullptr);

				if (HRSRC hrs = ::FindResourceW(module, (L'#' + path.substr(1)).c_str(), L"FILE"))
				{
					return ::SizeofResource(module, hrs);
				}
				else
				{
					return 0;
				}
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				// [Siv3D*TODO]
				return 0;
			}

			if (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return 0;
			}

			return (static_cast<uint64>(fad.nFileSizeHigh) << 32) + fad.nFileSizeLow;
		}

		Optional<DateTime> CreationTime(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return none;
			}

			if (detail::IsResourcePath(path))
			{
				return none;
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftCreationTime);
		}

		Optional<DateTime> WriteTime(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return none;
			}

			if (detail::IsResourcePath(path))
			{
				return none;
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastWriteTime);
		}

		Optional<DateTime> AccessTime(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return none;
			}

			if (detail::IsResourcePath(path))
			{
				return none;
			}

			::WIN32_FILE_ATTRIBUTE_DATA fad;

			if (::GetFileAttributesExW(path.c_str(), ::GetFileExInfoStandard, &fad) == 0)
			{
				return none;
			}

			return detail::FiletimeToTime(fad.ftLastAccessTime);
		}

		Array<FilePath> DirectoryContents(const FilePath& path, const bool recursive)
		{
			Array<FilePath> paths;

			if (path.isEmpty())
			{
				return paths;
			}

			if (detail::IsResourcePath(path))
			{
				return paths;
			}

			if (detail::IsRegular(fs::status(fs::path(path.str()))))
			{
				return paths;
			}

			detail::DirectoryContentsRecursive(FullPath(path), paths, recursive);

			return paths;
		}

		const FilePath& InitialPath()
		{
			return detail::init::g_initialPath;
		}

		const FilePath& ModulePath()
		{
			return detail::init::g_modulePath;
		}

		FilePath CurrentPath()
		{
			wchar result[1024];
			const DWORD length = ::GetCurrentDirectoryW(_countof(result), result);

			if (length == 0)
			{
				// [Siv3D*TODO]
				return FilePath();
			}
			else if (length > _countof(result))
			{
				// [Siv3D*TODO]
				return FilePath();
			}

			return detail::NormalizePath(FilePath(result, result + length), true);
		}

		FilePath SpecialFolderPath(const SpecialFolder folder)
		{
			constexpr int ids[] = {
				CSIDL_DESKTOP,
				CSIDL_MYDOCUMENTS,
				CSIDL_LOCAL_APPDATA,
				CSIDL_MYPICTURES,
				CSIDL_MYMUSIC,
				CSIDL_MYVIDEO
			};

			assert(static_cast<size_t>(folder) < _countof(ids));
			
			wchar path[MAX_PATH];

			if (FAILED(::SHGetFolderPathW(nullptr, ids[static_cast<size_t>(folder)], nullptr, 0, path)))
			{
				return FilePath();
			}

			return detail::NormalizePath(FilePath(path), true);
		}

		FilePath TempDirectoryPath()
		{
			wchar path[MAX_PATH];

			if (const auto length = ::GetTempPathW(MAX_PATH, path))
			{
				return detail::NormalizePath(FilePath(path, path + length), true);
			}
			else
			{
				return FilePath();
			}
		}

		//FilePath UniqueFilePath(const FilePath& directory)
		//{
		//	if (directory.isEmpty())
		//	{
		//		return FilePath();
		//	}

		//	if (!IsDirectory(directory))
		//	{
		//		return FilePath();
		//	}

		//	FilePath tempDirectory = FullPath(directory);

		//	if (tempDirectory.ends_with(L'/'))
		//	{
		//		tempDirectory.pop_back();
		//	}

		//	wchar path[MAX_PATH];

		//	if (::GetTempFileNameW(tempDirectory.c_str(), L"s3d", 0, path) == 0)
		//	{
		//		return FilePath();
		//	}
		//	
		//	return detail::NormalizePath(FilePath(path));
		//}

		bool Remove(const FilePath& path, const bool allowUndo)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				return false;
			}

			return detail::Remove(path, allowUndo);
		}
	}
}


# elif defined(SIV3D_TARGET_OSX)

# include <sys/stat.h>
# include <boost/filesystem.hpp>
# include <Siv3D/FileSystem.hpp>

bool trashFile(const char* path, unsigned long pathLength, bool isDirectory);
std::string specialFolder(int folder);

namespace s3d
{
    namespace fs = boost::filesystem;
    
    namespace detail
    {  
        static bool GetStat(const FilePath& path, struct stat& s)
        {
            return (::stat(path.replaced(L'\\', L'/').narrow().c_str(), &s) == 0);
        }

        static bool IsNotFound(const FilePath& path)
        {
            struct stat s;
            return !GetStat(path, s);
        }
        
        static bool IsRegular(const FilePath& path)
        {
            struct stat s;
            if (!GetStat(path, s))
            {
                return false;
            }
            
            return S_ISREG(s.st_mode);
        }

        static bool IsDirectory(const FilePath& path)
        {
            struct stat s;
            if (!GetStat(path, s))
            {
                return false;
            }

			return S_ISDIR(s.st_mode);
        }
        
        static FilePath NormalizePath(FilePath path, const bool skipDirectoryCheck = false)
        {
            for (auto& ch : path)
            {
                if (ch == L'\\')
                {
                    ch = L'/';
                }
            }
            
            if (!path.ends_with(L'/') && (skipDirectoryCheck || IsDirectory(path)))
            {
                path.push_back(L'/');
            }
            
            return path;
        }
        
        namespace init
        {
            const static FilePath g_initialPath = NormalizePath(fs::current_path().wstring());
            
            static FilePath g_modulePath;
            
            void SetModulePath(const FilePath& path)
            {
                g_modulePath = path;
            }
        }
    }
    
    namespace FileSystem
    {
        bool Exists(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return false;
            }
            
            return !detail::IsNotFound(path);
        }

        bool IsDirectory(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return false;
            }

			return detail::IsDirectory(path);
        }

        bool IsFile(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return false;
            }
            
			return detail::IsRegular(path);
        }

        bool IsResource(const FilePath&)
        {
            return false;
        }

        FilePath FullPath(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return path;
            }

            if (detail::IsNotFound(path))
            {
                return detail::NormalizePath(fs::weakly_canonical(fs::system_complete(fs::path(path.str()))).wstring());
            }
            else
            {
                return detail::NormalizePath(fs::canonical(fs::path(path.str())).wstring());
            }
        }
        
        FilePath VolumePath(const FilePath& path)
        {
            // [Siv3D*TODO]
            return FilePath(1, L'/');
        }
        
        bool IsEmpty(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return false;
            }

            struct stat s;
            if (!detail::GetStat(path, s))
            {
                return false;
            }
            
            if (S_ISREG(s.st_mode))
            {
                return s.st_size == 0;
            }
            else if (S_ISDIR(s.st_mode))
            {
                return fs::directory_iterator(fs::path(path.str())) == fs::directory_iterator();
            }
            else
            {
                // [Siv3D*TODO]
                return false;
            }
        }
        
        int64 Size(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return 0;
            }

            struct stat s;
            if (!detail::GetStat(path, s))
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
                
                for (const auto& v : fs::recursive_directory_iterator(path.str()))
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
                // [Siv3D*TODO]
                return 0;
            }
        }
        
        int64 FileSize(const FilePath& path)
        {
            if (path.isEmpty())
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
        
        Optional<DateTime> CreationTime(const FilePath& path)
        {
            struct stat s;
            if (!detail::GetStat(path, s))
            {
                return none;
            }
            
            auto tv = s.st_birthtimespec;
            ::tm lt;
            ::localtime_r(&tv.tv_sec, &lt);
            return DateTime((1900 + lt.tm_year), (1 + lt.tm_mon), (lt.tm_mday),
                            lt.tm_hour, lt.tm_min, lt.tm_sec, static_cast<int32>(tv.tv_nsec / (1000 * 1000)));
        }
        
        Optional<DateTime> WriteTime(const FilePath& path)
        {
            struct stat s;
            if (!detail::GetStat(path, s))
            {
                return none;
            }
            
            auto tv = s.st_mtimespec;
            ::tm lt;
            ::localtime_r(&tv.tv_sec, &lt);
            return DateTime((1900 + lt.tm_year), (1 + lt.tm_mon), (lt.tm_mday),
                            lt.tm_hour, lt.tm_min, lt.tm_sec, static_cast<int32>(tv.tv_nsec / (1000 * 1000)));
            
        }
        
        Optional<DateTime> AccessTime(const FilePath& path)
        {
            struct stat s;
            if (!detail::GetStat(path, s))
            {
                return none;
            }
            
            auto tv = s.st_atimespec;
            ::tm lt;
            ::localtime_r(&tv.tv_sec, &lt);
            return DateTime((1900 + lt.tm_year), (1 + lt.tm_mon), (lt.tm_mday),
                            lt.tm_hour, lt.tm_min, lt.tm_sec, static_cast<int32>(tv.tv_nsec / (1000 * 1000)));
        }
        
		Array<FilePath> DirectoryContents(const FilePath& path, const bool recursive)
		{
			Array<FilePath> paths;

			if (path.isEmpty())
			{
				return paths;
			}

			if (recursive)
			{
				for (const auto& v : fs::recursive_directory_iterator(path.str()))
				{
					paths.push_back(FullPath(v.path().wstring()));
				}
			}
			else
			{
				for (const auto& v : fs::directory_iterator(path.str()))
				{
					paths.push_back(FullPath(v.path().wstring()));
				}
			}

			return paths;
		}
               
		const FilePath& InitialPath()
        {
            return detail::init::g_initialPath;
        }
        
		const FilePath& ModulePath()
        {
            return detail::init::g_modulePath;
        }
           
        FilePath CurrentPath()
        {
            return detail::NormalizePath(fs::current_path().wstring());
        }
        
        FilePath SpecialFolderPath(const SpecialFolder folder)
        {
            return CharacterSet::Widen(specialFolder(static_cast<int>(folder)));
        }
        
        FilePath TempDirectoryPath()
        {
            return FilePath(fs::temp_directory_path().wstring());
        }

        bool Remove(const FilePath& path, const bool allowUndo)
        {
            if (path.isEmpty())
            {
                return false;
            }
            
            if (!allowUndo)
            {
                return std::remove(path.narrow().c_str()) == 0;
            }
            
            const std::string utf8Path = path.narrow();
            
            return trashFile(utf8Path.c_str(), utf8Path.length(), IsDirectory(path));
        }
    }
}

# endif

namespace s3d
{
    namespace FileSystem
    {
        String Extension(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return String();
            }
            
			# if defined(SIV3D_TARGET_WINDOWS)

				if (detail::IsResourcePath(path))
				{
					return String();
				}
			
			# endif
            
            const size_t dotPos = path.lastIndexOf(L'.');
            
            if (dotPos == String::npos)
            {
                return String();
            }
            
            const size_t sepPos = path.lastIndexOfAny(L"/\\");
            
            if (sepPos != String::npos && dotPos < sepPos)
            {
                return String();
            }
            
            return path.substr(dotPos + 1).lowercased();
        }
        
        String FileName(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return String();
            }
            
			# if defined(SIV3D_TARGET_WINDOWS)

				if (detail::IsResourcePath(path))
				{
					return String();
				}
			
			# endif
            
            const FilePath fullPath = FullPath(path);
            
            if (fullPath.isEmpty())
            {
                return String();
            }
            
            if (fullPath.ends_with(L'/'))
            {
                const size_t sepPos = fullPath.lastIndexOf(L'/', fullPath.length() - 2);
                
                if (sepPos == String::npos)
                {
                    return String(fullPath.begin(), fullPath.end() - 1);
                }
                else
                {
                    return String(fullPath.begin() + sepPos + 1, fullPath.end() - 1);
                }
            }
            else
            {
                const size_t sepPos = fullPath.lastIndexOf(L'/');
                
                if (sepPos == String::npos)
                {
                    return fullPath;
                }
                else
                {
                    return String(fullPath.begin() + sepPos + 1, fullPath.end());
                }
            }
        }
        
        String BaseName(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return String();
            }
            
			# if defined(SIV3D_TARGET_WINDOWS)

				if (detail::IsResourcePath(path))
				{
					return String();
				}
			
			# endif
            
            const FilePath fileName = FileName(path);
            
            const size_t dotPos = fileName.lastIndexOf(L'.');
            
            if (dotPos == String::npos)
            {
                return fileName;
            }
            
            return String(fileName.begin(), fileName.begin() + dotPos);
        }
        
        FilePath ParentPath(const FilePath& path, size_t level, FilePath* baseFullPath)
        {
            if (path.isEmpty())
            {
                return FilePath();
            }
            
			# if defined(SIV3D_TARGET_WINDOWS)

				if (detail::IsResourcePath(path))
				{
					return FilePath();
				}
			
			# endif
            
            FilePath result = FullPath(path);

			if (baseFullPath)
			{
				*baseFullPath = result;
			}
            
            if (result.ends_with(L'/'))
            {
                result.pop_back();
            }
            
            while (!result.isEmpty())
            {
                do
                {
                    result.pop_back();
                }
                while (!result.isEmpty() && !result.ends_with(L'/'));
                
                if (level-- == 0)
                {
                    break;
                }
            }
            
            return result;
        }

		// http://stackoverflow.com/questions/5772992/get-relative-path-from-two-absolute-paths
		FilePath RelativePath(const FilePath& _path, const FilePath& _start)
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

			# if defined(SIV3D_TARGET_WINDOWS)

				if (detail::IsResourcePath(path))
				{
					return path;
				}
			
			# endif

			if (path == start)
			{
				return L"./";
			}

			fs::path p(path.str()), base(start.str());
			fs::path from_path, from_base, output;
			fs::path::iterator path_it = p.begin(), path_end = p.end();
			fs::path::iterator base_it = base.begin(), base_end = base.end();

			# if defined(SIV3D_TARGET_WINDOWS)
            
				if (*path_it != *base_it)
				{
					return path;
				}

				++path_it, ++base_it;
			
            #endif

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

				++path_it, ++base_it;
			}

			return CharacterSet::Widen(output.string()).replace(L'\\', L'/');
		}

		bool CreateDirectories(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			# if defined(SIV3D_TARGET_WINDOWS)

				if (detail::IsResourcePath(path))
				{
					return false;
				}
			
			# endif

			try
			{
				if (fs::create_directories(fs::path(path.str())))
				{
					return true;
				}
				else
				{
					return true;
				}
			}
			catch (const fs::filesystem_error&)
			{
				return false;
			}
		}

		bool CreateParentDirectories(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			# if defined(SIV3D_TARGET_WINDOWS)

				if (detail::IsResourcePath(path))
				{
					return false;
				}
			
			# endif

			const FilePath parentDirectory = ParentPath(FullPath(path));

			if (!Exists(parentDirectory))
			{
				return CreateDirectories(parentDirectory);
			}

			return true;
		}
    }
}



