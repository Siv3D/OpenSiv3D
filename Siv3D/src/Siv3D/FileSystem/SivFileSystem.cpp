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
		String Extension(FilePathView path)
		{
			if (path.isEmpty())
			{
				return{};
			}

			while (path.starts_with(U'.'))
			{
				path.remove_prefix(1);
			}

			const size_t lastDotPos = path.lastIndexOf(U'.');

			if (lastDotPos == String::npos)
			{
				return{};
			}

			const size_t lastSeparatorPos = path.lastIndexOfAny(U"/\\");

			// aaa.bbb/ccc のようなケースを弾く
			if ((lastSeparatorPos != String::npos)
				&& (lastDotPos < lastSeparatorPos))
			{
				return{};
			}

			return String{ path.substr(lastDotPos + 1) }.lowercase();
		}

		String FileName(const FilePathView path_)
		{
			if (path_.isEmpty())
			{
				return{};
			}

			FilePath path = FilePath{ path_ }.replace(U'\\', U'/');

			if (path.ends_with(U'/'))
			{
				return{};
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

			if ((dotPos == 0) || (dotPos == (fileName.size() - 1)))
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
