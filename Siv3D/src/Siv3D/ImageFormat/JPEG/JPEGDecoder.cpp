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

# include <Siv3D/ImageFormat/JPEGDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/libjpeg-turbo/turbojpeg.h>
# else
#	include <turbojpeg.h>
# endif

namespace s3d
{
	StringView JPEGDecoder::name() const
	{
		return U"JPEG"_sv;
	}

	ImageFormat JPEGDecoder::imageFormat() const noexcept
	{
		return ImageFormat::JPEG;
	}

	bool JPEGDecoder::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 JFIF_SIGN0[] = { 0xFF, 0xD8, 0xFF, 0xE0 };
		static constexpr uint8 JFIF_SIGN1[] = { 'J', 'F', 'I', 'F' };
		static constexpr uint8 EXIF_SIGN0[] = { 0xFF, 0xD8, 0xFF, 0xE1 };
		static constexpr uint8 EXIF_SIGN1[] = { 'E', 'x', 'i', 'f' };

		return (std::memcmp(bytes, JFIF_SIGN0, sizeof(JFIF_SIGN0)) == 0 && std::memcmp(bytes + 6, JFIF_SIGN1, sizeof(JFIF_SIGN1)) == 0)
			|| (std::memcmp(bytes, EXIF_SIGN0, sizeof(EXIF_SIGN0)) == 0 && std::memcmp(bytes + 6, EXIF_SIGN1, sizeof(EXIF_SIGN1)) == 0);
	}

	const Array<String>& JPEGDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"jpg", U"jpeg" };

		return extensions;
	}

	Optional<ImageInfo> JPEGDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> JPEGDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		uint8 buf[24];

		if (not reader.lookahead(buf))
		{
			return none;
		}

		const auto len = reader.size();

		//
		//	http://www.wischik.com/lu/programmer/get-image-size.html
		//
		if ((buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && buf[3] == 0xE0 && buf[6] == 'J' && buf[7] == 'F' && buf[8] == 'I' && buf[9] == 'F')
			|| (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && buf[3] == 0xE1 && buf[6] == 'E' && buf[7] == 'x' && buf[8] == 'i' && buf[9] == 'f'))
		{
			int64 pos = 2;

			while (buf[2] == 0xFF)
			{
				if (buf[3] == 0xC0
					|| buf[3] == 0xC1
					|| buf[3] == 0xC2
					|| buf[3] == 0xC3
					|| buf[3] == 0xC5
					|| buf[3] == 0xC6
					|| buf[3] == 0xC7
					|| buf[3] == 0xC9
					|| buf[3] == 0xCA
					|| buf[3] == 0xCB
					|| buf[3] == 0xCD
					|| buf[3] == 0xCE
					|| buf[3] == 0xCF)
				{
					break;
				}

				pos += 2 + (buf[4] << 8) + buf[5];

				if (pos + 12 > len)
				{
					break;
				}

				reader.lookahead(buf + 2, pos, 12);
			}
		}

		// JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
		if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF)
		{
			const int32 width = (buf[9] << 8) + buf[10];
			const int32 height = (buf[7] << 8) + buf[8];

			return ImageInfo{ Size{ width, height }, ImageFormat::JPEG, ImagePixelFormat::R8G8B8, false };
		}

		return none;
	}

	Image JPEGDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image JPEGDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"JPEGDecoder::decode()");

		const int64 size = reader.size();

		uint8* buffer = static_cast<uint8*>(std::malloc(static_cast<size_t>(size)));

		reader.read(buffer, size);

		int width, height;

		tjhandle tj = ::tjInitDecompress();

		::tjDecompressHeader(tj, buffer, static_cast<unsigned long>(size), &width, &height);

		Image image(width, height);

		::tjDecompress(
			tj,
			buffer,
			static_cast<unsigned long>(size),
			image.dataAsUint8(),
			image.width(),
			image.stride(),
			image.height(),
			sizeof(Color),
			0);

		::tjDestroy(tj);

		std::free(buffer);

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
