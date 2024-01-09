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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ConstantBuffer.hpp>

namespace s3d
{
	struct VS2DQuadWarp
	{
		std::array<Float4, 3> homography;
	};

	struct PS2DQuadWarp
	{
		std::array<Float4, 3> invHomography;
		Float4 uvTransform;
	};

	struct EngineShaderConstantBuffer
	{
		ConstantBuffer<VS2DQuadWarp> vs2DQuadWarp;

		ConstantBuffer<PS2DQuadWarp> ps2DQuadWarp;
	};
}
