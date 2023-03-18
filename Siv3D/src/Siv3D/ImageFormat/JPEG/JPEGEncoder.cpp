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

# include <Siv3D/ImageFormat/JPEGEncoder.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/libjpeg-turbo/turbojpeg.h>
# else
#	include <turbojpeg.h>
# endif

namespace s3d
{
	StringView JPEGEncoder::name() const
	{
		return U"JPEG"_sv;
	}

	ImageFormat JPEGEncoder::imageFormat() const noexcept
	{
		return ImageFormat::JPEG;
	}

	const Array<String>& JPEGEncoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"jpg", U"jpeg" };

		return extensions;
	}

	bool JPEGEncoder::save(const Image& image, const FilePathView path) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		return encode(image, writer, DefaultQuality);
	}

	bool JPEGEncoder::save(const Image& image, const FilePathView path, const int32 quality) const
	{
		BinaryWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		return encode(image, writer, quality);
	}

	bool JPEGEncoder::encode(const Image& image, IWriter& writer) const
	{
		return encode(image, writer, DefaultQuality);
	}

	bool JPEGEncoder::encode(const Image& image, IWriter& writer, int32 quality) const
	{
		if (not writer.isOpen())
		{
			return false;
		}

		quality = Clamp(quality, 0, 100);

		const int32 width = image.width();
		const int32 height = image.height();

		const size_t size = ::tjBufSize(width, height, TJSAMP::TJSAMP_420);
		Blob blob{ size };

		unsigned long retJPEGsize = 0;

		tjhandle tj = ::tjInitCompress();

		::tjCompress(
			tj,
			const_cast<uint8*>(image.dataAsUint8()),
			width,
			width * 4,
			height,
			4,
			(unsigned char*)blob.data(),
			&retJPEGsize,
			TJ_420,
			quality,
			0
		);

		::tjDestroy(tj);

		const bool result = static_cast<int64>(retJPEGsize) == writer.write(blob.data(), retJPEGsize);

		return result;
	}

	Blob JPEGEncoder::encode(const Image& image) const
	{
		return encode(image, DefaultQuality);
	}

	Blob JPEGEncoder::encode(const Image& image, int32 quality) const
	{
		quality = Clamp(quality, 0, 100);

		const int32 width = image.width();
		const int32 height = image.height();

		const size_t size = ::tjBufSize(width, height, TJSAMP::TJSAMP_420);
		Blob blob{ size };

		unsigned long retJPEGsize = 0;

		tjhandle tj = ::tjInitCompress();

		::tjCompress(
			tj,
			const_cast<uint8*>(image.dataAsUint8()),
			width,
			width * 4,
			height,
			4,
			(unsigned char*)blob.data(),
			&retJPEGsize,
			TJ_420,
			quality,
			0
		);

		::tjDestroy(tj);

		blob.resize(retJPEGsize);

		return blob;
	}
}
