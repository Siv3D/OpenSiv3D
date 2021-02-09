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

# include "GlyphRenderer.hpp"
# include "BitmapGlyphRenderer.hpp"
# include "../FreeType.hpp"

namespace s3d
{
	BitmapGlyph RenderBitmapGlyph(FT_Face face, const GlyphIndex glyphIndex, const FontFaceProperty& prop)
	{
		FT_Int32 flag = (FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING);

		if (!(prop.style & FontStyle::Bitmap))
		{
			flag |= FT_LOAD_NO_BITMAP;
		}

		if (::FT_Load_Glyph(face, glyphIndex, flag))
		{
			return{};
		}

		if (prop.style & FontStyle::Bold)
		{
			::FT_GlyphSlot_Embolden(face->glyph);
		}

		if (prop.style & FontStyle::Italic)
		{
			::FT_GlyphSlot_Oblique(face->glyph);
		}

		const GlyphBBox bbox = GetGlyphBound(face);

		bool bitmapFormat = false;
		{
			if (face->glyph->format == FT_GLYPH_FORMAT_BITMAP)
			{
				bitmapFormat = true;
			}
			else
			{
				const FT_Render_Mode mode = (prop.style & FontStyle::Bitmap) ? FT_RENDER_MODE_MONO : FT_RENDER_MODE_NORMAL;

				if (::FT_Render_Glyph(face->glyph, mode))
				{
					return{};
				}
			}
		}

		const size_t bitmapWidth	= face->glyph->bitmap.width;
		const size_t bitmapHeight	= face->glyph->bitmap.rows;
		const int32 bitmapStride	= face->glyph->bitmap.pitch;

		Image image{ bitmapWidth, bitmapHeight, Color{ 255 } };
		const uint8* bitmapBuffer = face->glyph->bitmap.buffer;
		Color* pDst = image.data();

		if (face->glyph->bitmap.pixel_mode == FT_Pixel_Mode::FT_PIXEL_MODE_MONO)
		{
			const uint8* pSrcLine = bitmapBuffer;

			for (size_t y = 0; y < bitmapHeight; ++y)
			{
				for (size_t x = 0; x < bitmapWidth; ++x)
				{
					const size_t offsetI = (x / 8);
					const size_t offsetB = (7 - x % 8);
					const size_t a = ((pSrcLine[offsetI] >> offsetB) & 0x1);
					pDst->a = (a ? 255 : 0);
					++pDst;
				}

				pSrcLine += bitmapStride;
			}
		}
		else if (face->glyph->bitmap.pixel_mode == FT_Pixel_Mode::FT_PIXEL_MODE_GRAY)
		{
			const uint8* pSrc = bitmapBuffer;
			const uint8* const pSrcEnd = (pSrc + (bitmapHeight * bitmapWidth));

			while (pSrc != pSrcEnd)
			{
				pDst->a = *pSrc++;
				++pDst;
			}
		}

		BitmapGlyph result;
		result.glyphIndex	= glyphIndex;
		result.left			= static_cast<int16>(bbox.xMin);
		result.top			= static_cast<int16>(bbox.yMax);
		result.width		= static_cast<int16>(bbox.xMax - bbox.xMin);
		result.height		= static_cast<int16>(bbox.yMax - bbox.yMin);
		result.ascender		= prop.ascender;
		result.descender	= prop.descender;
		result.xAdvance		= (face->glyph->metrics.horiAdvance / 64.0);
		result.yAdvance		= (face->glyph->metrics.vertAdvance / 64.0);
		result.image		= std::move(image);
		return result;
	}
}
