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

# include <sys/stat.h>
# include <stdlib.h>
# include <string>
# include <boost/filesystem.hpp>
# include <glib-2.0/glib.h>
# include <glib-2.0/gio/gio.h>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/Distribution.hpp>
# include <Siv3D/HardwareRNG.hpp>

using namespace s3d;

namespace s3d
{
	namespace fs = boost::filesystem;
	
	namespace detail
	{
		std::string Linux_SpecialFolder(const int folder)
		{
			const GUserDirectory folders[] =
			{
				G_USER_DIRECTORY_DESKTOP,
				G_USER_DIRECTORY_DOCUMENTS,
				G_USER_DIRECTORY_DOCUMENTS, //dummy
				G_USER_DIRECTORY_PICTURES,
				G_USER_DIRECTORY_MUSIC,
				G_USER_DIRECTORY_VIDEOS,
				G_USER_DIRECTORY_DOCUMENTS, //dummy (System fonts)
				G_USER_DIRECTORY_DOCUMENTS, //dummy (Local fonts)
				G_USER_DIRECTORY_DOCUMENTS, //dummy (User fonts)
			};

			std::string sf_path = "";
			if (folder == static_cast<int>(SpecialFolder::LocalAppData))
			{
				const char *xch = getenv("XDG_CACHE_HOME");
				if (xch == nullptr)
				{
					sf_path = getenv("HOME");
					sf_path += "/.cache";
				}
				else
				{
					sf_path = xch;
				}
			}
			else
			{
				sf_path = g_get_user_special_dir(folders[folder]);
			}

			return sf_path;
		}

		bool Linux_TrashFile(const char* path)
		{
			GFile* gf = g_file_new_for_path(path);
			GError* ge;

			gboolean ret = g_file_trash(gf, nullptr, &ge);

			if (ge)
			{
				g_error_free(ge);
			}
			g_object_unref(gf);

			if(!ret)
			{
				return false;
			}

			return true;
		}

		static bool GetStat(const FilePathView path, struct stat& s)
		{
			return (::stat(FilePath(path).replaced(U'\\', U'/').narrow().c_str(), &s) == 0);
		}

		static bool IsNotFound(const FilePathView path)
		{
			struct stat s;
			return !GetStat(path, s);
		}

		static bool IsRegular(const FilePathView path)
		{
			struct stat s;
			if (!GetStat(path, s))
			{
				return false;
			}

			return S_ISREG(s.st_mode);
		}

		static bool IsDirectory(const FilePathView path)
		{
			struct stat s;
			if (!GetStat(path, s))
			{
				return false;
			}

			return S_ISDIR(s.st_mode);
		}

		static bool IsResourcePath(const FilePathView path)
		{
			static const FilePath resourcePath = FileSystem::ModulePath() + U"/resources/";

			return path.starts_with(resourcePath);
		}

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

		bool CopyDirectory(const fs::path& source, const fs::path& destination)
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

					if (boost::filesystem::is_directory(current))
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

		namespace init
		{
			const static FilePath g_initialPath = NormalizePath(Unicode::Widen(fs::current_path().string()));

			static FilePath g_modulePath;

			void SetModulePath(const FilePath& path)
			{
				g_modulePath = path;
			}
		}
	}

	namespace FileSystem
	{
		bool Exists(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			return !detail::IsNotFound(path);
		}

		bool IsDirectory(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			return detail::IsDirectory(path);
		}

		bool IsFile(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			return detail::IsRegular(path);
		}

		bool IsResource(const FilePathView path)
		{
			const FilePath resourcePath = FileSystem::ModulePath() + U"/resources/";

			return Exists(path) && path.starts_with(resourcePath);
		}

		FilePath FullPath(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if (detail::IsNotFound(path))
			{
				return detail::NormalizePath(Unicode::Widen(fs::weakly_canonical(fs::system_complete(fs::path(Unicode::ToWString(path)))).string()));
			}
			else
			{
				return detail::NormalizePath(Unicode::Widen(fs::canonical(fs::path(Unicode::ToWString(path))).string()));
			}
		}

		Platform::NativeFilePath NativePath(const FilePathView path)
		{
			// [Siv3D ToDo]
			return "";
		}

		FilePath VolumePath(const FilePathView)
		{
			// [Siv3D ToDo]
			return FilePath(1, U'/');
		}

		bool IsEmptyDirectory(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			const FilePath src(path);
			struct stat s;
			if (!detail::GetStat(path, s))
			{
				return false;
			}

			if (S_ISREG(s.st_mode))
			{
				return false;
			}
			else if (S_ISDIR(s.st_mode))
			{
				return fs::directory_iterator(fs::path(src.toWstr())) == fs::directory_iterator();
			}
			else
			{
				// [Siv3D ToDo]
				return false;
			}
		}

		int64 Size(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return 0;
			}

			struct stat s;
			if (!detail::GetStat(FilePath(path), s))
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

