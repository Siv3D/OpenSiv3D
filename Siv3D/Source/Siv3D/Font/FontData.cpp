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

# include <cfloat>
# include "FontData.hpp"
# include <Siv3D/CharacterSet.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/TextureRegion.hpp>

# include <Siv3D/Logger.hpp>

namespace s3d
{
	FontData::FontData(Null, FT_Library)
	{
		m_initialized = true;
	}

	FontData::FontData(FT_Library library, const String& filePath, const int32 fontSize, const FontStyle style)
	{
		if (!InRange(fontSize, 1, 256))
		{
			return;
		}

		if (const FT_Error error = ::FT_New_Face(library, filePath.narrow().c_str(), 0, &m_faceText))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else if (error)
			{
				// failed to open or load
			}

			return;
		}

		if (const FT_Error error = ::FT_Set_Pixel_Sizes(m_faceText, 0, fontSize))
		{
			return;
		}

		if (const FT_Error error = ::FT_New_Face(library, "engine/font/noto/NotoEmoji-Regular.ttf", 0, &m_faceEmoji))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else if (error)
			{
				// failed to open or load
			}
		}
		else
		{
			if (const FT_Error error2 = ::FT_Set_Pixel_Sizes(m_faceEmoji, 0, fontSize))
			{
				//
			}
		}

		//if (const FT_Error error = ::FT_Set_Char_Size(m_face, 0, fontSize * 64, 96, 96))
		//{
		//	return false;
		//}

		m_fontSize = fontSize;
		m_lineSpacing = static_cast<int32>(m_faceText->size->metrics.height / 64);

		m_bold = static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Bold);
		m_italic = static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Italic);
		m_noBitmap = !(static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Bitmap));

		m_initialized = true;
	}

	FontData::~FontData()
	{
		if (m_faceEmoji)
		{
			::FT_Done_Face(m_faceEmoji);
		}

		if (m_faceText)
		{
			::FT_Done_Face(m_faceText);
		}
	}

	RectF FontData::draw(const String& text, const Vec2& pos, const ColorF& color, double lineSpacingScale)
	{
		const std::u32string codePoints = CharacterSet::ToUTF32(text);
		
		if (!render(codePoints))
		{
			return RectF(pos, 0);
		}
		
		Vec2 penPos(pos);
		Vec2 minPos(DBL_MAX, DBL_MAX);
		Vec2 maxPos(DBL_MIN, DBL_MIN);
		
		for (const auto& codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = pos.x;
				penPos.y += m_lineSpacing * lineSpacingScale;
				continue;
			}
			else if (IsControl(codePoint))
			{
				continue;
			}
		
			const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
			const RectF region = m_texture(glyphInfo.bitmapRect).draw(penPos + glyphInfo.offset, color);
		
			minPos.x = std::min(minPos.x, region.x);
			minPos.y = std::min(minPos.y, region.y);
			maxPos.x = std::max(maxPos.x, region.x + region.w);
			maxPos.y = std::max(maxPos.y, region.y + region.h);
			penPos.x += glyphInfo.xAdvance;
		}
		
		if (minPos == Vec2(DBL_MAX, DBL_MAX))
		{
			return RectF(pos, 0);
		}
		
		return RectF(minPos, maxPos - minPos);
	}

	bool FontData::render(const std::u32string& codePoints)
	{
		bool hasDirty = false;

		for (const auto& codePoint : codePoints)
		{
			if (m_glyphIndexTable.find(codePoint) != m_glyphIndexTable.end())
			{
				continue;
			}

			Log << codePoint << L"----";

			const FT_UInt glyphIndexText = ::FT_Get_Char_Index(m_faceText, codePoint);
			const FT_UInt glyphIndexEmoji = (glyphIndexText != 0) ? 0 : m_faceEmoji ? ::FT_Get_Char_Index(m_faceEmoji, codePoint) : 0;

			Log << glyphIndexText << L", " << glyphIndexEmoji;

			if (glyphIndexText == 0 && glyphIndexEmoji == 0)
			{
				if (!m_tofuIndex)
				{
					if (!renderGlyph(m_faceText, 0))
					{
						continue;
					}

					hasDirty = true;

					m_tofuIndex = m_glyphs.size() - 1;
				}

				m_glyphIndexTable.emplace(codePoint, m_tofuIndex.value());
			}
			else
			{
				const FT_Face face = (glyphIndexText != 0) ? m_faceText : m_faceEmoji;
				const FT_UInt glyphIndex = (glyphIndexText != 0) ? glyphIndexText : glyphIndexEmoji;

				renderGlyph(face, glyphIndex);

				hasDirty = true;

				m_glyphIndexTable.emplace(codePoint, m_glyphs.size() - 1);
			}
		}

		if (hasDirty)
		{
			if (m_image.size() == m_texture.size())
			{
				m_texture.fill(m_image);
			}
			else
			{
				m_texture = DynamicTexture(m_image);
			}
		}

		return true;
	}

	bool FontData::renderGlyph(const FT_Face face, const FT_UInt glyphIndex)
	{
		if (const FT_Error error = ::FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT | (m_noBitmap ? FT_LOAD_NO_BITMAP : 0)))
		{
			return false;
		}

		if (m_bold)
		{
			::FT_GlyphSlot_Embolden(face->glyph);
		}

		if (m_italic)
		{
			::FT_GlyphSlot_Oblique(face->glyph);
		}

		const FT_GlyphSlot slot = face->glyph;
		bool isBitmap = false;

		if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
		{
			if (const FT_Error error = ::FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
			{
				return false;
			}
		}
		else
		{
			isBitmap = true;
		}

		if (!m_image)
		{
			const int32 baseWidth =
				m_fontSize <= 16 ? 512 :
				m_fontSize <= 32 ? 768 :
				m_fontSize <= 48 ? 1024 :
				m_fontSize <= 64 ? 1536 : 2048;

			m_image.resize(baseWidth, 256, Color(0, 0));
		}

		m_penPos.x += padding;
	
		const int32 bitmapWidth = slot->bitmap.width;
		const int32 bitmapHeight = slot->bitmap.rows;
		const int32 bitmapStride = slot->bitmap.pitch;

		if (m_penPos.x + (bitmapWidth + padding) > m_image.width())
		{
			m_penPos.x = padding;

			const int32 advanceY = static_cast<int32>(slot->metrics.vertAdvance / 64);

			m_penPos.y += advanceY + padding * 2;

			if (m_penPos.y + (bitmapHeight + padding) > m_image.height())
			{
				const int32 newHeight = ((m_penPos.y + (bitmapHeight + padding)) + 255) / 256 * 256;

				if (newHeight > 4096)
				{
					return false;
				}

				m_image.resizeRows(newHeight, Color(0, 0));
			}
		}

		GlyphInfo info;
		info.bitmapRect.set(m_penPos, bitmapWidth, bitmapHeight);
		info.offset.set(slot->bitmap_left, m_fontSize - slot->bitmap_top);
		info.xAdvance = static_cast<int32>(slot->metrics.horiAdvance / 64);

		const uint8* bitmapBuffer = slot->bitmap.buffer;

		if (isBitmap)
		{
			const uint8* pSrcLine = bitmapBuffer;

			for (int32 y = 0; y < bitmapHeight; ++y)
			{
				for (int32 x = 0; x < bitmapWidth; ++x)
				{
					const uint32 offsetI = x / 8;
					const uint32 offsetB = 7 - x % 8;

					m_image[m_penPos.y + y][m_penPos.x + x] = Color(255, ((pSrcLine[offsetI] >> offsetB) & 0x1) ? 255: 0);
				}

				pSrcLine += bitmapStride;
			}
		}
		else
		{
			for (int32 y = 0; y < bitmapHeight; ++y)
			{
				for (int32 x = 0; x < bitmapWidth; ++x)
				{
					m_image[m_penPos.y + y][m_penPos.x + x] = Color(255, bitmapBuffer[y * bitmapWidth + x]);
				}
			}
		}

		m_penPos.x += bitmapWidth + padding;

		m_glyphs.push_back(info);

		return true;
	}
}
