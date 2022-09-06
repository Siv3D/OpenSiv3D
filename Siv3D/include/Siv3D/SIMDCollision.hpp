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
# include "Platform.hpp"

# if SIV3D_INTRINSIC(SSE)
    # define _XM_SSE4_INTRINSICS_
# endif

# if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wunused-but-set-variable"
# endif
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4459)
# include <ThirdParty/DirectXMath/DirectXMath.h>
# include <ThirdParty/DirectXMath/DirectXCollision.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# ifdef __GNUC__
#	pragma GCC diagnostic pop
# endif

 # if !SIV3D_PLATFORM(WINDOWS)
    # undef __in
    # undef __out
    # undef __valid
# endif