				for (const auto& v : fs::recursive_directory_iterator(Unicode::ToWString(path)))
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
				// [Siv3D ToDo]
				return 0;
			}
		}

		int64 FileSize(const FilePathView path)
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

		Optional<DateTime> CreationTime(const FilePathView path)
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

		Optional<DateTime> WriteTime(const FilePathView path)
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

		Optional<DateTime> AccessTime(const FilePathView path)
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

			if (path.isEmpty() || !IsDirectory(path))
			{
				return paths;
			}

			if (recursive)
			{
				for (const auto& v : fs::recursive_directory_iterator(Unicode::ToWString(path)))
				{
					paths.push_back(FullPath(Unicode::Widen(v.path().string())));
				}
			}
			else
			{
				for (const auto& v : fs::directory_iterator(Unicode::ToWString(path)))
				{
					paths.push_back(FullPath(Unicode::Widen(v.path().string())));
				}
			}

			return paths;
		}

		const FilePath& InitialDirectory()
		{
			return detail::init::g_initialPath;
		}

		const FilePath& ModulePath()
		{
			return detail::init::g_modulePath;
		}

		FilePath CurrentDirectory()
		{
			return detail::NormalizePath(Unicode::Widen(fs::current_path().string()));
		}

		/*
		bool ChangeCurrentDirectory(const FilePathView path)
		{

		}
		*/

		FilePath SpecialFolderPath(const SpecialFolder folder)
		{
			return Unicode::Widen(detail::Linux_SpecialFolder(static_cast<int>(folder))) << U'/';
		}

		FilePath TemporaryDirectoryPath()
		{
			return Unicode::Widen(fs::temp_directory_path().string());
		}

		FilePath UniqueFilePath(const FilePathView directory)
		{
			HardwareRNG rng;
			UniformDistribution<uint64> ud(0, UINT64_MAX);

			FilePath directoryPath(directory);

			if (!directoryPath.isEmpty() && !directoryPath.ends_with(U'/'))
			{
				directoryPath.push_back(U'/');
			}

			for (uint64 n = ud(rng);; ++n)
			{
				const FilePath path = directoryPath + detail::ToUniqueFileName(n) + U".tmp";

				if (!Exists(path))
				{
					return path;
				}
			}
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
			if (path.isEmpty())
			{
				return false;
			}

			try
			{
				if (fs::create_directories(fs::path(Unicode::ToWString(path))))
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

		bool CreateParentDirectories(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return false;
			}

			const FilePath parentDirectory = ParentPath(FullPath(path));

			if (!Exists(parentDirectory))
			{
				return CreateDirectories(parentDirectory);
			}

			return true;
		}

		bool Copy(const FilePathView from, const FilePathView _to, const CopyOption copyOption)
		{
			if (from.isEmpty() || _to.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(from) || detail::IsResourcePath(_to))
			{
				return false;
			}

			const bool exists = !detail::IsNotFound(_to);

			if (copyOption == CopyOption::None && exists)
			{
				return false;
			}
			else if (copyOption == CopyOption::SkipExisting && exists)
			{
				return true;
			}

			FilePath to(_to);

			CreateParentDirectories(to);

			if (IsFile(from))
			{
				const fs::copy_option option =
					copyOption == CopyOption::OverwriteExisting ? fs::copy_option::overwrite_if_exists
					: fs::copy_option::fail_if_exists;

				try
				{
					fs::copy_file(fs::path(Unicode::ToWString(from)), fs::path(to.toWstr()), option);
				}
				catch (const fs::filesystem_error&)
				{
					return false;
				}
			}
			else
			{
				return detail::CopyDirectory(fs::path(Unicode::ToWString(from)), fs::path(to.toWstr()));
			}

			return true;
		}

		bool Remove(const FilePathView path, const bool allowUndo)
		{
			if (path.isEmpty())
			{
				return false;
			}

			if (!allowUndo)
			{
				return std::remove(Unicode::Narrow(path).c_str()) == 0;
			}

			const std::string utf8Path = Unicode::Narrow(path);

			return detail::Linux_TrashFile(utf8Path.c_str());
		}

		bool RemoveContents(const FilePathView path, const bool allowUndo)
		{
			if (!IsDirectory(path))
			{
				return false;
			}

			if (!Remove(path, allowUndo))
			{
				return false;
			}

			return CreateDirectories(path);
		}

		bool Rename(const FilePathView from, const FilePathView to)
		{
			if (from.isEmpty() || to.isEmpty())
			{
				return false;
			}

			if (detail::IsResourcePath(from) || detail::IsResourcePath(to))
			{
				return false;
			}

			boost::system::error_code ec;
			fs::rename(fs::path(Unicode::ToWString(from)), fs::path(Unicode::ToWString(to)), ec);

			return (ec.value() == 0);
		}

		bool IsSandBoxed()
		{
			return false;
		}
	}
}
