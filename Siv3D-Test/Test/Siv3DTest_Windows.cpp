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

# include "Siv3DTest.hpp"

# if defined(SIV3D_DO_TEST) && defined(SIV3D_TARGET_WINDOWS)

# include <conio.h>
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

namespace s3d
{
	void RunTest()
	{
		Console.open();

		int nArgs = 1;
		wchar_t unused = L'\0';
		wchar_t* pUnused = &unused;

		testing::InitGoogleTest(&nArgs, &pUnused);
		RUN_ALL_TESTS();
	}
}

# endif
