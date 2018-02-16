//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <cfloat>
# include "FontData.hpp"
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		struct OutLineData
		{
			Array<Array<Array<Vec2>>> contourPaths;

			Vec2 currentPos = Vec2(0, 0);
		};

		int32 MoveTo(const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			data->contourPaths.emplace_back();

			data->currentPos.set(to->x, to->y);

			return 0;
		}

		int32 LineTo(const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			Array<Vec2> line = { data->currentPos, Vec2(to->x, to->y) };

			data->contourPaths.back() << std::move(line);

			data->currentPos.set(to->x, to->y);

			return 0;
		}

		int32 ConicTo(const FT_Vector* c, const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			Array<Vec2> bezier2 = { data->currentPos, Vec2(c->x, c->y), Vec2(to->x, to->y) };

			data->contourPaths.back() << std::move(bezier2);

			data->currentPos.set(to->x, to->y);

			return 0;
		}

		int32 CubicTo(const FT_Vector* c1, const FT_Vector* c2, const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			Array<Vec2> bezier3 = { data->currentPos, Vec2(c1->x, c1->y), Vec2(c2->x, c2->y), Vec2(to->x, to->y) };

			data->contourPaths.back() << std::move(bezier3);

			data->currentPos.set(to->x, to->y);

			return 0;
		}
	}

	FontData::FontData(Null, FT_Library)
	{
		m_initialized = true;
	}

	FontData::FontData(const FT_Library library, const FilePath& filePath, const FilePath& emojiFilePath, const int32 fontSize, const FontStyle style)
	{
		if (!InRange(fontSize, 1, 256))
		{
			return;
		}

		if (const FT_Error error = ::FT_New_Face(library, filePath.narrow().c_str(), 0, &m_faceText.face))
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

		if (const FT_Error error = ::FT_Set_Pixel_Sizes(m_faceText.face, 0, fontSize))
		{
			return;
		}

		if (const FT_Error error = ::FT_New_Face(library, emojiFilePath.narrow().c_str(), 0, &m_faceEmoji.face))
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
			if (const FT_Error error2 = ::FT_Set_Pixel_Sizes(m_faceEmoji.face, 0, fontSize))
			{
				//
			}
		}

		m_familyName	= Unicode::Widen(m_faceText.face->family_name);
		m_styleName		= Unicode::Widen(m_faceText.face->style_name);

		m_fontSize		= fontSize;
		m_ascender		= static_cast<int32>(m_faceText.face->size->metrics.ascender / 64);
		m_descender		= -static_cast<int32>(m_faceText.face->size->metrics.descender / 64);
		m_lineSpacing	= m_ascender + m_descender;
		m_bold			= static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Bold);
		m_italic		= static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Italic);
		m_noBitmap		= !(static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Bitmap));

		const FT_UInt spaceGlyphIndex = ::FT_Get_Char_Index(m_faceText.face, U' ');

		if (const FT_Error error = ::FT_Load_Glyph(m_faceText.face, spaceGlyphIndex, FT_LOAD_DEFAULT | (m_noBitmap ? FT_LOAD_NO_BITMAP : 0)))
		{
			m_tabWidth = fontSize * 4;
		}
		else
		{
			m_tabWidth = static_cast<int32>(m_faceText.face->glyph->metrics.horiAdvance * 4 / 64);
		}	

		m_initialized	= true;
	}

	FontData::~FontData()
	{

	}

	Array<Glyph> FontData::getGlyphs(const String& codePoints)
	{
		if (!render(codePoints))
		{
			return Array<Glyph>(codePoints.size());
		}

		Array<Glyph> glyphs;
		int32 index = 0;

		for (const auto codePoint : codePoints)
		{
			Glyph glyph;
			glyph.codePoint	= codePoint;
			glyph.index		= index;

			if (codePoint == U'\n')
			{

			}
			else if (codePoint == U'\t')
			{
				glyph.xAdvance = m_tabWidth;
			}
			else if (IsControl(codePoint))
			{

			}
			else
			{
				const auto& glyphInfo	= m_glyphs[m_glyphIndexTable[codePoint]];
				glyph.texture			= m_texture(glyphInfo.bitmapRect);
				glyph.offset			= glyphInfo.offset;
				glyph.bearingY			= glyphInfo.bearingY;
				glyph.xAdvance			= glyphInfo.xAdvance;
			}

			glyphs.push_back(glyph);

			++index;
		}

		return glyphs;
	}

	OutlineGlyph FontData::getOutlineGlyph(const char32 codePoint)
	{
		OutlineGlyph outlineGlyph;

		if (!m_faceText)
		{
			return outlineGlyph;
		}

		const FT_UInt glyphIndex = ::FT_Get_Char_Index(m_faceText.face, codePoint);

		if (!glyphIndex)
		{
			return outlineGlyph;
		}

		if (const FT_Error error = FT_Load_Glyph(m_faceText.face, glyphIndex, FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_BITMAP))
		{
			return outlineGlyph;
		}

		FT_Outline_Funcs funcs;
		funcs.move_to	= detail::MoveTo;
		funcs.line_to	= detail::LineTo;
		funcs.conic_to	= detail::ConicTo;
		funcs.cubic_to	= detail::CubicTo;
		funcs.shift		= 0;
		funcs.delta		= 0;

		detail::OutLineData outlineData;
		FT_Outline_Decompose(&m_faceText.face->glyph->outline, &funcs, &outlineData);
		outlineGlyph.contourPaths = outlineData.contourPaths;

		for (auto& contourPath : outlineGlyph.contourPaths)
		{
			for (auto& path : contourPath)
			{
				for (auto& point : path)
				{
					point.x /= 64.0;
					point.y /= -64.0;
				}
			}
		}

		return outlineGlyph;
	}

	RectF FontData::getBoundingRect(const String& codePoints, const double lineSpacingScale)
	{
		if (!render(codePoints))
		{
			return RectF(0);
		}

		Vec2 penPos(0, 0);
		Vec2 minPos(DBL_MAX, DBL_MAX);
		Vec2 maxPos(DBL_MIN, DBL_MIN);

		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = 0;
				penPos.y += m_lineSpacing * lineSpacingScale;
			}
			else if (codePoint == U'\t')
			{
				minPos.x = std::min(minPos.x, penPos.x);
				minPos.y = std::min(minPos.y, penPos.y + m_ascender);
				maxPos.x = std::max(maxPos.x, penPos.x + m_tabWidth);
				maxPos.y = std::max(maxPos.y, penPos.y);
				penPos.x += m_tabWidth;
			}
			else if (!IsControl(codePoint))
			{
				const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
				const RectF region(penPos + glyphInfo.offset, glyphInfo.bitmapRect.size);
				const int32 characterWidth = glyphInfo.bitmapRect.size.isZero() ? glyphInfo.xAdvance : glyphInfo.bitmapRect.size.x;
				minPos.x = std::min(minPos.x, region.x);
				minPos.y = std::min(minPos.y, region.y);
				maxPos.x = std::max(maxPos.x, region.x + characterWidth);
				maxPos.y = std::max(maxPos.y, region.y + region.h);
				penPos.x += glyphInfo.xAdvance;
			}
		}

		if (minPos == Vec2(DBL_MAX, DBL_MAX))
		{
			return RectF(0);
		}

		return RectF(minPos, maxPos - minPos);
	}

	RectF FontData::getRegion(const String& codePoints, const double lineSpacingScale)
	{
		if (!render(codePoints))
		{
			return RectF(0);
		}

		Vec2 penPos(0, 0);
		Vec2 minPos(DBL_MAX, DBL_MAX);
		Vec2 maxPos(DBL_MIN, DBL_MIN);
		int32 lineCount = 0;

		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = 0;
				penPos.y += m_lineSpacing * lineSpacingScale;
				++lineCount;
			}
			else if (codePoint == U'\t')
			{
				minPos.x = std::min(minPos.x, penPos.x);
				minPos.y = std::min(minPos.y, penPos.y + m_ascender);
				maxPos.x = std::max(maxPos.x, penPos.x + m_tabWidth);
				maxPos.y = std::max(maxPos.y, penPos.y);
				penPos.x += m_tabWidth;
			}
			else if (!IsControl(codePoint))
			{
				if (lineCount == 0)
				{
					++lineCount;
				}

				const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
				const RectF region(penPos + glyphInfo.offset, glyphInfo.bitmapRect.size);
				const int32 characterWidth = glyphInfo.xAdvance;
				minPos.x = std::min(minPos.x, region.x);
				minPos.y = std::min(minPos.y, region.y);
				maxPos.x = std::max(maxPos.x, penPos.x + characterWidth);
				maxPos.y = std::max(maxPos.y, region.y + region.h);
				penPos.x += glyphInfo.xAdvance;
			}
		}

		if (minPos == Vec2(DBL_MAX, DBL_MAX))
		{
			return RectF(0);
		}

		return RectF(0, 0, maxPos.x, lineCount * m_lineSpacing * lineSpacingScale);
	}

	Array<int32> FontData::getXAdvances(const String& codePoints)
	{
		if (!render(codePoints))
		{
			return Array<int32>();
		}

		Array<int32> xAdvabces;

		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\t')
			{
				xAdvabces.push_back(m_tabWidth);
			}
			else if (IsControl(codePoint))
			{
				xAdvabces.push_back(0);
			}
			else
			{
				const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
				xAdvabces.push_back(glyphInfo.xAdvance);
			}
		}

		return xAdvabces;
	}

	RectF FontData::draw(const String& codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale)
	{
		if (!render(codePoints))
		{
			return RectF(pos, 0);
		}
		
		Vec2 penPos(pos);
		double maxPosX = DBL_MIN;
		int32 lineCount = 0;
		
		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = pos.x;
				penPos.y += m_lineSpacing * lineSpacingScale;
				++lineCount;
				continue;
			}
			else if (codePoint == U'\t')
			{
				maxPosX = std::max(maxPosX, penPos.x + m_tabWidth);
				penPos.x += m_tabWidth;
				continue;
			}
			else if (!IsControl(codePoint))
			{
				if (lineCount == 0)
				{
					++lineCount;
				}

				const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
				const RectF region = m_texture(glyphInfo.bitmapRect).draw(penPos + glyphInfo.offset, color);
				const int32 characterWidth = glyphInfo.xAdvance;
				maxPosX = std::max(maxPosX, region.x + characterWidth);
				penPos.x += glyphInfo.xAdvance;
			}
		}

		if (!lineCount)
		{
			return RectF(pos, 0);
		}
		
		return RectF(pos, maxPosX - pos.x, lineCount * m_lineSpacing * lineSpacingScale);
	}

	bool FontData::draw(const String& codePoints, const RectF& area, const ColorF& color, const double lineSpacingScale)
	{
		if (!render(codePoints))
		{
			return false;
		}

		const double width = area.w;
		const double height = area.h;

		std::u32string adjustedText;
		bool needDots = false;

		if (m_lineSpacing > height)
		{
			return false;
		}
		
		{
			Vec2 penPos(0, 0);		

			for (const auto& codePoint : codePoints)
			{
				if (codePoint == U'\n')
				{
					penPos.y += m_lineSpacing * lineSpacingScale;

					if (penPos.y + m_lineSpacing <= height)
					{
						penPos.x = 0;
						adjustedText.push_back(U'\n');
						continue;
					}
					else
					{
						needDots = true;
						break;
					}
				}
				else if (codePoint == U'\t')
				{
					const int32 characterWidth = m_tabWidth;

					if (penPos.x + characterWidth <= width)
					{
						penPos.x += characterWidth;
						adjustedText.push_back(codePoint);
						continue;
					}
					else
					{
						penPos.y += m_lineSpacing * lineSpacingScale;

						if (penPos.y + m_lineSpacing <= height)
						{
							if (characterWidth > width)
							{
								return false;
							}

							penPos.x = characterWidth;
							adjustedText.push_back(U'\n');
							adjustedText.push_back(codePoint);
							continue;
						}
						else
						{
							needDots = true;
							break;
						}
					}
				}
				else if (IsControl(codePoint))
				{
					continue;
				}

				const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
				const int32 characterWidth = glyphInfo.offset.x + glyphInfo.bitmapRect.w;

				if (penPos.x + characterWidth <= width)
				{
					penPos.x += glyphInfo.xAdvance;
					adjustedText.push_back(codePoint);
					continue;
				}
				else
				{
					penPos.y += m_lineSpacing * lineSpacingScale;

					if (penPos.y + m_lineSpacing <= height)
					{
						if (glyphInfo.xAdvance > width)
						{
							return false;
						}

						penPos.x = glyphInfo.xAdvance;
						adjustedText.push_back(U'\n');
						adjustedText.push_back(codePoint);
						continue;
					}
					else
					{
						needDots = true;
						break;
					}
				}
			}

			if (needDots)
			{
				if (!render(String(1, U'.')))
				{
					return false;
				}

				const auto& dotGlyph = m_glyphs[m_glyphIndexTable[U'.']];
				const int32 dotWidth = dotGlyph.offset.x + dotGlyph.bitmapRect.w;
				const int32 dotsWidth = dotGlyph.xAdvance * 2 + dotWidth;

				while (!adjustedText.empty())
				{
					const char32 codePoint = adjustedText.back();

					if (codePoint == U'\n')
					{
						break;
					}

					if (width - penPos.x >= dotsWidth)
					{
						break;
					}

					const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
					penPos.x -= glyphInfo.xAdvance;
					adjustedText.pop_back();
				}

				if (width - penPos.x >= dotsWidth)
				{
					adjustedText.append(U"...");
				}
			}
		}

		{
			Vec2 penPos(area.pos);
			int32 lineCount = 0;

			for (const auto& codePoint : adjustedText)
			{
				if (codePoint == U'\n')
				{
					penPos.x = area.x;
					penPos.y += m_lineSpacing * lineSpacingScale;
					++lineCount;
					continue;
				}
				else if (codePoint == U'\t')
				{
					penPos.x += m_tabWidth;

					continue;
				}
				else if (IsControl(codePoint))
				{
					continue;
				}

				if (lineCount == 0)
				{
					++lineCount;
				}

				const auto& glyphInfo = m_glyphs[m_glyphIndexTable[codePoint]];
				m_texture(glyphInfo.bitmapRect).draw(penPos + glyphInfo.offset, color);
				penPos.x += glyphInfo.xAdvance;
			}
		}

		return !needDots;
	}

	bool FontData::render(const String& codePoints)
	{
		if (!m_faceText)
		{
			return false;
		}

		bool hasDirty = false;

		for (const auto& codePoint : codePoints)
		{
			if (m_glyphIndexTable.find(codePoint) != m_glyphIndexTable.end())
			{
				continue;
			}

			const FT_UInt glyphIndexText = ::FT_Get_Char_Index(m_faceText.face, codePoint);
			const FT_UInt glyphIndexEmoji = (glyphIndexText != 0) ? 0 : m_faceEmoji ? ::FT_Get_Char_Index(m_faceEmoji.face, codePoint) : 0;

			if (glyphIndexText == 0 && glyphIndexEmoji == 0)
			{
				if (!m_tofuIndex)
				{
					if (!renderGlyph(m_faceText.face, 0))
					{
						continue;
					}

					hasDirty = true;

					m_tofuIndex = static_cast<CommonGlyphIndex>(m_glyphs.size() - 1);
				}

				m_glyphIndexTable.emplace(codePoint, m_tofuIndex.value());
			}
			else
			{
				const FT_Face face = (glyphIndexText != 0) ? m_faceText.face : m_faceEmoji.face;
				const FT_UInt glyphIndex = (glyphIndexText != 0) ? glyphIndexText : glyphIndexEmoji;

				renderGlyph(face, glyphIndex);

				hasDirty = true;

				m_glyphIndexTable.emplace(codePoint, static_cast<uint32>(m_glyphs.size() - 1));
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
				const bool hasTexture = !!m_texture;
				const Size previousSize = m_texture.size();
				const Size newSize = m_image.size();

				m_texture = DynamicTexture(m_image);

				if (hasTexture)
				{
					LOG_DEBUG(U"ℹ️ Font texture resized ({0}x{1} -> {2}x{3})"_fmt(previousSize.x, previousSize.y, newSize.x, newSize.y));
				}
				else
				{
					LOG_DEBUG(U"ℹ️ Created font texture (size: {0}x{1})"_fmt(newSize.x, newSize.y));
				}
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

			m_image.resize(baseWidth, 256, Color(255, 0));
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
		}

		if (m_penPos.y + (bitmapHeight + padding) > m_image.height())
		{
			const int32 newHeight = ((m_penPos.y + (bitmapHeight + padding)) + 255) / 256 * 256;

			if (newHeight > 4096)
			{
				return false;
			}

			m_image.resizeRows(newHeight, Color(255, 0));
		}

		GlyphInfo info;
		info.bitmapRect.set(m_penPos, bitmapWidth, bitmapHeight);
		info.offset.set(slot->bitmap_left, m_ascender - slot->bitmap_top);
		info.bearingY = static_cast<int32>(slot->bitmap_top);
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
