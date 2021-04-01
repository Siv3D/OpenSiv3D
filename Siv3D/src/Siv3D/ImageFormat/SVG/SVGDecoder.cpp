//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ImageFormat/SVGDecoder.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/EngineLog.hpp>
# include <ThirdParty/lunasvg/svgdocument.h>

namespace s3d
{
	StringView SVGDecoder::name() const
	{
		return U"SVG"_sv;
	}

	bool SVGDecoder::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 signature1[] = { '<', 's', 'v', 'g', ' ', 'x', 'm', 'l', 'n', 's' };
		static constexpr uint8 signature2[] = { '<', 's', 'v', 'g', ':', 's', 'v', 'g', ' ', 'x', 'm', 'l', 'n', 's' };
		static constexpr uint8 signature3[] = { '<', '?', 'x', 'm', 'l', ' ', 'v', 'e', 'r', 's', 'i', 'o', 'n' };

		return (std::memcmp(bytes, signature1, sizeof(signature1)) == 0)
			|| (std::memcmp(bytes, signature2, sizeof(signature2)) == 0)
			|| (std::memcmp(bytes, signature3, sizeof(signature3)) == 0);
	}

	const Array<String>& SVGDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"svg" };

		return extensions;
	}

	ImageFormat SVGDecoder::imageFormat() const noexcept
	{
		return ImageFormat::SVG;
	}

	Optional<ImageInfo> SVGDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> SVGDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		std::string source(reader.size(), '\0');

		if (reader.read(source.data(), source.size())
			!= static_cast<int64>(source.size()))
		{
			LOG_FAIL(U"❌ SVGDecoder::getImageInfo(): Failed to read the source");
			return none;
		}

		lunasvg::SVGDocument document;
		
		if (not document.loadFromData(source))
		{
			LOG_FAIL(U"❌ SVGDecoder::getImageInfo(): SVGDocument::loadFromData() failed");
			return none;
		}

		const int32 width = static_cast<int32>(std::ceil(document.documentWidth()));
		const int32 height = static_cast<int32>(std::ceil(document.documentHeight()));

		return ImageInfo{ ImageFormat::SVG, ImagePixelFormat::R8G8B8A8, Size(width, height), false };
	}

	Image SVGDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image SVGDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"SVGDecoder::decode()");

		std::string source(reader.size(), '\0');

		if (reader.read(source.data(), source.size())
			!= static_cast<int64>(source.size()))
		{
			LOG_FAIL(U"❌ SVGDecoder::decode(): Failed to read the source");
			return{};
		}

		lunasvg::SVGDocument document;

		if (not document.loadFromData(source))
		{
			LOG_FAIL(U"❌ SVGDecoder::decode(): SVGDocument::loadFromData() failed");
			return{};
		}

		const int32 width = static_cast<int32>(std::ceil(document.documentWidth()));
		const int32 height = static_cast<int32>(std::ceil(document.documentHeight()));
		const lunasvg::Bitmap bitmap = document.renderToBitmap(width, height, 96.0, 0x00000000);

		Image image(bitmap.width(), bitmap.height());
		assert(image.size_bytes() == (bitmap.stride() * bitmap.height()));
		std::memcpy(image.data(), bitmap.data(), image.size_bytes());

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
