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

# include <Siv3D/ImageFormat/GenericDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		struct DecodedImageData
		{
			uint8* decodedImage;
			uint32 length;
			uint32 width;
			uint32 height;
		};

		__attribute__((import_name("siv3dDecodeImageFromFile")))
		extern void siv3dDecodeImageFromFile(void* src, uint32 length, DecodedImageData* data);
	}

	StringView GenericDecoder::name() const
	{
		return U"Generic"_sv;
	}

	ImageFormat GenericDecoder::imageFormat() const noexcept
	{
		return ImageFormat::Unknown;
	}

	bool GenericDecoder::isHeader(const uint8(&_bytes)[16]) const
	{
		return true;
	}

	const Array<String>& GenericDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"bmp" };

		return extensions;
	}

	Optional<ImageInfo> GenericDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> GenericDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		const auto imageSize = reader.size();
		const auto imageData = std::malloc(imageSize);

		reader.read(imageData, imageSize);

		detail::DecodedImageData data;

		detail::siv3dDecodeImageFromFile(imageData, imageSize, &data);

		std::free(data.decodedImage);
		std::free(imageData);

		return ImageInfo{ Size{ data.width, data.height }, ImageFormat::BMP, ImagePixelFormat::R8G8B8A8, false };
	}

	Image GenericDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image GenericDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"GenericDecoder::decode()");

		const auto imageSize = reader.size();
		const auto imageData = ::malloc(imageSize);

		reader.read(imageData, imageSize);

		detail::DecodedImageData data;

		detail::siv3dDecodeImageFromFile(imageData, imageSize, &data);

		Image image{ data.width, data.height };

		std::memcpy(image.data(), data.decodedImage, image.size_bytes());

		return image;
	}
}
