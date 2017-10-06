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
# include <Siv3D/String.hpp>
# include <Siv3D/System.hpp>
# include "../Siv3DEngine.hpp"
# include "../System/ISystem.hpp"
# include "../Window/IWindow.hpp"
# include "../Audio/IAudio.hpp"
# include "../EngineDirectory/EngineDirectory.hpp"

namespace s3d
{
	namespace System
	{
		bool Update(bool clearGraphics)
		{
			if (!Siv3DEngine::GetSystem()->update(clearGraphics))
			{
				Siv3DEngine::GetWindow()->show(false);

				Siv3DEngine::GetAudio()->fadeMasterVolume();

				return false;
			}

			return true;
		}

		void Exit()
		{
			Siv3DEngine::GetSystem()->reportEvent(WindowEvent::ExitFlag);
		}

		void SetExitEvent(const uint32 windowEventFlag)
		{
			Siv3DEngine::GetSystem()->setExitEvent(windowEventFlag);
		}

		uint32 GetPreviousEvent()
		{
			return Siv3DEngine::GetSystem()->getPreviousEvent();
		}
		
		double DeltaTime(const double maxDuration)
		{
			return std::min(Siv3DEngine::GetSystem()->getDeltaTime(), maxDuration);
		}

		int32 FrameCount()
		{
			return Siv3DEngine::GetSystem()->getUserFrameCount();
		}

		void SetFrameCount(const int32 count)
		{
			Siv3DEngine::GetSystem()->setUserFrameCount(count);
		}

		void ShowLicenses()
		{
			LaunchBrowser(EngineDirectory::LicensePath());
		}
	}
}

# if defined(SIV3D_TARGET_WINDOWS)

# ifndef NOMINMAX
#	define  NOMINMAX
# endif
# ifndef STRICT
#	define  STRICT
# endif
# ifndef _WIN32_WINNT
#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
# endif
# ifndef NTDDI_VERSION
#	define  NTDDI_VERSION NTDDI_WIN7
# endif
# include <Windows.h>
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

			// システムクロックの精度を上げる
			::timeBeginPeriod(1);

			::Sleep(milliseconds);

			::timeEndPeriod(1);
		}

		bool LaunchBrowser(const FilePath& url)
		{
			// Web 上のコンテンツもしくは HTML ファイルでなければ処理を返す
			if (!url.starts_with(S3DSTR("http://")) && !url.starts_with(S3DSTR("https://")))
			{
				const String extension = FileSystem::Extension(url);

				if (extension != S3DSTR("html") && extension != S3DSTR("htm"))
				{
					return false;
				}		
			}

			return reinterpret_cast<size_t>(::ShellExecuteW(nullptr, S3DWSTR("open"), url.c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32;
		}
	}
}

# elif defined(SIV3D_TARGET_MACOS)

# include <unistd.h>
# include <Siv3D/FileSystem.hpp>

bool macOS_LaunchBrowser(const char* url);

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
			FilePath url = _url;
			
			if (!url.starts_with(S3DSTR("http://")) && !url.starts_with(S3DSTR("https://")))
			{
				const String extension = FileSystem::Extension(url);
				
				if (extension != S3DSTR("html") && extension != S3DSTR("htm"))
				{
					return false;
				}
				
				url.insert(0, S3DSTR("file://"));
			}
			
			return macOS_LaunchBrowser(url.narrow().c_str());
		}
	}
}

# elif defined(SIV3D_TARGET_LINUX)

# include <stdlib.h>
# include <unistd.h>
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
			FilePath url = _url;
			
			if (!url.starts_with(S3DSTR("http://")) && !url.starts_with(S3DSTR("https://")))
			{
				const String extension = FileSystem::Extension(url);
				
				if (extension != S3DSTR("html") && extension != S3DSTR("htm"))
				{
					return false;
				}
				
				url.insert(0, S3DSTR("file://"));
			}

			if (system("which xdg-open >/dev/null 2>&1"))
			{
				//There isn't xdg-open command.
				return false;
			}

			String command = S3DSTR("xdg-open ");
			command += url;
			command += S3DSTR(" >/dev/null 2>&1");
			if (system(command.narrow().c_str()) == 0)
			{
				return true;
			}
			return false;
		}
	}
}

# endif
