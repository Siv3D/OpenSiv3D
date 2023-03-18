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

# include <Siv3D/ImageFormat/PNGDecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Endian.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/libpng/png.h>
# else
#	include <png.h>
# endif

namespace s3d
{
	static void PngReadCallback(png_structp png_ptr, png_bytep buf, png_size_t length)
	{
		const auto reader = static_cast<IReader*>(::png_get_io_ptr(png_ptr));

		reader->read(buf, length);
	}

	StringView PNGDecoder::name() const
	{
		return U"PNG"_sv;
	}

	ImageFormat PNGDecoder::imageFormat() const noexcept
	{
		return ImageFormat::PNG;
	}

	bool PNGDecoder::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 signature[] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };

		return (std::memcmp(bytes, signature, sizeof(signature)) == 0);
	}

	const Array<String>& PNGDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"png" };

		return extensions;
	}

	Optional<ImageInfo> PNGDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> PNGDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		// png_ptr
		png_structp png_ptr = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		{
			if (!png_ptr)
			{
				return{};
			}
		}

		ScopeGuard cleanup_struct = [&]()
		{
			::png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		};

		// info_ptr
		png_infop info_ptr = ::png_create_info_struct(png_ptr);
		{
			if (!info_ptr)
			{
				return{};
			}
		}

		ScopeGuard cleanup_info = [&]()
		{
			::png_destroy_info_struct(png_ptr, &info_ptr);
		};

		// decode
		::png_set_read_fn(png_ptr, &reader, PngReadCallback);
		::png_read_info(png_ptr, info_ptr);

		png_uint_32 width = 0, height = 0;
		int iBitDepth, iColorType;

		::png_get_IHDR(png_ptr, info_ptr, &width, &height, &iBitDepth, &iColorType, nullptr, nullptr, nullptr);

		ImagePixelFormat pixelFormat = ImagePixelFormat::R8G8B8A8;

		if (iColorType == PNG_COLOR_TYPE_GRAY)
		{
			if (iBitDepth == 16)
			{
				pixelFormat = ImagePixelFormat::Gray16;
			}
			else
			{
				pixelFormat = ImagePixelFormat::Gray8;
			}
		}
		else if (iColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
		{
			if (iBitDepth == 16)
			{
				pixelFormat = ImagePixelFormat::Gray16A16;
			}
			else
			{
				pixelFormat = ImagePixelFormat::Gray8A8;
			}
		}
		else if (iColorType == PNG_COLOR_TYPE_RGB)
		{
			pixelFormat = ImagePixelFormat::R8G8B8;
		}

		return ImageInfo{ Size{ width, height }, ImageFormat::PNG, pixelFormat, false };
	}

	Image PNGDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image PNGDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"PNGDecoder::decode()");

		// png_ptr
		png_structp png_ptr = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		{
			if (!png_ptr)
			{
				return{};
			}
		}

		ScopeGuard cleanup_struct = [&]()
		{
			::png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		};

		// info_ptr
		png_infop info_ptr = ::png_create_info_struct(png_ptr);
		{
			if (!info_ptr)
			{
				return{};
			}
		}

		ScopeGuard cleanup_info = [&]()
		{
			::png_destroy_info_struct(png_ptr, &info_ptr);
		};

		// decode
		::png_set_read_fn(png_ptr, &reader, PngReadCallback);

		::png_read_info(png_ptr, info_ptr);

		png_uint_32 width = 0, height = 0;

		int iBitDepth, iColorType;

		::png_get_IHDR(png_ptr, info_ptr, &width, &height, &iBitDepth, &iColorType, nullptr, nullptr, nullptr);

		if ((Image::MaxWidth < width) || (Image::MaxHeight < height))
		{
			LOG_FAIL(U"PNGDecoder::decode(): Image size {}x{} is not supported"_fmt(
				width, height));
			return{};
		}

		if (iColorType == PNG_COLOR_TYPE_PALETTE)
		{
			LOG_VERBOSE(U"png_set_palette_to_rgb()");
			::png_set_palette_to_rgb(png_ptr);
		}

		if (::png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			LOG_VERBOSE(U"png_set_tRNS_to_alpha()");
			::png_set_tRNS_to_alpha(png_ptr);
		}

		if (iColorType == PNG_COLOR_TYPE_GRAY && iBitDepth < 8)
		{
			LOG_VERBOSE(U"png_set_expand_gray_1_2_4_to_8()");
			::png_set_expand_gray_1_2_4_to_8(png_ptr);
		}

		if (iBitDepth == 16)
		{
			LOG_VERBOSE(U"png_set_scale_16()");
			::png_set_scale_16(png_ptr);
		}

		if (iBitDepth < 8)
		{
			LOG_VERBOSE(U"png_set_packing()");
			::png_set_packing(png_ptr);
		}

		if ((iColorType == PNG_COLOR_TYPE_GRAY)
			|| (iColorType == PNG_COLOR_TYPE_GRAY_ALPHA))
		{
			LOG_VERBOSE(U"png_set_gray_to_rgb()");
			::png_set_gray_to_rgb(png_ptr);
		}

		::png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);

		double dGamma;

		if (::png_get_gAMA(png_ptr, info_ptr, &dGamma))
		{
			LOG_VERBOSE(U"png_set_gamma()");
			::png_set_gamma(png_ptr, 2.2, dGamma);
		}

		::png_read_update_info(png_ptr, info_ptr);

		const int nChannels = ::png_get_channels(png_ptr, info_ptr);

		::png_get_IHDR(png_ptr, info_ptr, &width, &height, &iBitDepth, &iColorType, nullptr, nullptr, nullptr);

		Image image(width, height);

		Array<uint8*> ppbRowPointers(height);
		{
			const size_t stride = (width * nChannels);
			uint8* pixels = image.dataAsUint8();

			for (size_t i = 0; i < height; ++i)
			{
				ppbRowPointers[i] = pixels;
				pixels += stride;
			}
		}

		::png_read_image(png_ptr, ppbRowPointers.data());

		::png_read_end(png_ptr, nullptr);

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}

	Grid<uint16> PNGDecoder::decodeGray16(const FilePathView path) const
	{
		return IImageDecoder::decodeGray16(path);
	}

	Grid<uint16> PNGDecoder::decodeGray16(IReader& reader, FilePathView) const
	{
		LOG_SCOPED_TRACE(U"PNGDecoder::decode()");

		// png_ptr
		png_structp png_ptr = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		{
			if (!png_ptr)
			{
				return{};
			}
		}

		ScopeGuard cleanup_struct = [&]()
		{
			::png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		};

		// info_ptr
		png_infop info_ptr = ::png_create_info_struct(png_ptr);
		{
			if (!info_ptr)
			{
				return{};
			}
		}

		ScopeGuard cleanup_info = [&]()
		{
			::png_destroy_info_struct(png_ptr, &info_ptr);
		};

		// decode
		::png_set_read_fn(png_ptr, &reader, PngReadCallback);

		::png_read_info(png_ptr, info_ptr);

		png_uint_32 width = 0, height = 0;

		int iBitDepth, iColorType;

		::png_get_IHDR(png_ptr, info_ptr, &width, &height, &iBitDepth, &iColorType, nullptr, nullptr, nullptr);

		if ((Image::MaxWidth < width) || (Image::MaxHeight < height))
		{
			LOG_FAIL(U"PNGDecoder::decode(): Image size {}x{} is not supported"_fmt(
				width, height));
			return{};
		}

		if (iColorType == PNG_COLOR_TYPE_PALETTE)
		{
			LOG_VERBOSE(U"png_set_palette_to_rgb()");
			::png_set_palette_to_rgb(png_ptr);
		}

		if (::png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			LOG_VERBOSE(U"png_set_tRNS_to_alpha()");
			::png_set_tRNS_to_alpha(png_ptr);
		}

		if (iColorType == PNG_COLOR_TYPE_GRAY && iBitDepth < 8)
		{
			LOG_VERBOSE(U"png_set_expand_gray_1_2_4_to_8()");
			::png_set_expand_gray_1_2_4_to_8(png_ptr);
		}

		if (iBitDepth != 16
			|| (iColorType != PNG_COLOR_TYPE_GRAY))
		{
			return{};
		}

		double dGamma;

		if (::png_get_gAMA(png_ptr, info_ptr, &dGamma))
		{
			LOG_VERBOSE(U"png_set_gamma()");
			::png_set_gamma(png_ptr, 2.2, dGamma);
		}

		::png_read_update_info(png_ptr, info_ptr);

		const int nChannels = ::png_get_channels(png_ptr, info_ptr);

		::png_get_IHDR(png_ptr, info_ptr, &width, &height, &iBitDepth, &iColorType, nullptr, nullptr, nullptr);

		Grid<uint16> image(width, height);

		Array<uint16*> ppbRowPointers(height);
		{
			const size_t stride = (width * nChannels);
			uint16* pixels = image.data();

			for (size_t i = 0; i < height; ++i)
			{
				ppbRowPointers[i] = pixels;
				pixels += stride;
			}
		}

		::png_read_image(png_ptr, static_cast<png_bytepp>(static_cast<void*>(ppbRowPointers.data())));

		::png_read_end(png_ptr, nullptr);

		for (auto& pixel : image)
		{
			pixel = SwapEndian(pixel);
		}

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
