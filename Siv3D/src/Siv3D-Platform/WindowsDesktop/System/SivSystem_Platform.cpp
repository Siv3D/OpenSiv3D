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

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Windows.hpp>

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

			::Sleep(milliseconds);

			::timeEndPeriod(1);
		}

		bool LaunchBrowser(const FilePath& url)
		{
			const bool isWebPage = url.starts_with(U"http://") || url.starts_with(U"https://");

			// Web 上のコンテンツもしくは HTML ファイルでなければ処理を返す
			if (!isWebPage)
			{
				const String extension = FileSystem::Extension(url);

				if (extension != U"html" && extension != U"htm")
				{
					return false;
				}
			}

			return reinterpret_cast<size_t>(::ShellExecuteW(nullptr, L"open", url.toWstr().c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32;
		}
	}
}
