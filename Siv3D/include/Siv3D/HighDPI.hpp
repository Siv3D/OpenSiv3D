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

# pragma once
# include "Platform.hpp"
# if defined(SIV3D_TARGET_WINDOWS)

extern "C"
{
# if defined(SIV3D_WINDOWS_HIGH_DPI)
	_declspec(selectany) int Siv3DHighDPIAwareness = 1;
# else
	_declspec(selectany) int Siv3DHighDPIAwareness = 0;
# endif
}

# endif
