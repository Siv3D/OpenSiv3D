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

# include "../../../ThirdParty/giflib/gif_lib.h"
# include "ImageFormat_GIF.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/IWriter.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	namespace detail
	{
		static int GifReadCallback(GifFileType* gif, GifByteType* bytes, const int size)
		{
			const auto reader = static_cast<IReader*>(gif->UserData);

			return static_cast<int>(reader->read(bytes, size));
		}

		static int GifWriteCallback(GifFileType* gif, const GifByteType * bytes, const int size)
		{
			const auto writer = static_cast<IWriter*>(gif->UserData);

			return static_cast<int>(writer->write(bytes, size));
		}
	}

	ImageFormat ImageFormat_GIF::format() const
	{
		return ImageFormat::GIF;
	}

	const Array<String>& ImageFormat_GIF::possibleExtexsions() const
	{
		static const Array<String> extensions = { L"gif" };

		return extensions;
	}

	bool ImageFormat_GIF::isHeader(const uint8(&bytes)[16]) const
	{
		static constexpr uint8 GIF_SIGN87a[] = { 'G', 'I', 'F', '8', '7', 'a' };
		static constexpr uint8 GIF_SIGN89a[] = { 'G', 'I', 'F', '8', '9', 'a' };
			
		return ::memcmp(bytes, GIF_SIGN87a, sizeof(GIF_SIGN87a)) == 0
			|| ::memcmp(bytes, GIF_SIGN89a, sizeof(GIF_SIGN89a)) == 0;
	}

	Size ImageFormat_GIF::getSize(const IReader& reader) const
	{
		uint8 buf[4];

		if (!reader.lookahead(buf))
		{
			return{ 0, 0 };
		}

		const int32 width = (buf[1] << 8) + (buf[0] << 0);
		const int32 height = (buf[3] << 8) + (buf[2] << 0);

		return{ width, height };
	}

	Image ImageFormat_GIF::decode(IReader& reader) const
	{
		Image image;

		int error;
		GifFileType* gif = DGifOpen(&reader, detail::GifReadCallback, &error);

		if (!gif)
		{
			return image;
		}

		if (DGifSlurp(gif) != GIF_OK)
		{
			DGifCloseFile(gif, &error);

			return image;
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
				ExtensionBlock *ext = &frame->ExtensionBlocks[i];

				if (ext->Function == GRAPHICS_EXT_FUNC_CODE && ext->ByteCount == 4)
				{
					// has transparency
					transparentIndex = (ext->Bytes[0] & 0x1) ? ext->Bytes[3] : -1;
				}
			}
		}

		const ColorMapObject* colorMap = frame->ImageDesc.ColorMap ? frame->ImageDesc.ColorMap : gif->SColorMap;
		
		// no local or global color map
		if (!colorMap)
		{
			DGifCloseFile(gif, &error);

			return image;
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
		const int32 width = frame->ImageDesc.Width;
		const int32 height = frame->ImageDesc.Height;

		image.resize(width, height);
		Color* pDst = image.data();

		for (int32 y = 0; y < height; ++y)
		{
			uint32 srcOffset = y * width;
			uint32 dstOffset = (y + offset_y) * gif->SWidth + offset_x;

			for (int32 x = 0; x < width; ++x)
			{
				++srcOffset;

				++dstOffset;

				const uint8 index = frame->RasterBits[srcOffset];

				*(pDst + dstOffset) = palette[index];
			}
		}

		DGifCloseFile(gif, &error);

		return image;
	}

	bool ImageFormat_GIF::encode(const Image& image, IWriter& writer) const
	{
		if (!writer.isOpened())
		{
			return false;
		}

		const int32 width = image.width();
		const int32 height = image.height();
		const int32 num_pixels = image.num_pixels();
		Array<uint8> rBuffer(num_pixels);
		Array<uint8> gBuffer(num_pixels);
		Array<uint8> bBuffer(num_pixels);

		uint8* rDst = rBuffer.data();
		uint8* gDst = gBuffer.data();
		uint8* bDst = bBuffer.data();
		{
			const Color* pSrc = image.data();
			const Color* const pSrcEnd = pSrc + num_pixels;

			while (pSrc != pSrcEnd)
			{
				*rDst++ = pSrc->r;
				*gDst++ = pSrc->g;
				*bDst++ = pSrc->b;
				++pSrc;
			}
		}

		bool hasTransparency = false;
		{
			const Color* pSrc = image.data();
			const Color* const pSrcEnd = pSrc + num_pixels;

			while (pSrc != pSrcEnd)
			{
				if (pSrc->a == 0)
				{
					hasTransparency = true;
					break;
				}

				++pSrc;
			}
		}

		int32 colorMapSize = hasTransparency ? 255 : 256;
		GifColorType colors[256] = {};

		ColorMapObject colorMap;
		colorMap.ColorCount		= colorMapSize;
		colorMap.BitsPerPixel	= 8;
		colorMap.Colors			= colors;
		Array<GifByteType> outputBuffer(num_pixels);

		GifQuantizeBuffer(width, height, &colorMapSize,
			rBuffer.data(), gBuffer.data(), bBuffer.data(), outputBuffer.data(), colorMap.Colors);

		int32 transparencyIndex = -1;

		if (hasTransparency)
		{
			transparencyIndex = colorMap.ColorCount;

			++colorMap.ColorCount;
			colorMap.Colors[transparencyIndex] = { 0,0,0 };

			const Color* pSrc = image.data();
			const Color* const pSrcEnd = pSrc + num_pixels;
			GifByteType* pDst = outputBuffer.data();

			while (pSrc != pSrcEnd)
			{
				if (pSrc->a == 0)
				{
					*pDst = 255;
				}

				++pSrc;
				++pDst;
			}
		}

		int error = 0;
		GifFileType* gif = EGifOpen(&writer, detail::GifWriteCallback, &error);
		
		EGifSetGifVersion(gif, true);

		if (EGifPutScreenDesc(gif, width, height, 8, 0, nullptr) == GIF_ERROR)
		{
			EGifCloseFile(gif, &error);
			return false;
		}

		/*
		uint8 param[3] = { 1, 0, 0 };
		EGifPutExtensionLeader(gif, APPLICATION_EXT_FUNC_CODE);
		EGifPutExtensionBlock(gif, 11, "NETSCAPE2.0");
		EGifPutExtensionBlock(gif, 3, param);
		EGifPutExtensionTrailer(gif);
		*/

		GraphicsControlBlock controlBlock;
		controlBlock.DisposalMode		= DISPOSAL_UNSPECIFIED;
		controlBlock.UserInputFlag		= false;
		controlBlock.DelayTime			= 100;
		controlBlock.TransparentColor	= hasTransparency ? transparencyIndex : NO_TRANSPARENT_COLOR;

		GifByteType ext[4];
		EGifGCBToExtension(&controlBlock, ext);

		if (EGifPutExtension(gif, GRAPHICS_EXT_FUNC_CODE, sizeof(ext), ext) == GIF_ERROR)
		{
			EGifCloseFile(gif, &error);
			return false;
		}

		int r = EGifPutImageDesc(gif, 0, 0, width, height, false, &colorMap);

		if (r != GIF_OK)
		{
			EGifCloseFile(gif, &error);
			return false;
		}

		for (int32 y = 0; y < height; ++y)
		{
			if (EGifPutLine(gif, &outputBuffer[y * width], width) == GIF_ERROR)
			{
				EGifCloseFile(gif, &error);
				return false;
			}
		}

		EGifCloseFile(gif, &error);

		return true;
	}

	bool ImageFormat_GIF::save(const Image& image, const FilePath& path) const
	{
		BinaryWriter writer(path);
			
		return encode(image, writer);
	}
}
