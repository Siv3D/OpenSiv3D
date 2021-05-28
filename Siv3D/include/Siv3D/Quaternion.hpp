//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "SIMD_Float4.hpp"

namespace s3d
{
	struct alignas(16) Quaternion
	{
		SIMD_Float4 vec = { 0.0f, 0.0f, 0.0f, 1.0f };


	};
}

# include "detail/Quaternion.ipp"
