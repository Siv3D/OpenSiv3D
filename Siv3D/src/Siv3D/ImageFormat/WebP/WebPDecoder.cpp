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

# include <Siv3D/ImageFormat/WebPDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/libwebp/decode.h>
# else
#	include <webp/decode.h>
# endif

namespace s3d
{
	StringView WebPDecoder::name() const
	{
		return U"WebP"_sv;
	}

	ImageFormat WebPDecoder::imageFormat() const noexcept
	{
		return ImageFormat::WebP;
	}

	bool WebPDecoder::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 riff[] = { 'R', 'I', 'F', 'F' };
		static constexpr uint8 webp[] = { 'W', 'E', 'B', 'P' };

		return (std::memcmp(bytes, riff, sizeof(riff)) == 0)
			&& (std::memcmp(bytes + 8, webp, sizeof(webp)) == 0);
	}

	const Array<String>& WebPDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"webp" };

		return extensions;
	}

	Optional<ImageInfo> WebPDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> WebPDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		uint8 data[32];

		if (not reader.lookahead(data))
		{
			LOG_FAIL(U"❌ WebPDecoder::getImageInfo(): File size is invalid");
			return{};
		}

		int32 width, height;

		if (not ::WebPGetInfo(data, sizeof(data), &width, &height))
		{
			uint8 data2[1024];

			const size_t readBytes = static_cast<size_t>(reader.lookahead(data2, sizeof(data2)));

			if (not ::WebPGetInfo(data2, readBytes, &width, &height))
			{
				return{};
			}
		}
		
		ImagePixelFormat pixelFormat = ImagePixelFormat::R8G8B8A8;

		return ImageInfo{ Size{ width, height }, ImageFormat::WebP, pixelFormat, false };
	}

	Image WebPDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image WebPDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"WebPDecoder::decode()");

		WebPDecoderConfig config;
		WebPDecBuffer* const output_buffer = &config.output;
		WebPBitstreamFeatures* const bitstream = &config.input;

		if (not ::WebPInitDecoderConfig(&config))
		{
			return{};
		}

		config.options.use_threads = true;
		config.output.colorspace = MODE_RGBA;

		const int64 dataSize = reader.size();
		Array<uint8> buffer(dataSize);

		if (dataSize != reader.read(buffer.data(), dataSize))
		{
			return{};
		}

		if (::WebPGetFeatures(static_cast<const uint8*>(buffer.data()), dataSize, bitstream) != VP8_STATUS_OK)
		{
			return{};
		}

		if (::WebPDecode(static_cast<const uint8*>(buffer.data()), dataSize, &config) != VP8_STATUS_OK)
		{
			return{};
		}

		const int32 width = output_buffer->width;
		const int32 height = output_buffer->height;

		if ((Image::MaxWidth < width) || (Image::MaxHeight < height))
		{
			return{};
		}

		const size_t size = output_buffer->u.RGBA.size;

		Image image(width, height);

		if (image.size_bytes() != size)
		{
			return image;
		}

		std::memcpy(image.data(), output_buffer->u.RGBA.rgba, size);

		::WebPFreeDecBuffer(output_buffer);

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
