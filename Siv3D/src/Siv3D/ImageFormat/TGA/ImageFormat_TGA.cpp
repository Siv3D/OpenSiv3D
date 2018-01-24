//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "ImageFormat_TGA.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
# pragma pack (push, 1)

	struct TGAHeader
	{
		uint8  descLen;
		uint8  cmapType;
		uint8  imageType;
		uint16 cmapStart;
		uint16 cmapEntries;
		uint8  cmapBits;
		uint16 xOffset;
		uint16 yOffset;
		uint16 width;
		uint16 height;
		uint8  bpp;
		uint8  attrib;
	};

# pragma pack (pop)

	ImageFormat ImageFormat_TGA::format() const
	{
		return ImageFormat::TGA;
	}

	const Array<String>& ImageFormat_TGA::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"tga" };

		return extensions;
	}

	bool ImageFormat_TGA::isHeader(const uint8(&)[16]) const
	{
		// [Siv3D TODO]
		return false;
	}

	Size ImageFormat_TGA::getSize(const IReader& reader) const
	{
		TGAHeader hed;

		const size_t offset = offsetof(TGAHeader, bpp);

		if (offset != reader.lookahead(&hed, offset))
		{
			return{ 0, 0 };
		}

		return{ hed.width, hed.height };
	}

	Image ImageFormat_TGA::decode(IReader& reader) const
	{
		TGAHeader hed;

		if (!reader.read(hed))
		{
			return Image();
		}

		if (hed.bpp == 8 || hed.bpp == 16)
		{
			return Image();
		}

		if (hed.bpp != 24 && hed.bpp != 32)
		{
			return Image();
		}

		if (hed.descLen)
		{
			reader.setPos(reader.getPos() + hed.descLen);
		}

		const int32 width = hed.width;
		const int32 height = hed.height;

		const int32 pixelSize = hed.bpp / 8;
		const int32 size = width * height*pixelSize;

		uint8* readPixels = static_cast<uint8*>(::malloc(size));
		reader.read(readPixels, size);

		Image image(width, height);

		switch (hed.bpp)
		{
		case 24:
		{
			const bool reversed = !(hed.attrib & 0x20);
			Color* pLine = image[reversed ? height - 1 : 0];
			const uint8* pSrc = &readPixels[0];
			int32 step = reversed ? -width : width;

			for (int32 y = 0; y < height; ++y)
			{
				Color* pDst = pLine;

				for (int32 x = 0; x < width; ++x)
				{
					pDst->set(pSrc[2], pSrc[1], pSrc[0]);
					pSrc += 3;
					++pDst;
				}

				pLine += step;
			}

			break;
		}
		case 32:
		{
			const bool reversed = !(hed.attrib & 0x20);
			Color* pLine = image[reversed ? height - 1 : 0];
			const uint8* pSrc = &readPixels[0];
			int32 step = reversed ? -width : width;

			for (int y = 0; y < height; ++y)
			{
				Color* pDst = pLine;

				for (int32 x = 0; x < width; ++x)
				{
					pDst->set(pSrc[2], pSrc[1], pSrc[0], pSrc[3]);
					pSrc += 4;
					++pDst;
				}

				pLine += step;
			}

			break;
		}
		}

		::free(readPixels);

		return image;
	}

	bool ImageFormat_TGA::encode(const Image& image, IWriter& writer) const
	{
		const size_t width = image.width();
		const size_t height = image.height();
		const size_t stride = image.stride();

		const TGAHeader hed =
		{
			0,
			0,
			2,
			0,
			0,
			0,
			0,
			0,
			static_cast<uint16>(width),
			static_cast<uint16>(height),
			32,
			32,
		};

		writer.write(hed);

		uint8* line = static_cast<uint8*>(::malloc(stride));

		const Color* pSrc = image[0];

		for (size_t y = 0; y < height; ++y)
		{
			::memcpy(line, pSrc, stride);

			size_t index = 0;

			for (size_t x = 0; x < width; ++x)
			{
				std::swap(line[index], line[index + 2]);

				index += 4;
			}

			writer.write(line, stride);

			pSrc += width;
		}

		::free(line);

		return true;
	}

	bool ImageFormat_TGA::save(const Image& image, const FilePath& path) const
	{
		BinaryWriter writer(path);
			
		return encode(image, writer);
	}
}
