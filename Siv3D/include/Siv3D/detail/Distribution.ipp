//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

# if defined(__clang__)
	_Pragma("clang diagnostic push")
	_Pragma("clang diagnostic ignored \"-Wshorten-64-to-32\"")
# endif

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(6001)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(6294)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(26495)
# include <ThirdParty/absl/random/distributions.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_CLANG_WARNINGS_POP()
