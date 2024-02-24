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

# include <Siv3D/ImageFormat/BMPDecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include "BMPHeader.hpp"

namespace s3d
{
	StringView BMPDecoder::name() const
	{
		return U"BMP"_sv;
	}

	ImageFormat BMPDecoder::imageFormat() const noexcept
	{
		return ImageFormat::BMP;
	}

	bool BMPDecoder::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 signature[] = { 0x42, 0x4d };

		return (std::memcmp(bytes, signature, sizeof(signature)) == 0);
	}

	const Array<String>& BMPDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"bmp" };

		return extensions;
	}

	Optional<ImageInfo> BMPDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> BMPDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		BMPHeader header;

		if (const size_t offset = offsetof(BMPHeader, biPlanes);
			offset != reader.lookahead(&header, offset))
		{
			LOG_FAIL(U"❌ BMPDecoder::getImageInfo(): Offset is invalid");
			return{};
		}

		const Size size(header.biWidth, std::abs(header.biHeight));

		ImagePixelFormat pixelFormat = ImagePixelFormat::R8G8B8;

		if (header.biBitCount == 32)
		{
			pixelFormat = ImagePixelFormat::R8G8B8X8;
		}

		return ImageInfo{ size, ImageFormat::BMP, pixelFormat, false };
	}

	Image BMPDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image BMPDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"BMPDecoder::decode()");

		BMPHeader header;

		if (not reader.read(header))
		{
			LOG_FAIL(U"❌ BMPDecoder::decode(): Failed to read header");
			return{};
		}

		if (header.biSize != 40)
		{
			LOG_FAIL(U"❌ BMPDecoder::decode(): BMPHeader::biSize != 40");
			return{};
		}

		if (header.biCompression)
		{
			LOG_FAIL(U"❌ BMPDecoder::decode(): Compressed BMP is not supported");
			return{};
		}

		const bool reverse	= (header.biHeight > 0);
		const int32 width	= header.biWidth;
		const int32 height	= reverse ? header.biHeight : -header.biHeight;

		if (not InRange<int32>(width, 1, Image::MaxWidth)
			|| not InRange<int32>(height, 1, Image::MaxHeight))
		{
			LOG_FAIL(U"BMPDecoder::decode(): Image size {}x{} is not supported"_fmt(
				width, height));
			return{};
		}

		const uint32 paletteSize = ((header.biBitCount > 8) ? 0 : (header.biClrUsed == 0) ? (1 << header.biBitCount) : header.biClrUsed);
		Array<uint8> paletteOwner(paletteSize * 4);
		const auto palette = paletteOwner.data();

		if (paletteSize)
		{
			reader.read(palette, paletteOwner.size());
		}

		if (header.bfOffBits > (sizeof(header) + paletteOwner.size()))
		{
			reader.setPos(header.bfOffBits);
		}

		Image image(width, height);

		LOG_VERBOSE(U"BMPHeader::biBitCount: {}"_fmt(header.biBitCount));

		switch (const int32 depth = header.biBitCount)
		{
		case 1:
			{
				const uint32 rowSize = ((width + 31) / 32 * 4);
				const int32 lineStep = reverse ? -width : width;
				Color* pDstLine = image[reverse ? height - 1 : 0];

				Array<uint8> bufferOwner(rowSize * 4);
				const auto buffer = bufferOwner.data();

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
					Color* pDst = pDstLine;

					for (int32 x = 0; x < width; x += 8)
					{
						const int32 n = Min(8, (width - x));

						for (int32 i = 0; i < n; ++i)
						{
							const size_t index = ((*tmp >> (7 - i)) & 1);
							const uint8* src = (palette + (index << 2));

							pDst++->set(src[2], src[1], src[0]);
						}

						++tmp;
					}

					pDstLine += lineStep;
				}

				break;
			}
		case 4:
			{
				const uint32 rowSize = ((width + 7) / 8 * 4);
				const int32 lineStep = reverse ? -width : width;
				Color* pDstLine = image[reverse ? height - 1 : 0];

				Array<uint8> bufferOwner(rowSize * 4);
				const auto buffer = bufferOwner.data();

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
					Color* pDst = pDstLine;
					const int32 w = (width - 1);

					for (int32 x = 0; x < w; x += 2)
					{
						const size_t index1 = ((*tmp >> 4) & 0x0f);
						const size_t index2 = (*tmp & 0x0f);
						const uint8* src1 = (palette + (index1 << 2));
						const uint8* src2 = (palette + (index2 << 2));

						pDst++->set(src1[2], src1[1], src1[0]);
						pDst++->set(src2[2], src2[1], src2[0]);

						++tmp;
					}

					if (width & 1)
					{
						const size_t index = ((*tmp >> 4) & 0x0f);
						const uint8* src = (palette + (index << 2));

						pDst++->set(src[2], src[1], src[0]);
					}

					pDstLine += lineStep;
				}

				break;
			}
		case 8:
			{
				const uint32 rowSize = width + (width % 4 ? 4 - width % 4 : 0);
				const int32 lineStep = reverse ? -width : width;
				Color* pDstLine = image[reverse ? height - 1 : 0];

				Array<uint8> bufferOwner(rowSize * 4);
				const auto buffer = bufferOwner.data();

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

				break;
			}
		case 16:
			{
				const size_t rowSize16 = ((width + 1) / 2 * 2);
				const size_t rowSize = (rowSize16 * 2);
				const int32 lineStep = reverse ? -width : width;
				Color* pDstLine = image[reverse ? height - 1 : 0];

				Array<uint16> bufferOwner(rowSize16 * 4);
				const auto buffer = bufferOwner.data();

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
					uint16* pSrc = &buffer[rowSize16 * (y % 4)];

					for (Color* pDst = pDstLine; pDst != pDstEnd; ++pDst)
					{
						uint32 b = ((*pSrc & 0x001f) << 3);
						uint32 g = ((*pSrc & 0x07e0) >> 2);
						uint32 r = ((*pSrc & 0xf800) >> 7);

						pDst->set(r, g, b);

						++pSrc;
					}

					pDstLine += lineStep;
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

				Array<uint8> bufferOwner(rowSize * 4);
				const auto buffer = bufferOwner.data();

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

				break;
			}
		default:
			{
				LOG_FAIL(U"❌ BMPDecoder::decode(): BMPHeader::biBitCount is invalid");
				return{};
			}
		}

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
