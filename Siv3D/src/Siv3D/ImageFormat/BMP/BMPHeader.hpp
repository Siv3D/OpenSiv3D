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

	struct BMPHeader
	{
		uint16 bfType;
		uint32 bfSize;
		uint16 bfReserved1;
		uint16 bfReserved2;
		uint32 bfOffBits;
		uint32 biSize;
		int32  biWidth;
		int32  biHeight;
		uint16 biPlanes;
		uint16 biBitCount;
		uint32 biCompression;
		uint32 biSizeImage;
		int32  biXPelsPerMeter;
		int32  biYPelsPerMeter;
		uint32 biClrUsed;
		uint32 biClrImportant;
		
		[[nodiscard]]
		static constexpr BMPHeader Make(int32 width, int32 height, uint32 size_bytes) noexcept
		{
			return
			{
				.bfType				= 0x4d42,
				.bfSize				= static_cast<uint32>(sizeof(BMPHeader) + size_bytes),
				.bfReserved1		= 0,
				.bfReserved2		= 0,
				.bfOffBits			= sizeof(BMPHeader),
				.biSize				= 40,
				.biWidth			= width,
				.biHeight			= height,
				.biPlanes			= 1,
				.biBitCount			= 24,
				.biCompression		= 0,
				.biSizeImage		= size_bytes,
				.biXPelsPerMeter	= 0,
				.biYPelsPerMeter	= 0,
				.biClrUsed			= 0,
				.biClrImportant		= 0
			};
		}
	};

	static_assert(sizeof(BMPHeader) == 54);

# pragma pack (pop)
}
