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

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	namespace System
	{
		void Sleep(const int32 milliseconds)
		{
			if (milliseconds < 0)
			{
				return;
			}

			// システムクロックの精度を上げる
			::timeBeginPeriod(1);
			{
				::Sleep(milliseconds);
			}
			::timeEndPeriod(1);
		}

		bool LaunchBrowser(const FilePathView _url)
		{
			String url{ _url };
			const bool isWebPage = url.starts_with(U"http://")
				|| url.starts_with(U"https://");

			if (not isWebPage)
			{
				const String extension = FileSystem::Extension(_url);
				const bool isHTML = (extension == U"html") || (extension == U"htm");

				if (not isHTML)
				{
					return false;
				}

				url = (U"file://" + FileSystem::FullPath(_url));
			}

			return reinterpret_cast<size_t>(::ShellExecuteW(nullptr, L"open", url.toWstr().c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32;
		}

		bool ShowInFileManager(const FilePathView path)
		{
			const FilePath fullPath = FileSystem::FullPath(path);

			if (FileSystem::IsFile(fullPath))
			{
				const String param = U"/select," + fullPath.replaced(U'/', U'\\');

				return (reinterpret_cast<int64>(::ShellExecuteW(nullptr, L"open", L"explorer.exe", param.toWstr().c_str(), nullptr, SW_SHOWNORMAL)) > 32);
			}
			else if (FileSystem::IsDirectory(fullPath))
			{
				return (reinterpret_cast<int64>(::ShellExecuteW(nullptr, L"explore", fullPath.toWstr().c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32);
			}

			return false;
		}
	}
}
