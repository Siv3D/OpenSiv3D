//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <cfloat>
# include "FontData.hpp"
# include FT_OPENTYPE_VALIDATE_H
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		struct OutLineData
		{
			Array<Array<Array<Vec2>>> contourPaths;

			Vec2 currentPos = Vec2(0, 0);
		};

		static int32 MoveTo(const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			data->contourPaths.emplace_back();

			data->currentPos.set(to->x, to->y);

			return 0;
		}

		static int32 LineTo(const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			Array<Vec2> line = { data->currentPos, Vec2(to->x, to->y) };

			data->contourPaths.back() << std::move(line);

			data->currentPos.set(to->x, to->y);

			return 0;
		}

		static int32 ConicTo(const FT_Vector* c, const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			Array<Vec2> bezier2 = { data->currentPos, Vec2(c->x, c->y), Vec2(to->x, to->y) };

			data->contourPaths.back() << std::move(bezier2);

			data->currentPos.set(to->x, to->y);

			return 0;
		}

		static int32 CubicTo(const FT_Vector* c1, const FT_Vector* c2, const FT_Vector* to, void* user)
		{
			OutLineData* data = (OutLineData*)user;

			Array<Vec2> bezier3 = { data->currentPos, Vec2(c1->x, c1->y), Vec2(c2->x, c2->y), Vec2(to->x, to->y) };

			data->contourPaths.back() << std::move(bezier3);

			data->currentPos.set(to->x, to->y);

			return 0;
		}

		static uint16 ToUint16(FT_Bytes p)
		{
			return uint16(((uint16)p[0] << 8) + (uint16)p[1]);
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

	# if defined(SIV3D_TARGET_WINDOWS)

		if (FileSystem::IsResource(filePath))
		{
			m_resource = FontResourceHolder(filePath);

			if (const FT_Error error = ::FT_New_Memory_Face(library, static_cast<const FT_Byte*>(m_resource.data()), static_cast<FT_Long>(m_resource.size()), 0, &m_faceText.face))
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
		}
		else
		{
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
		}
		
	# else
		
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

	# endif

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

		m_familyName = Unicode::Widen(m_faceText.face->family_name);
		m_styleName = Unicode::Widen(m_faceText.face->style_name);

		m_fontSize = fontSize;
		m_ascender = static_cast<int32>(m_faceText.face->size->metrics.ascender / 64);
		m_descender = -static_cast<int32>(m_faceText.face->size->metrics.descender / 64);
		m_lineSpacing = m_ascender + m_descender;
		m_bold = static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Bold);
		m_italic = static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Italic);
		m_noBitmap = !(static_cast<uint32>(style) & static_cast<uint32>(FontStyle::Bitmap));
		//m_width			= (m_faceText.face->bbox.xMax - m_faceText.face->bbox.xMin) / 64;

		const FT_UInt spaceGlyphIndex = ::FT_Get_Char_Index(m_faceText.face, U' ');

		if (const FT_Error error = ::FT_Load_Glyph(m_faceText.face, spaceGlyphIndex, FT_LOAD_DEFAULT | (m_noBitmap ? FT_LOAD_NO_BITMAP : 0)))
		{
			m_tabWidth = fontSize * 4;
		}
		else
		{
			m_tabWidth = static_cast<int32>(m_faceText.face->glyph->metrics.horiAdvance * 4 / 64);
		}

		m_initialized = true;
	}

	FontData::~FontData()
	{

	}

	bool FontData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const String& FontData::getFamilyName() const
	{
		return m_familyName;
	}

	const String& FontData::getStyleName() const
	{
		return m_styleName;
	}

	int32 FontData::getFontSize() const noexcept
	{
		return m_fontSize;
	}

	int32 FontData::getAscent() const noexcept
	{
		return m_ascender;
	}

	int32 FontData::getDescent() const noexcept
	{
		return m_descender;
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
				const char32VH indexVH = codePoint | Horizontal;
				const auto& glyphInfo	= m_glyphs[m_glyphVHIndexTable[indexVH]];
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

	Array<Glyph> FontData::getVerticalGlyphs(const String& codePoints)
	{
		if (!renderVertical(codePoints))
		{
			return Array<Glyph>(codePoints.size());
		}

		Array<Glyph> glyphs;
		int32 index = 0;

		for (const auto codePoint : codePoints)
		{
			Glyph glyph;
			glyph.codePoint = codePoint;
			glyph.index = index;

			if (codePoint == U'\n')
			{

			}
			else if (codePoint == U'\t')
			{
				glyph.xAdvance = m_tabWidth;
				glyph.yAdvance = m_tabWidth;
			}
			else if (IsControl(codePoint))
			{

			}
			else
			{
				const char32VH indexVH = codePoint | Vertical;
				const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
				glyph.texture = m_texture(glyphInfo.bitmapRect);
				glyph.offset = glyphInfo.offset;
				glyph.bearingY = glyphInfo.bearingY;
				glyph.xAdvance = glyphInfo.xAdvance;
				glyph.yAdvance = glyphInfo.yAdvance;
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

	const Texture& FontData::getTexture() const
	{
		return m_texture;
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
				const char32VH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
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

				const char32VH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
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
				const char32VH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
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

				const char32VH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
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

				const char32VH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
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

				const auto& dotGlyph = m_glyphs[m_glyphVHIndexTable[U'.' | Horizontal]];
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

					const char32VH indexVH = codePoint | Horizontal;
					const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
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

				const char32VH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphs[m_glyphVHIndexTable[indexVH]];
				m_texture(glyphInfo.bitmapRect).draw(penPos + glyphInfo.offset, color);
				penPos.x += glyphInfo.xAdvance;
			}
		}

		return !needDots;
	}

	Rect FontData::paint(Image& dst, const bool overwrite, const String& codePoints, const Point& pos, const Color& color, const double lineSpacingScale) const
	{
		Vec2 penPos(pos);
		double maxPosX = DBL_MIN;
		int32 lineCount = 0;
		Image tmpImage;

		for (const auto& codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = pos.x;
				penPos.y += m_lineSpacing * lineSpacingScale;
				++lineCount;
			}
			else if (codePoint == U'\t')
			{
				maxPosX = std::max(maxPosX, penPos.x + m_tabWidth);
				penPos.x += m_tabWidth;
			}
			else if (IsControl(codePoint))
			{

			}
			else
			{
				const char32VH indexVH = codePoint | Horizontal;
				const FT_UInt glyphIndexText = ::FT_Get_Char_Index(m_faceText.face, codePoint);
				const FT_UInt glyphIndexEmoji = (glyphIndexText != 0) ? 0 : m_faceEmoji ? ::FT_Get_Char_Index(m_faceEmoji.face, codePoint) : 0;
				const FT_Face face = (glyphIndexText != 0 || (glyphIndexEmoji == 0)) ? m_faceText.face : m_faceEmoji.face;
				const FT_UInt glyphIndex = (glyphIndexText != 0 || (glyphIndexEmoji == 0)) ? glyphIndexText : glyphIndexEmoji;

				const double startX = penPos.x;
				int32 width = 0, xAdvance = 0;
				paintGlyph(face, glyphIndex, dst, tmpImage, overwrite, penPos.asPoint(), color, width, xAdvance);
				penPos.x += xAdvance;
				maxPosX = std::max(maxPosX, startX + width);
			}
		}

		if (!lineCount)
		{
			return RectF(pos, 0);
		}

		return Rect(pos, static_cast<int32>(maxPosX - pos.x), static_cast<int32>(lineCount * m_lineSpacing * lineSpacingScale));
	}

	void FontData::generateVerticalTable()
	{
		FT_Bytes baseTable = nullptr, gdefTable = nullptr, gposTable = nullptr, gsubTable = nullptr, jstfTable = nullptr;
		int error = ::FT_OpenType_Validate(m_faceText.face, FT_VALIDATE_GSUB, &baseTable, &gdefTable, &gposTable, &gsubTable, &jstfTable);
		
		if (error != 0)
		{
			m_verticalTableInitialized = true;
			return;
		}
	
		uint16 featureOffset = detail::ToUint16(gsubTable + 6);
		FT_Bytes featureList = gsubTable + featureOffset;
		uint16 featureCount = detail::ToUint16(featureList + 0);
		FT_Bytes featureRecords = featureList + 2;

		uint16 lookupOffset = detail::ToUint16(gsubTable + 8);
		FT_Bytes lookupList = gsubTable + lookupOffset;
		//uint16 lookupCount = toUint16(lookupList + 0);
		FT_Bytes lookups = lookupList + 2;

		//Coverageテーブルが指定しているグリフインデックスを読み取る
		auto coverageToIndices = [](FT_Bytes coverage)
		{
			Array<uint16> ret;
			uint16 format = detail::ToUint16(coverage + 0);
			if (format == 1) {
				uint16 count = detail::ToUint16(coverage + 2);
				FT_Bytes indices = coverage + 4;
				for (int i = 0; i < count; i++) {
					ret.push_back(detail::ToUint16(indices + 2 * i));
				}
			}
			else if (format == 2) {
				uint16 count = detail::ToUint16(coverage + 2);
				FT_Bytes rangeRecords = coverage + 4;
				for (int i = 0; i < count; i++) {
					FT_Bytes rangeRecord = rangeRecords + 6 * i;
					uint16 startIndex = detail::ToUint16(rangeRecord + 0);
					uint16 endIndex = detail::ToUint16(rangeRecord + 2);
					for (uint16 j = startIndex; j <= endIndex; j++) {
						ret.push_back(j);
					}
				}
			}
			return ret;
		};

		//Lookupテーブルを読んで、_vertSubstitutionを構築
		auto readLookup = [&](FT_Bytes lookup) {
			uint16 lookupType = detail::ToUint16(lookup + 0);
			if (lookupType != 1) return; //単独置換(type == 1)のみ処理
			uint16 subTableCount = detail::ToUint16(lookup + 4);
			FT_Bytes subTables = lookup + 6;
			for (int i = 0; i < subTableCount; i++) {
				FT_Bytes subTable = lookup + detail::ToUint16(subTables + 2 * i);
				uint16 sbstFormat = detail::ToUint16(subTable + 0);
				if (sbstFormat == 1) {
					FT_Bytes coverage = subTable + detail::ToUint16(subTable + 2);
					int16 deltaGlyphID = (int16)detail::ToUint16(subTable + 4);
					Array<uint16> indices = coverageToIndices(coverage);
					for (size_t k = 0; k < indices.size(); ++k) {
						int outputIndex = (int)indices[k] + deltaGlyphID;
						if (outputIndex < 0) outputIndex += 65536;
						else if (outputIndex >= 65536) outputIndex -= 65536;
						m_verticalTable.emplace(indices[k], (uint16)outputIndex);
					}
				}
				else if (sbstFormat == 2) {
					FT_Bytes coverage = subTable + detail::ToUint16(subTable + 2);
					//uint16 count = toUint16(subTable + 4); //indices.size()と同じはずなので使わない
					FT_Bytes substitutes = subTable + 6;
					Array<uint16> indices = coverageToIndices(coverage);
					for (uint16 k = 0; k < indices.size(); k++) {
						uint16 outputIndex = detail::ToUint16(substitutes + 2 * k);
						m_verticalTable.emplace(indices[k], outputIndex);
					}
				}
			}
		};

		//vertフィーチャー(縦書き用グリフ置換の機能)を見つけて、内部の置換情報を読みに行く
		//厳密には、使いたい文字体系(Script)と言語体系(Language)を選択した上で対応するfeatureだけを読むべき。それをすると呼び出し側がScriptとLanguageを選択する必要が出てきて複雑になるので、とりあえずvertとついたfeatureを全部読んでいる。縦書きへのグリフ置換しか利用しないなら大きな問題はないと思われる
		for (uint16 i = 0; i < featureCount; ++i)
		{
			FT_Bytes featureRecord = featureRecords + 6 * i;

			if (featureRecord[0] != 'v'
				|| featureRecord[1] != 'e'
				|| featureRecord[2] != 'r'
				|| featureRecord[3] != 't')
			{
				continue;
			}

			FT_Bytes feature = featureList + detail::ToUint16(featureRecord + 4);
			uint16 featureLookupCount = detail::ToUint16(feature + 2);
			FT_Bytes lookupIndices = feature + 4;
			for (int j = 0; j < featureLookupCount; j++) {
				uint16 lookupIndex = ((uint16)lookupIndices[2 * j]) + lookupIndices[2 * j + 1];
				uint16 lookupTableOffset = ((uint16)lookups[2 * lookupIndex] << 8) + (uint16)lookups[2 * lookupIndex + 1];
				FT_Bytes lookup = lookupList + lookupTableOffset;
				readLookup(lookup);
			}
		}

		::FT_OpenType_Free(m_faceText.face, baseTable);
		::FT_OpenType_Free(m_faceText.face, gdefTable);
		::FT_OpenType_Free(m_faceText.face, gposTable);
		::FT_OpenType_Free(m_faceText.face, gsubTable);
		::FT_OpenType_Free(m_faceText.face, jstfTable);

		m_verticalTableInitialized = true;

		LOG_DEBUG(U"ℹ️ Vertical glyph table generated (table size: {0})"_fmt(m_verticalTable.size()));

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
			const char32VH indexVH = codePoint | Horizontal;

			if (m_glyphVHIndexTable.find(indexVH) != m_glyphVHIndexTable.end())
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

				m_glyphVHIndexTable.emplace(indexVH, m_tofuIndex.value());
			}
			else
			{
				const FT_Face face = (glyphIndexText != 0) ? m_faceText.face : m_faceEmoji.face;
				const FT_UInt glyphIndex = (glyphIndexText != 0) ? glyphIndexText : glyphIndexEmoji;

				renderGlyph(face, glyphIndex);

				hasDirty = true;

				m_glyphVHIndexTable.emplace(indexVH, static_cast<uint32>(m_glyphs.size() - 1));
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
				[[maybe_unused]] const Size previousSize = m_texture.size();
				[[maybe_unused]] const Size newSize = m_image.size();

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

	bool FontData::renderVertical(const String& codePoints)
	{
		if (!m_faceText)
		{
			return false;
		}

		if (!m_verticalTableInitialized)
		{
			generateVerticalTable();
		}

		bool hasDirty = false;

		for (const auto& codePoint : codePoints)
		{
			const char32VH indexVH = codePoint | Vertical;

			if (m_glyphVHIndexTable.find(indexVH) != m_glyphVHIndexTable.end())
			{
				continue;
			}

			const FT_UInt glyphIndexText = ::FT_Get_Char_Index(m_faceText.face, codePoint);
			const FT_UInt glyphIndexEmoji = (glyphIndexText != 0) ? 0 : m_faceEmoji ? ::FT_Get_Char_Index(m_faceEmoji.face, codePoint) : 0;
			const bool isEmoji = (glyphIndexText == 0) && (glyphIndexEmoji != 0);

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

				m_glyphVHIndexTable.emplace(indexVH, m_tofuIndex.value());
			}
			else if (isEmoji)
			{
				const auto it = m_glyphVHIndexTable.find(codePoint);

				if (it == m_glyphVHIndexTable.end())
				{
					renderGlyph(m_faceEmoji.face, glyphIndexEmoji);

					hasDirty = true;

					const CommonGlyphIndex index = static_cast<uint32>(m_glyphs.size() - 1);

					m_glyphVHIndexTable.emplace(codePoint | Horizontal, index);
					m_glyphVHIndexTable.emplace(codePoint | Vertical, index);
				}
				else
				{
					const CommonGlyphIndex index = it->second;
					m_glyphVHIndexTable.emplace(codePoint | Vertical, index);
				}
			}
			else
			{
				const auto itV = m_verticalTable.find(static_cast<uint16>(glyphIndexText));
				const bool hasVerticalGlyph = (itV != m_verticalTable.end());

				if (hasVerticalGlyph)
				{
					renderGlyph(m_faceText.face, itV->second);

					hasDirty = true;

					const CommonGlyphIndex index = static_cast<uint32>(m_glyphs.size() - 1);

					m_glyphVHIndexTable.emplace(codePoint | Vertical, index);
				}
				else
				{
					const auto it = m_glyphVHIndexTable.find(codePoint);

					if (it == m_glyphVHIndexTable.end())
					{
						renderGlyph(m_faceText.face, glyphIndexText);

						hasDirty = true;

						const CommonGlyphIndex index = static_cast<uint32>(m_glyphs.size() - 1);

						m_glyphVHIndexTable.emplace(codePoint | Horizontal, index);
						m_glyphVHIndexTable.emplace(codePoint | Vertical, index);
					}
					else
					{
						const CommonGlyphIndex index = it->second;
						m_glyphVHIndexTable.emplace(codePoint | Vertical, index);
					}
				}
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
				[[maybe_unused]] const Size previousSize = m_texture.size();
				[[maybe_unused]] const Size newSize = m_image.size();

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
		info.yAdvance = static_cast<int32>(slot->metrics.vertAdvance / 64);

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

	void FontData::paintGlyph(FT_Face face, FT_UInt glyphIndex, Image& image, Image& tmpImage, const bool overwrite, const Point& penPos, const Color& color, int32& width, int32& xAdvance) const
	{
		if (const FT_Error error = ::FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT | (m_noBitmap ? FT_LOAD_NO_BITMAP : 0)))
		{
			return;
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
				return;
			}
		}
		else
		{
			isBitmap = true;
		}

		const int32 bitmapWidth = slot->bitmap.width;
		const int32 bitmapHeight = slot->bitmap.rows;
		const int32 bitmapStride = slot->bitmap.pitch;
		const uint8* bitmapBuffer = slot->bitmap.buffer;
		const Point offset(slot->bitmap_left, m_ascender - slot->bitmap_top);

		width = bitmapWidth;
		xAdvance = static_cast<int32>(slot->metrics.horiAdvance / 64);

		tmpImage.resize(bitmapWidth, bitmapHeight);

		if (!tmpImage)
		{
			return;
		}

		Color* pDst = tmpImage.data();

		if (isBitmap)
		{
			const uint8* pSrcLine = bitmapBuffer;

			for (int32 y = 0; y < bitmapHeight; ++y)
			{
				for (int32 x = 0; x < bitmapWidth; ++x)
				{
					const uint32 offsetI = x / 8;
					const uint32 offsetB = 7 - x % 8;

					(*pDst++) = Color(255, ((pSrcLine[offsetI] >> offsetB) & 0x1) ? 255 : 0);
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
					(*pDst++) = Color(255, (*bitmapBuffer++));
				}
			}
		}

		if (overwrite)
		{
			tmpImage.overwrite(image, penPos + offset, color);
		}
		else
		{
			tmpImage.paint(image, penPos + offset, color);
		}
	}
}
