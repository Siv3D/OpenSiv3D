﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)
# include <png.h>
# else
# include "../../../ThirdParty/libpng/png.h"
# endif

# include "ImageFormat_PNG.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	static void PngReadCallback(png_structp png_ptr, png_bytep buf, png_size_t length)
	{
		const auto reader = static_cast<IReader*>(::png_get_io_ptr(png_ptr));

		reader->read(buf, length);
	}

	static void PngWriteCallback(png_structp png_ptr, png_bytep buf, png_size_t length)
	{
		const auto writer = static_cast<IWriter*>(::png_get_io_ptr(png_ptr));

		writer->write(buf, length);
	}

	ImageFormat ImageFormat_PNG::format() const
	{
		return ImageFormat::PNG;
	}

	const Array<String>& ImageFormat_PNG::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"png" };

		return extensions;
	}

	bool ImageFormat_PNG::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 signature[] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };

		return ::memcmp(bytes, signature, sizeof(signature)) == 0;
	}

	Size ImageFormat_PNG::getSize(const IReader& reader) const
	{
		uint8 buf[24];

		if (!reader.lookahead(buf))
		{
			return{ 0, 0 };
		}

		if (buf[12] != 'I' || buf[13] != 'H' || buf[14] != 'D' || buf[15] != 'R')
		{
			return{ 0, 0 };
		}

		const int32 width	= (buf[16] << 24) + (buf[17] << 16) + (buf[18] << 8) + (buf[19] << 0);
		const int32 height	= (buf[20] << 24) + (buf[21] << 16) + (buf[22] << 8) + (buf[23] << 0);

		return{ width, height };
	}

	Image ImageFormat_PNG::decode(IReader& reader) const
	{
		Image image;

		png_structp png_ptr = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if (!png_ptr)
		{
			return image;
		}

		png_infop info_ptr = ::png_create_info_struct(png_ptr);

		if (!info_ptr)
		{
			::png_destroy_read_struct(&png_ptr, nullptr, nullptr);

			return image;
		}

		::png_set_read_fn(png_ptr, &reader, PngReadCallback);

		::png_read_info(png_ptr, info_ptr);

		png_uint_32 width = 4, height = 4;

		int iBitDepth, iColorType;

		::png_get_IHDR(png_ptr, info_ptr, &width, &height, &iBitDepth, &iColorType, nullptr, nullptr, nullptr);

		if (iColorType == PNG_COLOR_TYPE_PALETTE)
		{
			::png_set_palette_to_rgb(png_ptr);
		}

		if (::png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			::png_set_tRNS_to_alpha(png_ptr);
		}

		if (iColorType == PNG_COLOR_TYPE_GRAY && iBitDepth < 8)
		{
			::png_set_expand_gray_1_2_4_to_8(png_ptr);
		}

		if (iBitDepth == 16)
		{
			::png_set_scale_16(png_ptr);
		}

		if (iBitDepth < 8)
		{
			::png_set_packing(png_ptr);
		}

		if (iColorType == PNG_COLOR_TYPE_GRAY || iColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
		{
			::png_set_gray_to_rgb(png_ptr);
		}

		::png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);

		double dGamma;

		if (::png_get_gAMA(png_ptr, info_ptr, &dGamma))
		{
			::png_set_gamma(png_ptr, 2.2, dGamma);
		}

		::png_read_update_info(png_ptr, info_ptr);

		const int nChannels = ::png_get_channels(png_ptr, info_ptr);

		::png_get_IHDR(png_ptr, info_ptr, &width, &height, &iBitDepth, &iColorType, nullptr, nullptr, nullptr);

		image.resize(width, height);

		uint8* pixels = image.dataAsUint8();

		Array<uint8*> ppbRowPointers(height);

		for (size_t i = 0; i < height; ++i)
		{
			ppbRowPointers[i] = pixels + i * width * nChannels;
		}

		::png_read_image(png_ptr, ppbRowPointers.data());

		::png_read_end(png_ptr, nullptr);

		::png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

		return image;
	}

	bool ImageFormat_PNG::encode(const Image& image, IWriter& writer) const
	{
		return encode(image, writer, PNGFilter::Default);
	}

	bool ImageFormat_PNG::encode(const Image& image, IWriter& writer, const uint32 filterFlag) const
	{
		if (!writer.isOpened())
		{
			return false;
		}

		png_structp png_ptr = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if (!png_ptr)
		{
			return false;
		}

		png_infop info_ptr = ::png_create_info_struct(png_ptr);

		if (!info_ptr)
		{
			::png_destroy_write_struct(&png_ptr, nullptr);

			return false;
		}

		::png_set_write_fn(png_ptr, &writer, PngWriteCallback, nullptr);

		const png_uint_32 width = image.width();

		const png_uint_32 height = image.height();

		::png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		::png_set_filter(png_ptr, 0, filterFlag);

		::png_write_info(png_ptr, info_ptr);

		const uint8* pRow = image.dataAsUint8();

		for (uint32 y = 0; y < height; ++y)
		{
			::png_write_row(png_ptr, pRow);

			pRow += image.stride();
		}

		::png_write_end(png_ptr, info_ptr);

		::png_destroy_write_struct(&png_ptr, &info_ptr);

		return true;
	}

	bool ImageFormat_PNG::save(const Image& image, const FilePath& path) const
	{
		BinaryWriter writer(path);
			
		return encode(image, writer);
	}
}
