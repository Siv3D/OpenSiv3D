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

# pragma once
# include "Platform.hpp"
# if defined(SIV3D_TARGET_WINDOWS)

extern "C"
{
	_declspec(selectany) _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	_declspec(selectany) _declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

# endif
