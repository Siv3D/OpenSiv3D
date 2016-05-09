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
# include "Platform.hpp"

/// <summary>
/// Siv3D のバージョン | Version of Siv3D
/// </summary>
# define Siv3DVersion L"0.0.3"

/// <summary>
/// Siv3D のバージョン ID | Version ID of Siv3D
/// </summary>
# define Siv3DVersionID 200'000'003

/// <summary>
/// ターゲットプラットフォーム | Platform target
/// </summary>
# if   defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)
	# define Siv3DPlatform	L"WindowsDesktop-x64"
# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)
	# define Siv3DPlatform	L"WindowsDesktop-x86"
# elif defined(SIV3D_TARGET_OSX)
	# define Siv3DPlatform	L"OSX"
# else
	# error	
# endif
