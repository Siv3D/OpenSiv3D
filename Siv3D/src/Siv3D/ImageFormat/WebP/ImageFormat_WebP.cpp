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
# include <libwebp/decode.h>
# include <libwebp/encode.h>
# include "ImageFormat_WebP.hpp"

namespace s3d
{
	namespace detail
	{
		static int WebPWriteCallback(const uint8_t* data, size_t data_size, const WebPPicture* picture)
		{
			IWriter* pWriter = static_cast<IWriter*>(picture->custom_ptr);

			return (static_cast<int64>(data_size) == pWriter->write(data, data_size));
		}

		static void SetMethod(const WebPMethod method, WebPConfig& config)
		{
			switch (method)
			{
			case WebPMethod::Fast:
				config.method = 0;
				break;
			case WebPMethod::Default:
				config.method = 4;
				config.pass = 1;
				break;
			case WebPMethod::Quality:
				config.method = 6;
				config.pass = 2;
				break;
			case WebPMethod::BestQuality:
				config.method = 6;
				config.pass = 10;
				config.alpha_filtering = 2;
				break;
			}
		}
	}

	ImageFormat ImageFormat_WebP::format() const
	{
		return ImageFormat::WebP;
	}

	const Array<String>& ImageFormat_WebP::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"webp" };

		return extensions;
	}

	bool ImageFormat_WebP::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 riff[] = { 'R', 'I', 'F', 'F' };
		static constexpr uint8 webp[] = { 'W', 'E', 'B', 'P' };

		return (std::memcmp(bytes, riff, sizeof(riff)) == 0)
			&& (std::memcmp(bytes + 8, webp, sizeof(webp)) == 0);
	}

	Size ImageFormat_WebP::getSize(const IReader& reader) const
	{
		uint8 data[32];

		if (!reader.lookahead(data))
		{
			return{ 0, 0 };
		}

		int width, height;

		if (!::WebPGetInfo(data, sizeof(data), &width, &height))
		{
			uint8 data2[1024];

			const size_t readBytes = static_cast<size_t>(reader.lookahead(data2, sizeof(data2)));

			if (!::WebPGetInfo(data2, readBytes, &width, &height))
			{
				return{ 0, 0 };
			}
		}

		return{ width, height };
	}

	Image ImageFormat_WebP::decode(IReader& reader) const
	{
		Image image;

		WebPDecoderConfig config;
		WebPDecBuffer* const output_buffer = &config.output;
		WebPBitstreamFeatures* const bitstream = &config.input;

		if (!::WebPInitDecoderConfig(&config))
		{
			return image;
		}

		config.options.use_threads	= true;
		config.output.colorspace	= MODE_RGBA;

		const int64 dataSize = reader.size();
		Array<uint8> buffer(dataSize);

		if (dataSize != reader.read(buffer.data(), dataSize))
		{
			return image;
		}

		if (::WebPGetFeatures(static_cast<const uint8*>(buffer.data()), dataSize, bitstream) != VP8_STATUS_OK)
		{
			return image;
		}

		if (::WebPDecode(static_cast<const uint8*>(buffer.data()), dataSize, &config) != VP8_STATUS_OK)
		{
			return image;
		}

		const int32 width = output_buffer->width;
		const int32 height = output_buffer->height;

		if ((Image::MaxWidth < width) || (Image::MaxHeight < height))
		{
			return image;
		}

		const size_t size = output_buffer->u.RGBA.size;

		image.resize(width, height);

		if (image.size_bytes() != size)
		{
			return image;
		}

		std::memcpy(image.data(), output_buffer->u.RGBA.rgba, size);

		::WebPFreeDecBuffer(output_buffer);

		return image;
	}

	bool ImageFormat_WebP::encode(const Image& image, IWriter& writer) const
	{
		return encode(image, writer, false, 90.0, WebPMethod::Default);
	}

	bool ImageFormat_WebP::encode(const Image& image, IWriter& writer, const bool lossless, const double quality, const WebPMethod method) const
	{
		if (!writer.isOpen())
		{
			return false;
		}

		WebPPicture picture;
		WebPConfig config;
		WebPAuxStats stats;

		if (!::WebPPictureInit(&picture) || !::WebPConfigInit(&config))
		{
			return false;
		}

		picture.width	= image.width();
		picture.height	= image.height();

		if (lossless)
		{
			Image tmp(image);

			picture.argb		= static_cast<uint32*>(static_cast<void*>(tmp.data()));
			picture.argb_stride	= tmp.width();
			picture.use_argb	= 1;
			config.lossless		= 1;
			config.thread_level	= true;
			detail::SetMethod(method, config);

			::WebPPictureImportRGBA(&picture, tmp.dataAsUint8(), tmp.stride());

			if (!::WebPValidateConfig(&config))
			{
				return false;
			}

			picture.writer		= detail::WebPWriteCallback;
			picture.custom_ptr	= &writer;
			picture.stats		= &stats;

			if (!::WebPEncode(&config, &picture))
			{
				::WebPPictureFree(&picture);
				return false;
			}

			::WebPPictureFree(&picture);
		}
		else
		{
			::WebPPictureImportRGBA(&picture, image.dataAsUint8(), image.stride());

			if (!::WebPConfigPreset(&config, WEBP_PRESET_DEFAULT, static_cast<float>(Clamp(quality, 0.0, 100.0))))
			{
				return false;
			}

			config.thread_level = true;
			detail::SetMethod(method, config);

			if (!::WebPValidateConfig(&config))
			{
				return false;
			}

			picture.writer		= detail::WebPWriteCallback;
			picture.custom_ptr	= &writer;
			picture.stats		= &stats;

			if (!::WebPEncode(&config, &picture))
			{
				::WebPPictureFree(&picture);
				return false;
			}

			::WebPPictureFree(&picture);
		}

		return true;
	}

	bool ImageFormat_WebP::save(const Image& image, const FilePath& path) const
	{
		BinaryWriter writer(path);
			
		return encode(image, writer);
	}
}
