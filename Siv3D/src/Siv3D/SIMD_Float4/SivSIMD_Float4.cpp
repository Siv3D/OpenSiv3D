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

# include <Siv3D/SIMD_Float4.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const SIMD_Float4& value)
	{
		alignas(16) float values[4];
		_mm_store_ps(values, value.vec);
		Formatter(formatData, Vec4(values[0], values[1], values[2], values[3]));
	}
}
