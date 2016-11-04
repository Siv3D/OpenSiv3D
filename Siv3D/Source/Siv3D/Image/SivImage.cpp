//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Image.hpp>

namespace s3d
{

}


//
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{


//

# pragma pack ( push, 1 )
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
	};
# pragma pack ( pop )

	bool Image::saveBMP(const FilePath& path) const
	{
		BinaryWriter writer(path);

		if (!writer)
		{
			return false;
		}

		const int32 width = m_width;
		const int32 height = m_height;
		const uint32 rowSize = width * 3 + width % 4;
		const uint32 bmpsize = rowSize * height;

		const BMPHeader hed =
		{
			0x4d42,
			static_cast<uint32>(bmpsize + sizeof(BMPHeader)),
			0,
			0,
			sizeof(BMPHeader),
			40,
			width,
			height,
			1,
			24,
			0,
			bmpsize,
			0,
			0,
			0,
			0
		};

		writer.write(hed);

		const Color* pSrcLine = operator[](height - 1);

		uint8* const line = static_cast<uint8*>(::calloc(rowSize, sizeof(uint8)));

		for (int32 y = 0; y < height; ++y)
		{
			uint8* pDst = line;
			const Color* pSrc = pSrcLine;

			for (int32 x = 0; x < width; ++x)
			{
				*pDst++ = pSrc->b;
				*pDst++ = pSrc->g;
				*pDst++ = pSrc->r;
				++pSrc;
			}

			writer.write(line, rowSize);

			pSrcLine -= width;
		}

		::free(line);

		return true;
	}
}
