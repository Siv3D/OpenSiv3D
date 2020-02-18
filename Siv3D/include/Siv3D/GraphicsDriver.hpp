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
# if SIV3D_PLATFORM(WINDOWS)

extern "C"
{
# if defined(SIV3D_WINDOWS_D3D_DRIVER_TYPE_REFERENCE)
	_declspec(selectany) int Siv3D_D3DDriverType = 3;
# elif defined(SIV3D_WINDOWS_D3D_DRIVER_TYPE_WARP)
	_declspec(selectany) int Siv3D_D3DDriverType = 2;
# elif defined(SIV3D_WINDOWS_D3D_DRIVER_TYPE_HARDWARE_FAVOR_INTEGRATED)
	_declspec(selectany) int Siv3D_D3DDriverType = 1;
# else
	_declspec(selectany) int Siv3D_D3DDriverType = 0;
# endif
}

# endif
