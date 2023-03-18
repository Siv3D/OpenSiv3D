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

namespace s3d
{
# pragma pack (push, 1)

	struct TGAHeader
	{
		// Image ID length
		uint8  descLen;

		// Color map type
		uint8  cmapType;

		// Image type
		uint8  imageType;

		// Color map specification, First entry index
		uint16 cmapStart;

		// Color map specification, Color map length
		uint16 cmapEntries;

		// Color map specification, Color map entry size 
		uint8  cmapBits;
		
		// X-origin
		uint16 xOffset;

		// Y-origin
		uint16 yOffset;

		// Image width
		uint16 width;

		// Image height
		uint16 height;

		// Pixel depth
		uint8  bpp;

		// Image descriptor
		uint8  attrib;

		[[nodiscard]]
		static constexpr TGAHeader Make(int32 width, int32 height) noexcept
		{
			return
			{
				.descLen		= 0,
				.cmapType		= 0,
				.imageType		= 2,
				.cmapStart		= 0,
				.cmapEntries	= 0,
				.cmapBits		= 0,
				.xOffset		= 0,
				.yOffset		= 0,
				.width			= static_cast<uint16>(width),
				.height			= static_cast<uint16>(height),
				.bpp			= 32,
				.attrib			= 32,
			};
		}
	};

	static_assert(sizeof(TGAHeader) == 18);

# pragma pack (pop)
}
