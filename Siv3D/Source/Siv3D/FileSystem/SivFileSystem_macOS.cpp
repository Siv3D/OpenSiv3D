//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <sys/stat.h>
# include <Siv3D/FileSystem.hpp>
# include <boost/filesystem.hpp>

bool macOS_TrashFile(const char* path, unsigned long pathLength, bool isDirectory);
std::string macOS_SpecialFolder(int folder);

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

		bool IsResource(const FilePath& path)
		{
			static const FilePath resourcePath = FileSystem::ModulePath() + S3DSTR("/Contents/Resources/");
			
			return path.starts_with(resourcePath) && Exists(path);
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

			if (path.isEmpty() || !IsDirectory(path))
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
			return CharacterSet::Widen(macOS_SpecialFolder(static_cast<int>(folder))) << L'/';
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

			return macOS_TrashFile(utf8Path.c_str(), utf8Path.length(), IsDirectory(path));
		}
	}
}

# endif
