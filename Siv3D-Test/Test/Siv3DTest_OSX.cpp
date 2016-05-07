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
# if defined (SIV3D_TARGET_OSX)

# include <Siv3D.hpp>
# include <gtest/gtest.h>

namespace s3d
{
	void RunTest()
	{
		int nArgs = 1;
		wchar_t unused = L'\0';
		wchar_t* pUnused = &unused;

		testing::InitGoogleTest(&nArgs, &pUnused);
		(void)RUN_ALL_TESTS();
	}
}

# endif
