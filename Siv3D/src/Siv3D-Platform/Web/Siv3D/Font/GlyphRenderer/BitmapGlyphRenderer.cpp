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

# include <Siv3D/Font/GlyphRenderer/GlyphRenderer.hpp>
# include <Siv3D/Font/GlyphRenderer/BitmapGlyphRenderer.hpp>
# include <Siv3D/Font/FreeType.hpp>

namespace s3d
{
	namespace detail
	{
		__attribute__((import_name("siv3dRenderText")))
		void siv3dRenderText(uint32 codePoint, BitmapGlyph* glyph);

		uint32 searchCodePointFromGlyphIndex(FT_Face face, const GlyphIndex glyphIndex)
		{
			FT_UInt index;
			FT_ULong charCode = ::FT_Get_First_Char( face, &index );

			while (index != 0 && index != glyphIndex)
			{
				charCode = ::FT_Get_Next_Char( face, charCode, &index );
			}

			return charCode;
		}
	}

	BitmapGlyph RenderBitmapGlyph(FT_Face face, const GlyphIndex glyphIndex, const FontFaceProperty& prop)
	{
		BitmapGlyph result;
		uint32 codePoint = detail::searchCodePointFromGlyphIndex(face, glyphIndex);

		if (codePoint == 0)
		{
			return {};
		}

		detail::siv3dRenderText(codePoint, &result);

		const size_t bitmapWidth	= result.width;
		const size_t bitmapHeight	= result.height;

		Image image{ bitmapWidth, bitmapHeight, Color{ 255 } };
		const uint8* bitmapBuffer = reinterpret_cast<uint8*>(result.buffer);
		Color* pDst = image.data();

		const uint8* pSrc = bitmapBuffer;
		const uint8* const pSrcEnd = (pSrc + ((bitmapHeight * bitmapWidth) * 4));

		while (pSrc != pSrcEnd)
		{
			uint8 b = pSrc[0];
			uint8 g = pSrc[1];
			uint8 r = pSrc[2];
			uint8 a = pSrc[3];
			if (InRange<uint8>(a, 1, 254))
			{
				const float t = (255.0f / a);
				r = static_cast<uint8>(r * t);
				g = static_cast<uint8>(g * t);
				b = static_cast<uint8>(b * t);
			}
			pDst->set(r, g, b, a);

			pSrc += 4;
			++pDst;
		}

		std::free(reinterpret_cast<void*>(result.buffer));

		result.buffer = 0;
		result.glyphIndex = glyphIndex;
		result.image = std::move(image);

		if (result.yAdvance == 0)
		{
			result.yAdvance = result.xAdvance;
		}

		return result;
	}
}
