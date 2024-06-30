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

# include <Siv3D/ImageFormat/SVGDecoder.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/EngineLog.hpp>
# include <ThirdParty/lunasvg/lunasvg.h>

namespace s3d
{
	StringView SVGDecoder::name() const
	{
		return U"SVG"_sv;
	}

	ImageFormat SVGDecoder::imageFormat() const noexcept
	{
		return ImageFormat::SVG;
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

		std::unique_ptr<lunasvg::Document> document = lunasvg::Document::loadFromData(source);
		
		if (not document)
		{
			LOG_FAIL(U"❌ SVGDecoder::getImageInfo(): SVGDocument::loadFromData() failed");
			return none;
		}

		const int32 width = static_cast<int32>(std::ceil(document->width()));
		const int32 height = static_cast<int32>(std::ceil(document->height()));

		return ImageInfo{ Size{ width, height }, ImageFormat::SVG, ImagePixelFormat::R8G8B8A8, false };
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

		std::unique_ptr<lunasvg::Document> document = lunasvg::Document::loadFromData(source);

		if (not document)
		{
			LOG_FAIL(U"❌ SVGDecoder::decode(): SVGDocument::loadFromData() failed");
			return{};
		}

		const int32 width = static_cast<int32>(std::ceil(document->width()));
		const int32 height = static_cast<int32>(std::ceil(document->height()));
		lunasvg::Bitmap bitmap = document->renderToBitmap(width, height, 0x00000000);
		bitmap.convert(0, 1, 2, 3, true);

		Image image(bitmap.width(), bitmap.height());
		assert(image.size_bytes() == (bitmap.stride() * bitmap.height()));
		std::memcpy(image.data(), bitmap.data(), image.size_bytes());

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
}
