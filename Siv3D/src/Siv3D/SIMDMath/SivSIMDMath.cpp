//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/SIMDMath.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const aligned_float4 value)
	{
		DirectX::XMFLOAT4A t;

		DirectX::XMStoreFloat4A(&t, value);
		
		Formatter(formatData, Float4{ t.x, t.y, t.z, t.w });
	}
}
