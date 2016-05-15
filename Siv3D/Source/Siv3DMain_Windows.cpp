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

void Main();

namespace s3d
{
	namespace detail
	{
		void OutputLicense();
	}
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, wchar_t*, int)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		int nArgs = 0;

		LPWSTR* szArglist = ::CommandLineToArgvW(::GetCommandLineW(), &nArgs);

		if (nArgs >= 2 && s3d::FileSystem::Exists(szArglist[1]))
		{
			::SetCurrentDirectoryW(s3d::FileSystem::ParentPath(s3d::FileSystem::ModulePath()).c_str());
		}

		::LocalFree(szArglist);
	}

	::OutputDebugStringW(L"Siv3D for Windows\n");

	Main();

	s3d::detail::OutputLicense();

	return 0;
}

# endif
