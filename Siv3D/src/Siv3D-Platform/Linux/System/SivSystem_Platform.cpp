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

# include <stdlib.h>
# include <unistd.h>
# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace System
	{
		void Sleep(int32 milliseconds)
		{
			if (milliseconds < 0)
			{
				return;
			}
			
			::usleep(static_cast<uint32>(milliseconds) * 1000);
		}
		
		bool LaunchBrowser(const FilePath& _url)
		{
			const bool isWebPage = _url.starts_with(U"http://") || _url.starts_with(U"https://");
			FilePath url = _url;
			
			if (!isWebPage)
			{
				const String extension = FileSystem::Extension(_url);
				
				if (extension != U"html" && extension != U"htm")
				{
					return false;
				}
				
				url.insert(0, U"file://");
			}
			
			if (system("which xdg-open >/dev/null 2>&1"))
			{
				//There isn't xdg-open command.
				return false;
			}

			String command = U"xdg-open ";
			command += url;
			command += U" >/dev/null 2>&1";

			if (system(command.narrow().c_str()) == 0)
			{
				return true;
			}

			return false;
		}
	}
}
