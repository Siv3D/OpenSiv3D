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
# include "../Siv3DEngine.hpp"
# include "../System/ISystem.hpp"

namespace s3d
{
	namespace System
	{
		bool Update()
		{
			return Siv3DEngine::GetSystem()->update();
		}
	}
}

# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
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

			::timeBeginPeriod(1);

			::Sleep(milliseconds);

			::timeEndPeriod(1);
		}

		bool LaunchBrowser(const FilePath& url)
		{
			if (!url.starts_with(L"http://") && !url.starts_with(L"https://"))
			{
				const String extension = FileSystem::Extension(url);

				if (extension != L"html" && extension != L"htm")
				{
					return false;
				}		
			}

			return reinterpret_cast<size_t>(::ShellExecuteW(nullptr, L"open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32;
		}
	}
}

# elif defined(SIV3D_TARGET_MACOS)

# include <unistd.h>

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

		bool LaunchBrowser(const FilePath& url)
		{

			return false;
		}
	}
}

# endif
