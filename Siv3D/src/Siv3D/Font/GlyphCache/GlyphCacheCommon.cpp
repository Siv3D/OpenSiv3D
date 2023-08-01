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

# include "GlyphCacheCommon.hpp"

namespace s3d
{
	double GetTabAdvance(const double spaceWidth, const double scale, const double baseX, const double currentX, const int32 indentSize)
	{
		const double maxTabWidth = (spaceWidth * scale * indentSize);
		const int32 indentLevel = static_cast<int32>(((currentX + maxTabWidth) - baseX) / maxTabWidth);
		double newX = (baseX + indentLevel * maxTabWidth);
		// 戻り値が 0 になる場合は、浮動小数点数の誤差により indentLevel が 1 だけ小さく計算されている
		if ((newX - currentX) == 0)
		{
			// indentLevel を 1 だけ増やして再計算
			newX = (baseX + (indentLevel + 1) * maxTabWidth);
		}
		return (newX - currentX);
	}

	bool ProcessControlCharacter(const char32 ch, Vec2& penPos, int32& line, const Vec2& basePos, const double scale, const double lineHeightScale, const FontFaceProperty& prop)
	{
		if (not IsControl(ch))
		{
			return false;
		}

		switch (ch)
		{
		case U'\t':
			{
				penPos.x += GetTabAdvance(prop.spaceWidth, scale, basePos.x, penPos.x, prop.indentSize);
				break;
			}
		case U'\n':
			penPos.x = basePos.x;
			penPos.y += (prop.height() * scale * lineHeightScale);
			++line;
			break;
		default:
			break;
		}

		return true;
	}

	bool CacheGlyph(const FontData& font, const Image& image, const GlyphInfo& glyphInfo,
		BufferImage& buffer, HashTable<GlyphIndex, GlyphCache>& glyphTable)
	{
		if (not buffer.image)
		{
			const int32 fontSize = font.getProperty().fontPixelSize;
			const int32 baseWidth =
				fontSize <= 16 ? 512 :
				fontSize <= 32 ? 768 :
				fontSize <= 48 ? 1024 :
				fontSize <= 64 ? 1536 :
				fontSize <= 256 ? 2048 : 4096;
			const int32 baseHeight = (fontSize <= 256 ? 256 : 512);
			buffer.image.resize(baseWidth, baseHeight, buffer.backgroundColor);
		}

		buffer.penPos.x += buffer.padding;

		const int32 bitmapWidth		= image.width();
		const int32 bitmapHeight	= image.height();

		if (buffer.image.width() < (buffer.penPos.x + (bitmapWidth + buffer.padding)))
		{
			buffer.penPos.x = buffer.padding;
			buffer.penPos.y += (buffer.currentMaxHeight + (buffer.padding * 2));
			buffer.currentMaxHeight = 0;
		}

		if (buffer.image.height() < (buffer.penPos.y + (bitmapHeight + buffer.padding)))
		{
			const int32 newHeight = ((buffer.penPos.y + (bitmapHeight + buffer.padding)) + 255) / 256 * 256;

			if (BufferImage::MaxImageHeight < newHeight)
			{
				return false;
			}

			buffer.image.resizeRows(newHeight, buffer.backgroundColor);
		}

		image.overwrite(buffer.image, buffer.penPos);

		GlyphCache cache;
		cache.info					= glyphInfo;
		cache.textureRegionLeft		= static_cast<int16>(buffer.penPos.x);
		cache.textureRegionTop		= static_cast<int16>(buffer.penPos.y);
		cache.textureRegionWidth	= static_cast<int16>(bitmapWidth);
		cache.textureRegionHeight	= static_cast<int16>(bitmapHeight);
		glyphTable.emplace(glyphInfo.glyphIndex, cache);

		buffer.currentMaxHeight = Max(buffer.currentMaxHeight, bitmapHeight);
		buffer.penPos.x += (bitmapWidth + buffer.padding);

		return true;
	}
}
