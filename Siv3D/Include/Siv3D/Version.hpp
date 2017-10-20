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
# include "Types.hpp"

/// <summary>
/// Siv3D のバージョン | Version of Siv3D
/// </summary>
# define Siv3DVersion S3DSTR("0.1.6")

/// <summary>
/// Siv3D のバージョン ID | Version ID of Siv3D
/// </summary>
# define Siv3DVersionID 200'001'006

/// <summary>
/// ターゲットプラットフォーム | Platform target
/// </summary>
# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	# define Siv3DPlatform	S3DSTR("WindowsDesktop-x64")

# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

	# define Siv3DPlatform	S3DSTR("WindowsDesktop-x86")

# elif defined(SIV3D_TARGET_MACOS)

	# define Siv3DPlatform	S3DSTR("macOS")

# elif defined(SIV3D_TARGET_LINUX)

	# define Siv3DPlatform	S3DSTR("Linux")

# else

	# error	

# endif
