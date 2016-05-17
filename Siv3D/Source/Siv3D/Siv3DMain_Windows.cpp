//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <crtdbg.h>
# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>
# include "Siv3DEngine.hpp"
# include "Logger/ILogger.hpp"

void Main();

namespace s3d
{
	namespace detail
	{
		namespace init
		{
			void SetModulePath();
		}
	}
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int)
{
	using namespace s3d;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	detail::init::SetModulePath();
	{
		int nArgs = 0;

		LPWSTR* szArglist = ::CommandLineToArgvW(::GetCommandLineW(), &nArgs);

		if (nArgs >= 2 && FileSystem::Exists(szArglist[1]))
		{
			::SetCurrentDirectoryW(FileSystem::ParentPath(FileSystem::ModulePath()).c_str());
		}

		::LocalFree(szArglist);
	}

	::OutputDebugStringW(L"Siv3D for Windows\n");

	Siv3DEngine engine;

	if (!engine.GetLogger()->init())
	{
		return -1;
	}

	Main();

	return 0;
}

# endif
