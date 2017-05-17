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
# include <Siv3D/TextureRegion.hpp>

namespace s3d
{
	FontData::FontData(Null, FT_Library)
	{
		m_initialized = true;
	}

	FontData::FontData(FT_Library library, const String& filePath, const int32 fontSize)
	{
		if (!InRange(fontSize, 1, 256))
		{
			return;
		}

		if (const FT_Error error = ::FT_New_Face(library, filePath.narrow().c_str(), 0, &m_face))
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

		if (const FT_Error error = ::FT_Set_Pixel_Sizes(m_face, 0, fontSize))
		{
			return;
		}

		//if (const FT_Error error = ::FT_Set_Char_Size(m_face, 0, fontSize * 64, 96, 96))
		//{
		//	return false;
		//}

		m_fontSize = fontSize;
		m_lineSpacing = (m_face->size->metrics.height / 64);

		m_initialized = true;
	}

	FontData::~FontData()
	{
		if (m_face)
		{
			::FT_Done_Face(m_face);
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

			const FT_UInt glyphIndex = ::FT_Get_Char_Index(m_face, codePoint);

			m_glyphIndexTable.emplace(codePoint, glyphIndex);

			if (m_glyphs.find(glyphIndex) != m_glyphs.end())
			{
				continue;
			}

			if (const FT_Error error = ::FT_Load_Glyph(m_face, glyphIndex, FT_LOAD_DEFAULT))
			{
				continue;
			}

			const FT_GlyphSlot slot = m_face->glyph;

			if (m_face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			{
				if (const FT_Error error = ::FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
				{
					return false;
				}
			}

			const uint8* bitmapBuffer = slot->bitmap.buffer;
			const int32 bitmapWidth = slot->bitmap.width;
			const int32 bitmapHeight = slot->bitmap.rows;

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

			for (int32 y = 0; y < bitmapHeight; ++y)
			{
				for (int32 x = 0; x < bitmapWidth; ++x)
				{
					m_image[m_penPos.y + y][m_penPos.x + x] = Color(255, bitmapBuffer[y * bitmapWidth + x]);
				}
			}

			hasDirty = true;

			m_penPos.x += bitmapWidth + padding;

			m_glyphs.emplace(glyphIndex, info);
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
}
