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

# include <Siv3D/ImageFormat/TGADecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include "TGAHeader.hpp"

namespace s3d
{
	StringView TGADecoder::name() const
	{
		return U"TGA"_sv;
	}

	ImageFormat TGADecoder::imageFormat() const noexcept
	{
		return ImageFormat::TGA;
	}

	bool TGADecoder::isHeader(const uint8(&)[16]) const
	{
		// [Siv3D TODO]
		return false;
	}

	const Array<String>& TGADecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"tga" };

		return extensions;
	}

	Optional<ImageInfo> TGADecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> TGADecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		TGAHeader header;

		if (not reader.lookahead(header))
		{
			LOG_FAIL(U"❌ TGADecoder::getImageInfo(): Failed to load the header");
			return{};
		}

		const Size size{ header.width, header.height };
		
		ImagePixelFormat pixelFormat = ImagePixelFormat::Unknown;

		if (header.imageType == 2)
		{
			if (header.bpp == 24)
			{
				pixelFormat = ImagePixelFormat::R8G8B8X8;
			}
			else if (header.bpp == 32)
			{
				pixelFormat = ImagePixelFormat::R8G8B8A8;
			}
		}

		return ImageInfo{ size, ImageFormat::TGA, pixelFormat, false };
	}

	Image TGADecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image TGADecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"TGADecoder::decode()");

		TGAHeader header;
			
		if (not reader.read(header))
		{
			return{};
		}

		if ((header.bpp != 24)
			&& (header.bpp != 32))
		{
			return{};
		}

		if (header.descLen)
		{
			reader.setPos(reader.getPos() + header.descLen);
		}

		const int32 width		= header.width;
		const int32 height		= header.height;
		const int32 pixelSize	= (header.bpp / 8);
		const int32 data_bytes	= width * height * pixelSize;
		const bool reversed		= !(header.attrib & 0x20);

		uint8* readPixels = static_cast<uint8*>(std::malloc(data_bytes));

		if (not readPixels)
		{
			return{};
		}

		reader.read(readPixels, data_bytes);

		Image image{ Size{ width, height }, Color{ 255 } };

		switch (header.bpp)
		{
		case 24:
			{
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
				Color* pLine = image[reversed ? height - 1 : 0];
				const uint8* pSrc = &readPixels[0];
				int32 step = reversed ? -width : width;

				for (int32 y = 0; y < height; ++y)
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

		std::free(readPixels);

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
