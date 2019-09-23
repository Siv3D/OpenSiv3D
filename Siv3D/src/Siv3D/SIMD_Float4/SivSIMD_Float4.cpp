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
		SIMD::Float4A fv;

		fv.vec = value.vec;

		Formatter(formatData, Vec4(fv.f[0], fv.f[1], fv.f[2], fv.f[3]));
	}
}
