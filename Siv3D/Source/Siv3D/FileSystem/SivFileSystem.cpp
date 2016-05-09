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

# include "../../../Include/Siv3D/Fwd.hpp"

# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <filesystem>
# include "../../../Include/Siv3D/FileSystem.hpp"

namespace s3d
{
	namespace fs = std::experimental::filesystem;

	namespace detail
	{
		static bool IsResourcePath(const FilePath& path)
		{	
			// [Siv3D*TODO]
			path;
			return false;
		}

		static bool DirectoryExists(const FilePath& path)
		{
			const DWORD attr = ::GetFileAttributesW(path.c_str());
			
			return (attr != -1) && (attr & FILE_ATTRIBUTE_DIRECTORY);
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

			if (!path.ends_with(L'/') && (skipDirectoryCheck || DirectoryExists(path)))
			{
				path.push_back(L'/');
			}

			return path;
		}

		const static FilePath InitialPath = NormalizePath(fs::current_path().wstring());
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
				// [Siv3D*TODO]
				return false;
			}

			return fs::exists(fs::path(path.str()));
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

			return detail::DirectoryExists(path);
		}

		bool IsFile(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(path))
			{
				// [Siv3D*TODO]
				return false;
			}

			return fs::is_regular_file(fs::path(path.str()));
		}

		bool IsResource(const FilePath& path)
		{
			// [Siv3D*TODO]
			path;
			return false;
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

		String Extension(const FilePath& path)
		{
			if (path.isEmpty())
			{
				return String();
			}

			if (detail::IsResourcePath(path))
			{
				return String();
			}

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

			if (detail::IsResourcePath(path))
			{
				return path;
			}

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

			if (detail::IsResourcePath(path))
			{
				return path;
			}

			const FilePath fileName = FileName(path);

			const size_t dotPos = fileName.lastIndexOf(L'.');

			if (dotPos == String::npos)
			{
				return fileName;
			}

			return String(fileName.begin(), fileName.begin() + dotPos);
		}

		FilePath InitialPath()
		{
			return detail::InitialPath;
		}

		FilePath CurrentPath()
		{
			return detail::NormalizePath(fs::current_path().wstring());
		}
	}
}


# elif defined(SIV3D_TARGET_OSX)

# include <sys/stat.h>
# include <boost/filesystem.hpp>
# include "../../../Include/Siv3D/FileSystem.hpp"

namespace s3d
{
    namespace fs = boost::filesystem;
    
    namespace detail
    {
        static bool IsResourcePath(const FilePath&)
        {
            // [Siv3D*TODO]
            return false;
        }

        static bool DirectoryExists(const FilePath& path)
        {
			struct stat s;
			if (::stat(path.replaced(L'\\', L'/').narrow().c_str(), &s) != 0)
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
            
            if (!path.ends_with(L'/') && (skipDirectoryCheck || DirectoryExists(path)))
            {
                path.push_back(L'/');
            }
            
            return path;
        }
        
        const static FilePath InitialPath = NormalizePath(fs::current_path().wstring());
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
                // [Siv3D*TODO]
                return false;
            }
            
            struct stat s;
            return (::stat(path.replaced(L'\\', L'/').narrow().c_str(), &s) == 0);
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
            
			return detail::DirectoryExists(path);
        }

        bool IsFile(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return false;
            }
            
            if (detail::IsResourcePath(path))
            {
                return false;
            }
            
            struct stat s;
            if(::stat(path.replaced(L'\\', L'/').narrow().c_str(), &s) != 0)
            {
                return false;
            }
            
            return S_ISREG(s.st_mode);
        }

        bool IsResource(const FilePath&)
        {
            // [Siv3D*TODO]
            return false;
        }
/*
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
            const DWORD length = ::GetFullPathNameW(path.c_str(), std::size(result), result, &pFilePart);
            
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
        
        String Extension(const FilePath& path)
        {
            if (path.isEmpty())
            {
                return String();
            }
            
            if (detail::IsResourcePath(path))
            {
                return String();
            }
            
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
            
            if (detail::IsResourcePath(path))
            {
                return path;
            }
            
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
            
            if (detail::IsResourcePath(path))
            {
                return path;
            }
            
            const FilePath fileName = FileName(path);
            
            const size_t dotPos = fileName.lastIndexOf(L'.');
            
            if (dotPos == String::npos)
            {
                return fileName;
            }
            
            return String(fileName.begin(), fileName.begin() + dotPos);
        }
*/
        FilePath InitialPath()
        {
            return detail::InitialPath;
        }
   
        FilePath CurrentPath()
        {
            return detail::NormalizePath(fs::current_path().wstring());
        }
    }
}

# endif
