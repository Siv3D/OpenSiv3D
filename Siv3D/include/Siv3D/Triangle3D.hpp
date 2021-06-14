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

namespace s3d
{
	struct Triangle3D
	{
		SIMD_Float4 p0;

		SIMD_Float4 p1;

		SIMD_Float4 p2;


	};
}

# include "detail/Triangle3D.ipp"
