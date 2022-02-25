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

namespace s3d
{
	enum class TexturePixelFormat : uint8
	{
		Unknown,

		// 32-bit
		R8G8B8A8_Unorm,

		// 32-bit
		R8G8B8A8_Unorm_SRGB,

		// 32-bit
		R16G16_Float,

		// 32-bit
		R32_Float,

		// 32-bit
		R10G10B10A2_Unorm,

		// 32-bit
		R11G11B10_UFloat,

		// 64-bit
		R16G16B16A16_Float,

		// 64-bit
		R32G32_Float,

		// 128-bit
		R32G32B32A32_Float,
	};
}
