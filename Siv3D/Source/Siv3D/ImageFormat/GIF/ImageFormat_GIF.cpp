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
	static int GifReadCallback(GifFileType* gif, GifByteType* bytes, int size)
	{
		const auto reader = static_cast<IReader*>(gif->UserData);

		return static_cast<int>(reader->read(bytes, size));
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

		return{ 0,0 };
	}

	Image ImageFormat_GIF::decode(IReader& reader) const
	{
		Image image;

		int error;
		GifFileType* gif = DGifOpen(&reader, GifReadCallback, &error);

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
			palette[i].a = (transparentIndex == i ? 0 : 255);
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

		return true;
	}

	bool ImageFormat_GIF::save(const Image& image, const FilePath& path) const
	{
		BinaryWriter writer(path);
			
		return encode(image, writer);
	}
}
