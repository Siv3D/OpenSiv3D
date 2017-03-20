//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../ThirdParty/libjpeg-turbo/turbojpeg.h"
# include "ImageFormat_JPEG.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	ImageFormat ImageFormat_JPEG::format() const
	{
		return ImageFormat::JPEG;
	}

	const Array<String>& ImageFormat_JPEG::possibleExtexsions() const
	{
		static const Array<String> extensions = { L"jpg", L"jpeg" };

		return extensions;
	}

	bool ImageFormat_JPEG::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 JFIF_SIGN0[] = { 0xFF, 0xD8, 0xFF, 0xE0 };
		static constexpr uint8 JFIF_SIGN1[] = { 'J', 'F', 'I', 'F' };
		static constexpr uint8 EXIF_SIGN0[] = { 0xFF, 0xD8, 0xFF, 0xE1 };
		static constexpr uint8 EXIF_SIGN1[] = { 'E', 'x', 'i', 'f' };

		return (::memcmp(bytes, JFIF_SIGN0, sizeof(JFIF_SIGN0)) == 0 && ::memcmp(bytes + 6, JFIF_SIGN1, sizeof(JFIF_SIGN1)) == 0)
			|| (::memcmp(bytes, EXIF_SIGN0, sizeof(EXIF_SIGN0)) == 0 && ::memcmp(bytes + 6, EXIF_SIGN1, sizeof(EXIF_SIGN1)) == 0);
	}

	Size ImageFormat_JPEG::getSize(const IReader& reader) const
	{
		uint8 buf[24];

		if (!reader.lookahead(buf))
		{
			return{ 0, 0 };
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

			return{ width, height };
		}

		return{ 0, 0 };
	}

	Image ImageFormat_JPEG::decode(IReader& reader) const
	{
		const int64 size = reader.size();
		
		uint8* buffer = static_cast<uint8*>(::malloc(static_cast<size_t>(size)));
		
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

		::free(buffer);

		return image;
	}

	bool ImageFormat_JPEG::encode(const Image& image, IWriter& writer) const
	{
		return encode(image, writer, 90);
	}

	bool ImageFormat_JPEG::encode(const Image& image, IWriter& writer, int32 quality) const
	{
		quality = Clamp(quality, 0, 100);

		const int32 width = image.width();
		const int32 height = image.height();

		const size_t size = ::tjBufSize(width, height, TJSAMP::TJSAMP_420);
		uint8* buffer = static_cast<uint8*>(::malloc(size));

		unsigned long retJPEGsize = 0;

		tjhandle tj = ::tjInitCompress();

		::tjCompress(
			tj,
			const_cast<uint8*>(image.dataAsUint8()),
			width,
			width * 4,
			height,
			4,
			buffer,
			&retJPEGsize,
			TJ_420,
			quality,
			0
		);

		::tjDestroy(tj);

		const bool result = retJPEGsize == writer.write(buffer, retJPEGsize);

		::free(buffer);

		return result;
	}

	bool ImageFormat_JPEG::save(const Image& image, const FilePath& path) const
	{
		BinaryWriter writer(path);
			
		return encode(image, writer);
	}
}
