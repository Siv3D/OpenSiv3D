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

		R8G8B8A8_Unorm,

		R8G8B8A8_Unorm_SRGB,
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
