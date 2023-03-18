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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/UUIDValue.hpp>

namespace s3d
{
	namespace FileSystem
	{
		String Extension(const FilePathView path)
		{
			if (not path)
			{
				return{};
			}

			if constexpr (Platform::HasEmbeddedResource)
			{
				if (IsResourcePath(path))
				{
					return{};
				}
			}

			const size_t dotPos = path.lastIndexOf(U'.');

			if (dotPos == String::npos)
			{
				return{};
			}

			const size_t sepPos = path.lastIndexOfAny(U"/\\");

			if ((sepPos != String::npos) && (dotPos < sepPos))
			{
				return{};
			}

			return String{ path.substr(dotPos + 1) }.lowercase();
		}

		String FileName(const FilePathView path)
		{
			if (not path)
			{
				return{};
			}

			if constexpr (Platform::HasEmbeddedResource)
			{
				if (IsResourcePath(path))
				{
					return{};
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
				return{};
			}

			const size_t dotPos = fileName.lastIndexOf(U'.');

			if (dotPos == String::npos)
			{
				return fileName;
			}

			return String(fileName.begin(), fileName.begin() + dotPos);
		}

		FilePath ParentPath(const FilePathView path, const size_t level)
		{
			FilePath unused;
			return ParentPath(path, level, unused);
		}

		FilePath ParentPath(const FilePathView path, size_t level, FilePath& baseFullPath)
		{
			if (not path)
			{
				return{};
			}

			if constexpr (Platform::HasEmbeddedResource)
			{
				if (IsResourcePath(path))
				{
					baseFullPath.clear();

					return{};
				}
			}

			FilePath result = FullPath(path);

			baseFullPath = result;

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

		FilePath UniqueFilePath(const FilePathView directory)
		{
			if (FileSystem::IsFile(directory))
			{
				return{};
			}

			FilePath directoryPath{ directory };

			if (directoryPath && (not directoryPath.ends_with(U'/')))
			{
				directoryPath.push_back(U'/');
			}

			for (;;)
			{
				const FilePath path = (directoryPath + UUIDValue::Generate().str() + U".tmp");

				if (not Exists(path))
				{
					return path;
				}
			}
		}
	}
}
