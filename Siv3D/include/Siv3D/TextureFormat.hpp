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

# pragma once
# include "Fwd.hpp"
# include "StringView.hpp"

namespace s3d
{
	enum class TextureFormat
	{
		Unknown,

		// 32
		R8G8B8A8_Unorm,

		// 32
		R8G8B8A8_Unorm_SRGB,

		// 32
		R16G16_Float,

		// 32
		R32_Float,

		// 32
		R10G10B10A2_Unorm,

		// 32
		R11G11B10_UFloat,

		// 64
		R16G16B16A16_Float,

		// 64
		R32G32_Float,

		// 128
		R32G32B32A32_Float,
	};

	struct TextureFormatProperty
	{
		StringView name;

		int32 DXGIFormat;

		int32 GLInternalFormat;

		int32 GLFormat;

		int32 GLType;
		
		// 1 ピクセル当たりのサイズ
		uint32 pixelSize;

		// チャンネル数
		uint32 num_channels;
		
		bool isSRGB;
	};

	[[nodiscard]] const TextureFormatProperty& GetTextureFormatProperty(TextureFormat textureFormat);

	[[nodiscard]] StringView ToString(TextureFormat textureFormat) noexcept;
}
