//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <conio.h>
# include <gtest/gtest.h>
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D.hpp>

namespace s3d
{
	void RunTest()
	{
		FILE* out = nullptr;
		FILE* in = nullptr;
		::AllocConsole();
		::freopen_s(&out, "CONOUT$", "w", stdout);
		::freopen_s(&in, "CONIN$", "r", stdin);
		std::wcout.imbue(std::locale(""));
		std::wcin.imbue(std::locale(""));

		int nArgs = 1;
		wchar_t unused = L'\0';
		wchar_t* pUnused = &unused;

		testing::InitGoogleTest(&nArgs, &pUnused);
		RUN_ALL_TESTS();

		std::wcout << "Press Any Key to Exit.\n";
		_getch();

		if (out)
		{
			::fclose(out);
			out = nullptr;
		}

		if (in)
		{
			::fclose(in);
			in = nullptr;
		}

		::FreeConsole();
	}
}

# endif
