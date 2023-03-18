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

# include <Siv3D/ImageFormat/PNGEncoder.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/libpng/png.h>
# else
#	include <png.h>
# endif

namespace s3d
{
	static void PngWriteCallbackIWriter(png_structp png_ptr, png_bytep src, png_size_t length)
	{
		IWriter* pWriter = static_cast<IWriter*>(::png_get_io_ptr(png_ptr));

		pWriter->write(src, length);
	}

	static void PngWriteCallbackBlob(png_structp png_ptr, png_bytep src, png_size_t length)
	{
		Blob* pBlob = static_cast<Blob*>(::png_get_io_ptr(png_ptr));

		pBlob->append(src, length);
	}

	StringView PNGEncoder::name() const
	{
		return U"PNG"_sv;
	}

	ImageFormat PNGEncoder::imageFormat() const noexcept
	{
		return ImageFormat::PNG;
	}

	bool PNGEncoder::save(const Image& image, const FilePathView path) const
	{
		return save(image, path, PNGFilter::Default);
	}

	const Array<String>& PNGEncoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"png" };

		return extensions;
	}

	bool PNGEncoder::save(const Image& image, const FilePathView path, const PNGFilter filter) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		return encode(image, writer, filter);
	}

	bool PNGEncoder::save(const Grid<uint16>& image, const FilePathView path, const PNGFilter filter) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		return encode(image, writer, filter);
	}

	bool PNGEncoder::encode(const Image& image, IWriter& writer) const
	{
		return encode(image, writer, PNGFilter::Default);
	}

	bool PNGEncoder::encode(const Image& image, IWriter& writer, const PNGFilter filter) const
	{
		if (not writer.isOpen())
		{
			return false;
		}

		png_structp png_ptr = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if (not png_ptr)
		{
			return false;
		}

		png_infop info_ptr = ::png_create_info_struct(png_ptr);

		if (not info_ptr)
		{
			::png_destroy_write_struct(&png_ptr, nullptr);

			return false;
		}

		::png_set_write_fn(png_ptr, &writer, PngWriteCallbackIWriter, nullptr);

		const png_uint_32 width = image.width();

		const png_uint_32 height = image.height();

		::png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		::png_set_filter(png_ptr, 0, FromEnum(filter));

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

	bool PNGEncoder::encode(const Grid<uint16>& image, IWriter& writer, const PNGFilter filter) const
	{
		if (not writer.isOpen())
		{
			return false;
		}

		png_structp png_ptr = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if (not png_ptr)
		{
			return false;
		}

		png_infop info_ptr = ::png_create_info_struct(png_ptr);

		if (not info_ptr)
		{
			::png_destroy_write_struct(&png_ptr, nullptr);

			return false;
		}

		::png_set_write_fn(png_ptr, &writer, PngWriteCallbackIWriter, nullptr);

		const png_uint_32 width = static_cast<png_uint_32>(image.width());

		const png_uint_32 height = static_cast<png_uint_32>(image.height());

		::png_set_IHDR(png_ptr, info_ptr, width, height, 16, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		::png_set_filter(png_ptr, 0, FromEnum(filter));

		::png_write_info(png_ptr, info_ptr);

		const uint8* pRow = static_cast<const uint8*>(static_cast<const void*>(image.data()));

		const uint32 stride = (width * sizeof(uint16));

		Array<const uint8*> rows(image.height());

		for (uint32 y = 0; y < height; ++y)
		{
			rows[y] = pRow;

			pRow += stride;
		}

		::png_set_rows(png_ptr, info_ptr, (png_bytepp)rows.data());

		::png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_SWAP_ENDIAN, nullptr);

		::png_destroy_write_struct(&png_ptr, &info_ptr);

		return true;
	}

	Blob PNGEncoder::encode(const Image& image) const
	{
		return encode(image, PNGFilter::Default);
	}

	Blob PNGEncoder::encode(const Image& image, const PNGFilter filter) const
	{
		png_structp png_ptr = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if (not png_ptr)
		{
			return{};
		}

		png_infop info_ptr = ::png_create_info_struct(png_ptr);

		if (not info_ptr)
		{
			::png_destroy_write_struct(&png_ptr, nullptr);

			return{};
		}

		Blob blob;

		::png_set_write_fn(png_ptr, &blob, PngWriteCallbackBlob, nullptr);

		const png_uint_32 width = image.width();

		const png_uint_32 height = image.height();

		::png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		::png_set_filter(png_ptr, 0, FromEnum(filter));

		::png_write_info(png_ptr, info_ptr);

		const uint8* pRow = image.dataAsUint8();

		for (uint32 y = 0; y < height; ++y)
		{
			::png_write_row(png_ptr, pRow);

			pRow += image.stride();
		}

		::png_write_end(png_ptr, info_ptr);

		::png_destroy_write_struct(&png_ptr, &info_ptr);

		return blob;
	}

	Blob PNGEncoder::encode(const Grid<uint16>& image, const PNGFilter filter) const
	{
		png_structp png_ptr = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

		if (not png_ptr)
		{
			return{};
		}

		png_infop info_ptr = ::png_create_info_struct(png_ptr);

		if (not info_ptr)
		{
			::png_destroy_write_struct(&png_ptr, nullptr);

			return{};
		}

		Blob blob;

		::png_set_write_fn(png_ptr, &blob, PngWriteCallbackBlob, nullptr);

		const png_uint_32 width = static_cast<png_uint_32>(image.width());

		const png_uint_32 height = static_cast<png_uint_32>(image.height());

		::png_set_IHDR(png_ptr, info_ptr, width, height, 16, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		::png_set_filter(png_ptr, 0, FromEnum(filter));

		::png_write_info(png_ptr, info_ptr);

		const uint8* pRow = static_cast<const uint8*>(static_cast<const void*>(image.data()));

		const uint32 stride = (width * sizeof(uint16));

		Array<const uint8*> rows(image.height());

		for (uint32 y = 0; y < height; ++y)
		{
			rows[y] = pRow;

			pRow += stride;
		}

		::png_set_rows(png_ptr, info_ptr, (png_bytepp)rows.data());

		::png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_SWAP_ENDIAN, nullptr);

		::png_destroy_write_struct(&png_ptr, &info_ptr);

		return blob;
	}
}
