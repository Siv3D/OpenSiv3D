//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace System
	{
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

				url = FileSystem::FullPath(_url);
			}

			if (std::system("which xdg-open >/dev/null 2>&1") != 0)
			{
				// xdg-open command not found
				return false;
			}

			String command = U"xdg-open ";
			command += (U'\"' + url + U'\"');
			command += U" >/dev/null 2>&1";

			return (std::system(command.narrow().c_str()) == 0);
		}
	}
}
