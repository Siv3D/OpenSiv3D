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
		int32 DXGIFormat;
		
		uint32 pixelSize;

		uint32 num_channels;
		
		bool isSRGB;
	};

	[[nodiscard]] const TextureFormatProperty& GetTextureFormatProperty(TextureFormat format);
}
