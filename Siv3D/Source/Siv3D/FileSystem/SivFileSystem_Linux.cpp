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
# if defined(SIV3D_TARGET_LINUX)

# include <sys/stat.h>
# include <stdlib.h>
# include <string>
# include <boost/filesystem.hpp>
# include <glib-2.0/glib.h>
# include <glib-2.0/gio/gio.h>
# include <Siv3D/FileSystem.hpp>

using namespace s3d;

std::string Linux_SpecialFolder(const int folder)
{
	const GUserDirectory folders[] = {
		G_USER_DIRECTORY_DESKTOP,
		G_USER_DIRECTORY_DOCUMENTS,
		G_USER_DIRECTORY_DOCUMENTS, //dummy
		G_USER_DIRECTORY_PICTURES,
		G_USER_DIRECTORY_MUSIC,
		G_USER_DIRECTORY_VIDEOS
	};

	std::string sf_path = "";
	if(folder == static_cast<int>(SpecialFolder::LocalAppData))
	{
		char* xch = getenv("XDG_CACHE_HOME");
		if(xch == NULL)
		{
			sf_path = getenv("HOME");
			sf_path += "/.cache";
		}
		else
			sf_path = xch;
	}
	else
		sf_path = g_get_user_special_dir(folders[folder]);

	return sf_path;
} 

bool Linux_TrashFile(const char* path)
{
	gboolean ret;
	GFile* gf = g_file_new_for_path(path);
	GError* ge;

	ret = g_file_trash(gf, nullptr, &ge);

	if(ge)
		g_error_free(ge);
	g_object_unref(gf);

	if(!ret)
		return false;

	return true;
}

/*
	bool Linux_TrashFile(const char* path);
	std::string Linux_SpecialFolder(int folder);
	*/

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
			static const FilePath resourcePath = FileSystem::ModulePath() + L"/resources/";

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

			auto tv = s.st_ctim;

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

			auto tv = s.st_mtim;

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
			auto tv = s.st_atim;

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
			return CharacterSet::Widen(Linux_SpecialFolder(static_cast<int>(folder))) << L'/';
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

			return Linux_TrashFile(utf8Path.c_str());
		}
	}
}

# endif
