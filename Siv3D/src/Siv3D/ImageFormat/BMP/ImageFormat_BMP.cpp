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

# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include "ImageFormat_BMP.hpp"

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
	};

	static_assert(sizeof(BMPHeader) == 54);

# pragma pack (pop)

	ImageFormat ImageFormat_BMP::format() const
	{
		return ImageFormat::BMP;
	}

	const Array<String>& ImageFormat_BMP::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"bmp" };

		return extensions;
	}

	bool ImageFormat_BMP::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 signature[] = { 0x42, 0x4d };

		return std::memcmp(bytes, signature, sizeof(signature)) == 0;
	}

	Size ImageFormat_BMP::getSize(const IReader& reader) const
	{
		BMPHeader hed;

		const size_t offset = offsetof(BMPHeader, biPlanes);

		if (offset != reader.lookahead(&hed, offset))
		{
			return{ 0, 0 };
		}

		return{ hed.biWidth, std::abs(hed.biHeight) };
	}

	Image ImageFormat_BMP::decode(IReader& reader) const
	{
		Image image;

		BMPHeader hed;
			
		if (!reader.read(hed))
		{
			return image;
		}

		if (hed.biSize != 40 || hed.biCompression)
		{
			return image;
		}

		const bool reverse	= hed.biHeight > 0;
		const int32 width	= hed.biWidth;
		const int32 height	= reverse ? hed.biHeight : -hed.biHeight;

		if (!InRange<int32>(width, 1, Image::MaxWidth)
			|| !InRange<int32>(height, 1, Image::MaxHeight))
		{
			return image;
		}

		image.resize(width, height);

		switch (const int32 depth = hed.biBitCount)
		{
		case 8:
			{
				uint8 palette[1024];			
				reader.read(palette);

				const uint32 rowSize = width + (width % 4 ? 4 - width % 4 : 0);
				const int32 lineStep = reverse ? -width : width;
				Color* pDstLine = image[reverse ? height - 1 : 0];
				
				if (uint8 * const buffer = static_cast<uint8*>(std::malloc(rowSize * 4)))
				{
					for (int32 y = 0; y < height; ++y)
					{
						if (height - y < 4)
						{
							reader.read(buffer, rowSize * (height - y));
						}
						else if (y % 4 == 0)
						{
							reader.read(buffer, rowSize * 4);
						}

						uint8* tmp = &buffer[rowSize * (y % 4)];
						const Color* const pDstEnd = pDstLine + width;

						for (Color* pDst = pDstLine; pDst != pDstEnd; ++pDst)
						{
							const uint8* src = palette + (static_cast<size_t>(*tmp++) << 2);

							pDst->set(src[2], src[1], src[0]);
						}

						pDstLine += lineStep;
					}

					std::free(buffer);
				}

				break;
			}
		case 24:
		case 32:
			{
				const size_t rowSize = depth == 24 ? width * 3 + width % 4 : width * 4;			
				const int32 depthBytes = depth / 8;
				const int32 lineStep = reverse ? -width : width;
				Color* pDstLine = image[reverse ? height - 1 : 0];

				if (uint8 * const buffer = static_cast<uint8*>(std::malloc(rowSize * 4)))
				{
					for (int32 y = 0; y < height; ++y)
					{
						if (height - y < 4)
						{
							reader.read(buffer, rowSize * (height - y));
						}
						else if (y % 4 == 0)
						{
							reader.read(buffer, rowSize * 4);
						}

						const Color* const pDstEnd = pDstLine + width;
						uint8* pSrc = &buffer[rowSize * (y % 4)];

						for (Color* pDst = pDstLine; pDst != pDstEnd; ++pDst)
						{
							pDst->set(pSrc[2], pSrc[1], pSrc[0]);

							pSrc += depthBytes;
						}

						pDstLine += lineStep;
					}

					std::free(buffer);
				}

				break;
			}
		}

		return image;
	}

	bool ImageFormat_BMP::encode(const Image& image, IWriter& writer) const
	{
		if (!writer.isOpened())
		{
			return false;
		}

		const int32 width		= image.width();
		const int32 height		= image.height();
		const uint32 rowSize	= width * 3 + width % 4;
		const uint32 bmpsize	= rowSize * height;

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

		const Color* pSrcLine = image[height - 1];

		if (uint8 * const line = static_cast<uint8*>(std::calloc(rowSize, sizeof(uint8))))
		{
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

			std::free(line);
		}

		return true;
	}

	bool ImageFormat_BMP::save(const Image& image, const FilePath& path) const
	{
		BinaryWriter writer(path);
			
		return encode(image, writer);
	}
}
