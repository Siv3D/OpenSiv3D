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

# include <Siv3D/PlatformDetail.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace detail
	{
		inline constexpr bool IsResourcePath(const FilePathView path)
		{
			return path.starts_with(U'/');
		}
	}

	namespace FileSystem
	{
		String Extension(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return String();
			}

			if constexpr(Platform::HasEmbeddedResource)
			{
				if (detail::IsResourcePath(path))
				{
					return String();
				}
			}

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

			return String(path.substr(dotPos + 1)).lowercase();
		}

		String FileName(const FilePathView path)
		{
			if (path.isEmpty())
			{
				return String();
			}

			if constexpr (Platform::HasEmbeddedResource)
			{
				if (detail::IsResourcePath(path))
				{
					return String();
				}
			}

			if (path.ends_with(U'/'))
			{
				const size_t sepPos = path.lastIndexOf(U'/', path.length() - 2);

				if (sepPos == String::npos)
				{
					return String(path.begin(), path.end() - 1);
				}
				else
				{
					return String(path.begin() + sepPos + 1, path.end() - 1);
				}
			}
			else
			{
				const size_t sepPos = path.lastIndexOf(U'/');

				if (sepPos == String::npos)
				{
					return String(path);
				}
				else
				{
					return String(path.begin() + sepPos + 1, path.end());
				}
			}
		}

		String BaseName(const FilePathView path)
		{
			const String fileName = FileName(path);

			if (fileName.isEmpty())
			{
				return String();
			}

			const size_t dotPos = fileName.lastIndexOf(U'.');

			if (dotPos == String::npos)
			{
				return fileName;
			}

			return String(fileName.begin(), fileName.begin() + dotPos);
		}

		FilePath ParentPath(const FilePathView path, size_t level, FilePath * const baseFullPath)
		{
			if (path.isEmpty())
			{
				return FilePath();
			}

			if constexpr (Platform::HasEmbeddedResource)
			{
				if (detail::IsResourcePath(path))
				{
					return String();
				}
			}

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
	}
}
