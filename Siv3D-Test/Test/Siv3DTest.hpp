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

# pragma once
# include <Siv3D.hpp>

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)
	# ifdef _DEBUG
		# pragma comment (lib, "Windows(x64)/gtest/gtest_d")
	# else
		# pragma comment (lib, "Windows(x64)/gtest/gtest")
	# endif
# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)
	# ifdef _DEBUG
		# pragma comment (lib, "Windows(x86)/gtest/gtest_d")
	# else
		# pragma comment (lib, "Windows(x86)/gtest/gtest")
	# endif
# endif

namespace s3d
{
	void RunTest();
}
