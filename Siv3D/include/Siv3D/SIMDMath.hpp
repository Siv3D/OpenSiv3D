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
# include "Common.hpp"
# include "FormatData.hpp"

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

namespace s3d
{
#if defined(_XM_SSE_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)

    using aligned_float4 = __m128;

#elif defined(_XM_ARM_NEON_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
    
    using aligned_float4 = float32x4_t;

#else
    
    using aligned_float4 = DirectX::__vector4;

#endif

# define SIV3D_VECTOR_CALL XM_CALLCONV

    void Formatter(FormatData& formatData, aligned_float4 value);
}
