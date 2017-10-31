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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Random.hpp>

# if defined(SIV3D_TARGET_WINDOWS)

	# include <filesystem>
	namespace fs = std::experimental::filesystem;

# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

	# include <boost/filesystem.hpp>
	namespace fs = boost::filesystem;

# endif

namespace s3d
{
	namespace detail
	{
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

	# if defined(SIV3D_TARGET_WINDOWS)

		bool IsResourcePath(const FilePath& path);

	# endif
	}

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

			const size_t dotPos = path.lastIndexOf(U'.');

			if (dotPos == String::npos)
			{
				return String();
			}

			const size_t sepPos = path.lastIndexOfAny(U"/\\");

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

			if (fullPath.ends_with(U'/'))
			{
				const size_t sepPos = fullPath.lastIndexOf(U'/', fullPath.length() - 2);

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
				const size_t sepPos = fullPath.lastIndexOf(U'/');

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

			const size_t dotPos = fileName.lastIndexOf(U'.');

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

			if (result.ends_with(U'/'))
			{
				result.pop_back();
			}

			while (!result.isEmpty())
			{
				do
				{
					result.pop_back();
				} while (!result.isEmpty() && !result.ends_with(U'/'));

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
				return U"./";
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

		# endif

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

			return Unicode::Widen(output.string()).replace(U'\\', U'/');
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

		FilePath UniqueFilePath(const FilePath& directory)
		{
			HardwareRNG rng;
			UniformDistribution<uint64> ud(0, UINT64_MAX);

			FilePath directoryPath = directory;

			if (!directoryPath.isEmpty() && !directoryPath.ends_with(L'/'))
			{
				directoryPath.push_back(L'/');
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
	}
}
