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

# include <Siv3D/ImageFormat/WebPDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	/*
	StringView WebPDecoder::name() const
	{
		return U"WebP"_sv;
	}

	bool WebPDecoder::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 WebP_SIGN87a[] = { 'G', 'I', 'F', '8', '7', 'a' };
		static constexpr uint8 WebP_SIGN89a[] = { 'G', 'I', 'F', '8', '9', 'a' };

		return std::memcmp(bytes, WebP_SIGN87a, sizeof(WebP_SIGN87a)) == 0
			|| std::memcmp(bytes, WebP_SIGN89a, sizeof(WebP_SIGN89a)) == 0;
	}

	const Array<String>& WebPDecoder::possibleExtensions() const
	{
		static const Array<String> extensions = { U"gif" };

		return extensions;
	}

	Optional<ImageInfo> WebPDecoder::getImageInfo(const FilePathView path) const
	{
		return IImageDecoder::getImageInfo(path);
	}

	Optional<ImageInfo> WebPDecoder::getImageInfo(IReader& reader, const FilePathView) const
	{
		uint8 buf[4];

		if (not reader.lookahead(buf))
		{
			LOG_FAIL(U"❌ WebPDecoder::getImageInfo(): File size is invalid");
			return{};
		}

		const int32 width = ((buf[1] << 8) + (buf[0] << 0));
		const int32 height = ((buf[3] << 8) + (buf[2] << 0));
		const Size size{ width, height };
		
		ImagePixelFormat pixelFormat = ImagePixelFormat::R8G8B8A8;

		return ImageInfo{ ImageFormat::WebP, pixelFormat, size, false };
	}

	Image WebPDecoder::decode(const FilePathView path) const
	{
		return IImageDecoder::decode(path);
	}

	Image WebPDecoder::decode(IReader& reader, const FilePathView) const
	{
		LOG_SCOPED_TRACE(U"WebPDecoder::decode()");

		int error;
		GifFileType* gif = DGifOpen(&reader, detail::GifReadCallback, &error);

		if (not gif)
		{
			return{};
		}

		if (DGifSlurp(gif) != WebP_OK)
		{
			DGifCloseFile(gif, &error);

			return{};
		}

		if (gif->SColorMap && gif->SColorMap->ColorCount < gif->SBackGroundColor)
		{
			gif->SBackGroundColor = 0;
		}

		int32 transparentIndex = -1;
		const uint32 frameIndex = 0;
		const SavedImage* frame = &gif->SavedImages[frameIndex];

		if (frame->ExtensionBlockCount > 0)
		{
			for (int32 i = 0; i < frame->ExtensionBlockCount; ++i)
			{
				ExtensionBlock* ext = &frame->ExtensionBlocks[i];

				if (ext->Function == GRAPHICS_EXT_FUNC_CODE && ext->ByteCount == 4)
				{
					// has transparency
					transparentIndex = (ext->Bytes[0] & 0x1) ? ext->Bytes[3] : -1;
				}
			}
		}

		const ColorMapObject* colorMap = frame->ImageDesc.ColorMap ? frame->ImageDesc.ColorMap : gif->SColorMap;

		// no local or global color map
		if (not colorMap)
		{
			DGifCloseFile(gif, &error);

			return{};
		}

		Color palette[256];
		memset(palette, 0, sizeof(palette));
		for (int32 i = 0; i < colorMap->ColorCount; ++i)
		{
			palette[i].r = colorMap->Colors[i].Red;
			palette[i].g = colorMap->Colors[i].Green;
			palette[i].b = colorMap->Colors[i].Blue;
			palette[i].a = 255;
		}

		if (0 <= transparentIndex)
		{
			palette[transparentIndex].set(0, 0, 0, 0);
		}

		const int32 offset_x = frame->ImageDesc.Left;
		const int32 offset_y = frame->ImageDesc.Top;
		const size_t width = frame->ImageDesc.Width;
		const size_t height = frame->ImageDesc.Height;

		if ((width == 0) || (height == 0))
		{
			return{};
		}

		Image image{ width, height };
		Color* pDst = image.data();

		for (int32 y = 0; y < height; ++y)
		{
			size_t srcOffset = y * width;
			size_t dstOffset = (y + offset_y) * gif->SWidth + offset_x;

			for (int32 x = 0; x < width; ++x)
			{
				const uint8 index = frame->RasterBits[srcOffset];

				*(pDst + dstOffset) = palette[index];

				++srcOffset;
				++dstOffset;
			}
		}

		DGifCloseFile(gif, &error);

		LOG_VERBOSE(U"Image ({}x{}) decoded"_fmt(
			width, height));

		return image;
	}
	*/
}
