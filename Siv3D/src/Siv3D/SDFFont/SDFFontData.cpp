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
# include "SDFFontData.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Char.hpp>
# include <Siv3D/JSONReader.hpp>
# include <Siv3D/JSONWriter.hpp>
# include <Siv3D/Indexed.hpp>
# include <msdf/msdfgen.h>

namespace s3d
{
	struct FtContext
	{
		msdfgen::Point2 position;
		msdfgen::Shape* shape;
		msdfgen::Contour* contour;
	};

	static msdfgen::Point2 ftPoint2(const FT_Vector& vector)
	{
		return msdfgen::Point2(vector.x / 64., vector.y / 64.);
	}

	static int ftMoveTo(const FT_Vector* to, void* user)
	{
		FtContext* context = reinterpret_cast<FtContext*>(user);
		context->contour = &context->shape->addContour();
		context->position = ftPoint2(*to);
		return 0;
	}

	static int ftLineTo(const FT_Vector* to, void* user)
	{
		FtContext* context = reinterpret_cast<FtContext*>(user);
		context->contour->addEdge(new msdfgen::LinearSegment(context->position, ftPoint2(*to)));
		context->position = ftPoint2(*to);
		return 0;
	}

	static int ftConicTo(const FT_Vector* control, const FT_Vector* to, void* user)
	{
		FtContext* context = reinterpret_cast<FtContext*>(user);
		context->contour->addEdge(new msdfgen::QuadraticSegment(context->position, ftPoint2(*control), ftPoint2(*to)));
		context->position = ftPoint2(*to);
		return 0;
	}

	static int ftCubicTo(const FT_Vector* control1, const FT_Vector* control2, const FT_Vector* to, void* user)
	{
		FtContext* context = reinterpret_cast<FtContext*>(user);
		context->contour->addEdge(new msdfgen::CubicSegment(context->position, ftPoint2(*control1), ftPoint2(*control2), ftPoint2(*to)));
		context->position = ftPoint2(*to);
		return 0;
	}

	SDFFontData::SDFFontData(Null, FT_Library)
	{
		m_initialized = true;
	}

	SDFFontData::SDFFontData(FT_Library library, const FilePath& filePath, const FilePath& emojiFilePath, const int32 baseSize, const FontStyle style)
	{
	# if SIV3D_PLATFORM(WINDOWS)

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

		if (const FT_Error error = ::FT_Set_Pixel_Sizes(m_faceText.face, 0, baseSize))
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

		// フォントのプロパティを設定
		m_property.familyName	= Unicode::Widen(m_faceText.face->family_name);
		m_property.styleName	= Unicode::Widen(m_faceText.face->style_name);
		m_property.scale		= (m_faceText.face->units_per_EM / 64.0);
		m_property.baseSize		= baseSize;
		m_property.ascender		= m_faceText.face->size->metrics.ascender / 64.0;
		m_property.descender	= -m_faceText.face->size->metrics.descender / 64.0;
		m_property.height		= m_property.ascender + m_property.descender;
		m_property.isBold		= static_cast<bool>(FromEnum(style) & FromEnum(FontStyle::Bold));
		m_property.isItalic		= static_cast<bool>(FromEnum(style) & FromEnum(FontStyle::Italic));

		// Tab 幅を設定
		{
			const FT_UInt spaceGlyphIndex = ::FT_Get_Char_Index(m_faceText.face, U' ');

			if (const FT_Error error = ::FT_Load_Glyph(m_faceText.face, spaceGlyphIndex, FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP))
			{
				m_property.tabWidth = 0.0;
			}
			else
			{
				m_property.tabWidth = (m_faceText.face->glyph->advance.x * 4) / 64.0;
			}
		}

		String info = U"familyName: {}\n"_fmt(m_property.familyName);
		info += U"    styleName: {}\n"_fmt(m_property.styleName);
		info += U"    scale: {}\n"_fmt(m_property.scale);
		info += U"    baseSize: {}\n"_fmt(m_property.baseSize);
		info += U"    ascender: {}\n"_fmt(m_property.ascender);
		info += U"    descender: {}\n"_fmt(m_property.descender);
		info += U"    height: {}\n"_fmt(m_property.height);
		info += U"    isBold: {}\n"_fmt(m_property.isBold);
		info += U"    isItalic: {}\n"_fmt(m_property.isItalic);
		info += U"    tabWidth: {}"_fmt(m_property.tabWidth);
		LOG_DEBUG(info);

		m_initialized = true;
	}

	SDFFontData::~SDFFontData()
	{

	}

	bool SDFFontData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	bool SDFFontData::load(const FilePath& imagePath, const FilePath& glyphPath)
	{
		assert(m_image.isEmpty() && m_texture.isEmpty() &&
			m_glyphTable.empty() && m_glyphInfos.empty());

		if (!imagePath || !glyphPath)
		{
			return false;
		}

		Image image(imagePath);

		if (!image)
		{
			return false;
		}

		const JSONReader json(glyphPath);

		if (!json)
		{
			return false;
		}

		if (const String format = json[U"format"].getString();
			format != U"OpenSiv3D MSDF Font")
		{
			return false;
		}

		if (const int32 version = json[U"version"].get<int32>();
			version > 1)
		{
			return false;
		}

		if (const String familyName = json[U"Property.familyName"].getString();
			familyName != m_property.familyName)
		{
			return false;
		}

		if (const String styleName = json[U"Property.styleName"].getString();
			styleName != m_property.styleName)
		{
			return false;
		}

		if (const int32 baseSize = json[U"Property.baseSize"].get<int32>();
			baseSize != m_property.baseSize)
		{
			return false;
		}

		m_image = std::move(image);

		m_texture = DynamicTexture(m_image, TextureDesc::SDF);

		m_penPos = json[U"Property.penPos"].get<Point>();
		
		if (!json[U"Property.nullCharacterIndex"].isNull())
		{
			m_tofuIndex = json[U"Property.nullCharacterIndex"].get<GlyphIndex>();
		}

		for (const auto& codePoint : json[U"CodePoints"].objectView())
		{
			m_glyphTable.emplace(Parse<CodePointVH>(codePoint.name), codePoint.value.get<GlyphIndex>());
		}

		for (const auto& glyph : json[U"Glyphs"].arrayView())
		{
			GlyphInfoF g;
			g.bitmapRect = glyph[U"bitmapRect"].get<RectF>();
			g.offset = glyph[U"offset"].get<Vec2>();
			g.bearingY = glyph[U"bearingY"].get<double>();
			g.xAdvance = glyph[U"xAdvance"].get<double>();
			g.yAdvance = glyph[U"yAdvance"].get<double>();
			m_glyphInfos << g;
		}

		return true;
	}

	const SDFFontProperty& SDFFontData::getProperty() const noexcept
	{
		return m_property;
	}

	const Texture& SDFFontData::getTexture() const
	{
		return m_texture;
	}

	RectF SDFFontData::getBoundingRect(const double fontSize, const StringView codePoints, const double lineSpacingScale)
	{
		if (!renderGlyphs(codePoints))
		{
			return RectF(0);
		}

		const double scale = (fontSize / m_property.baseSize);
		Vec2 penPos(0, 0);
		Vec2 minPos(DBL_MAX, DBL_MAX);
		Vec2 maxPos(DBL_MIN, DBL_MIN);

		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = 0;
				penPos.y += (m_property.height * lineSpacingScale) * scale;
			}
			else if (codePoint == U'\t')
			{
				minPos.x = std::min(minPos.x, penPos.x);
				minPos.y = std::min(minPos.y, penPos.y + (m_property.ascender * scale));
				maxPos.x = std::max(maxPos.x, penPos.x + (m_property.tabWidth * scale));
				maxPos.y = std::max(maxPos.y, penPos.y);
				penPos.x += (m_property.tabWidth * scale);
			}
			else if (!IsControl(codePoint))
			{
				const CodePointVH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphInfos[m_glyphTable[indexVH]];
				const RectF region(penPos + glyphInfo.offset, glyphInfo.bitmapRect.size);
				const double characterWidth = (glyphInfo.bitmapRect.size.isZero() ? glyphInfo.xAdvance : glyphInfo.bitmapRect.size.x) * scale;
				minPos.x = std::min(minPos.x, (region.x * scale));
				minPos.y = std::min(minPos.y, (region.y * scale));
				maxPos.x = std::max(maxPos.x, (region.x * scale + characterWidth));
				maxPos.y = std::max(maxPos.y, (region.y * scale + region.h * scale));
				penPos.x += (glyphInfo.xAdvance * scale);
			}
		}

		if (minPos == Vec2(DBL_MAX, DBL_MAX))
		{
			return RectF(0);
		}

		return RectF(minPos, maxPos - minPos);
	}

	RectF SDFFontData::getRegion(const double fontSize, const StringView codePoints, const double lineSpacingScale)
	{
		if (!renderGlyphs(codePoints))
		{
			return RectF(0);
		}

		const double scale = (fontSize / m_property.baseSize);
		Vec2 penPos(0, 0);
		Vec2 minPos(DBL_MAX, DBL_MAX);
		Vec2 maxPos(DBL_MIN, DBL_MIN);
		int32 lineCount = 0;

		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = 0;
				penPos.y += (m_property.height * lineSpacingScale * scale);
				++lineCount;
			}
			else if (codePoint == U'\t')
			{
				minPos.x = std::min(minPos.x, penPos.x);
				minPos.y = std::min(minPos.y, penPos.y + (m_property.ascender * scale));
				maxPos.x = std::max(maxPos.x, penPos.x + (m_property.tabWidth * scale));
				maxPos.y = std::max(maxPos.y, penPos.y);
				penPos.x += (m_property.tabWidth * scale);
			}
			else if (!IsControl(codePoint))
			{
				if (lineCount == 0)
				{
					++lineCount;
				}

				const CodePointVH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphInfos[m_glyphTable[indexVH]];
				const RectF region(penPos + glyphInfo.offset, glyphInfo.bitmapRect.size);
				const double characterWidth = (glyphInfo.xAdvance * scale);
				minPos.x = std::min(minPos.x, (region.x * scale));
				minPos.y = std::min(minPos.y, (region.y * scale));
				maxPos.x = std::max(maxPos.x, penPos.x + characterWidth);
				maxPos.y = std::max(maxPos.y, (region.y * scale) + (region.h * scale));
				penPos.x += (glyphInfo.xAdvance * scale);
			}
		}

		if (minPos == Vec2(DBL_MAX, DBL_MAX))
		{
			return RectF(0);
		}

		return RectF(0, 0, maxPos.x, lineCount * (m_property.height * lineSpacingScale * scale));
	}

	Array<double> SDFFontData::getXAdvances(const double fontSize, const StringView codePoints)
	{
		if (!renderGlyphs(codePoints))
		{
			return Array<double>();
		}

		const double scale = (fontSize / m_property.baseSize);
		Array<double> xAdvabces;

		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\t')
			{
				xAdvabces.push_back((m_property.tabWidth * scale));
			}
			else if (IsControl(codePoint))
			{
				xAdvabces.push_back(0.0);
			}
			else
			{
				const CodePointVH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphInfos[m_glyphTable[indexVH]];
				xAdvabces.push_back((glyphInfo.xAdvance * scale));
			}
		}

		return xAdvabces;
	}

	void SDFFontData::preload(const StringView codePoints)
	{
		if (!renderGlyphs(codePoints))
		{
			return;
		}
	}

	Array<GlyphF> SDFFontData::getGlyphs(const StringView codePoints)
	{
		if (!renderGlyphs(codePoints))
		{
			return Array<GlyphF>(codePoints.size());
		}

		Array<GlyphF> glyphs;
		int32 index = 0;

		for (const auto codePoint : codePoints)
		{
			GlyphF glyph;
			glyph.codePoint = codePoint;
			glyph.index = index;

			if (codePoint == U'\n')
			{

			}
			else if (codePoint == U'\t')
			{
				glyph.xAdvance = m_property.tabWidth;
			}
			else if (IsControl(codePoint))
			{

			}
			else
			{
				const CodePointVH indexVH = (codePoint | Horizontal);
				const auto& glyphInfo = m_glyphInfos[m_glyphTable[indexVH]];
				glyph.texture = m_texture(glyphInfo.bitmapRect);
				glyph.offset = glyphInfo.offset;
				glyph.bearingY = glyphInfo.bearingY;
				glyph.xAdvance = glyphInfo.xAdvance;
			}

			glyphs.push_back(glyph);

			++index;
		}

		return glyphs;
	}

	bool SDFFontData::saveGlyphs(const FilePathView imagePath, const FilePathView jsonPath)
	{
		if (!m_image.save(FilePath(imagePath)))
		{
			return false;
		}

		JSONWriter json;

		json.startObject();
		{
			json.key(U"format").write(U"OpenSiv3D MSDF Font");
			json.key(U"version").write(1);

			json.key(U"Property").startObject();
			{
				json.key(U"familyName").write(m_property.familyName);
				json.key(U"styleName").write(m_property.styleName);
				json.key(U"baseSize").write(m_property.baseSize);
				json.key(U"penPos").write(m_penPos);

				if (m_tofuIndex)
				{
					json.key(U"nullCharacterIndex").write(m_tofuIndex.value());
				}
				else
				{
					json.key(U"nullCharacterIndex").writeNull();
				}
			}
			json.endObject();

			json.key(U"CodePoints").startObject();
			{
				for (auto[codePoint, glyphIndex] : m_glyphTable)
				{
					json.key(Format(codePoint)).write(glyphIndex);
				}
			}
			json.endObject();

			json.key(U"Glyphs").startArray();
			{
				for (auto[i, glyphInfo] : Indexed(m_glyphInfos))
				{
					json.startObject();
					{
						json.key(U"index").write(i);
						json.key(U"bitmapRect").write(Format(10_dp, glyphInfo.bitmapRect));
						json.key(U"offset").write(glyphInfo.offset);
						json.key(U"bearingY").write(glyphInfo.bearingY);
						json.key(U"xAdvance").write(glyphInfo.xAdvance);
						json.key(U"yAdvance").write(glyphInfo.yAdvance);
					}
					json.endObject();
				}
			}
			json.endArray();
		}
		json.endObject();

		if (!json.save(jsonPath))
		{
			return false;
		}

		return true;
	}

	RectF SDFFontData::draw(const double fontSize, const StringView codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale)
	{
		if (!renderGlyphs(codePoints))
		{
			return RectF(pos, 0);
		}

		const double scale = (fontSize / m_property.baseSize);
		Vec2 penPos(pos);
		double maxPosX = DBL_MIN;
		int32 lineCount = 0;

		for (const auto codePoint : codePoints)
		{
			if (codePoint == U'\n')
			{
				penPos.x = pos.x;
				penPos.y += (m_property.height * lineSpacingScale * scale);
				++lineCount;
				continue;
			}
			else if (codePoint == U'\t')
			{
				maxPosX = std::max(maxPosX, penPos.x + (m_property.tabWidth * scale));
				penPos.x += (m_property.tabWidth * scale);
				continue;
			}
			else if (!IsControl(codePoint))
			{
				if (lineCount == 0)
				{
					++lineCount;
				}

				const CodePointVH indexVH = codePoint | Horizontal;
				const auto& glyphInfo = m_glyphInfos[m_glyphTable[indexVH]];
				const RectF region = m_texture(glyphInfo.bitmapRect).scaled(scale).draw(penPos + (glyphInfo.offset * scale), color);
				const double characterWidth = (glyphInfo.xAdvance * scale);
				maxPosX = std::max(maxPosX, region.x + characterWidth);
				penPos.x += (glyphInfo.xAdvance * scale);
			}
		}

		if (!lineCount)
		{
			return RectF(pos, 0);
		}

		return RectF(pos, maxPosX - pos.x, lineCount * (m_property.height * lineSpacingScale * scale));
	}

	bool SDFFontData::renderGlyphs(const StringView codePoints)
	{
		if (!m_faceText)
		{
			return false;
		}

		bool hasDirty = false;

		for (const auto codePoint : codePoints)
		{
			const CodePointVH codePointVH = (codePoint | Horizontal);

			if (m_glyphTable.contains(codePointVH))
			{
				continue;
			}

			const FT_UInt glyphIndexText = ::FT_Get_Char_Index(m_faceText.face, codePoint);
			const FT_UInt glyphIndexEmoji = (glyphIndexText != 0) ? 0 : m_faceEmoji ? ::FT_Get_Char_Index(m_faceEmoji.face, codePoint) : 0;

			if (glyphIndexText == 0 && glyphIndexEmoji == 0) // tofu
			{
				if (!m_tofuIndex)
				{
					if (!renderGlyph(m_faceText.face, 0))
					{
						continue;
					}

					hasDirty = true;
					m_tofuIndex = static_cast<GlyphIndex>(m_glyphInfos.size() - 1);
				}

				m_glyphTable.emplace(codePointVH, m_tofuIndex.value());
			}
			else
			{
				const FT_Face face = (glyphIndexText != 0) ? m_faceText.face : m_faceEmoji.face;
				const FT_UInt glyphIndex = (glyphIndexText != 0) ? glyphIndexText : glyphIndexEmoji;
				
				if (!renderGlyph(face, glyphIndex))
				{
					continue;
				}

				hasDirty = true;		
				m_glyphTable.emplace(codePointVH, static_cast<uint32>(m_glyphInfos.size() - 1));
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

				m_texture = DynamicTexture(m_image, TextureDesc::SDF);

				if (hasTexture)
				{
					LOG_DEBUG(U"ℹ️ SDFFont texture resized ({0}x{1} -> {2}x{3})"_fmt(previousSize.x, previousSize.y, newSize.x, newSize.y));
				}
				else
				{
					LOG_DEBUG(U"ℹ️ Created SDFFont texture (size: {0}x{1})"_fmt(newSize.x, newSize.y));
				}
			}
		}

		return true;
	}

	bool SDFFontData::renderGlyph(const FT_Face face, const FT_UInt glyphIndex)
	{
		if (const FT_Error error = ::FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT | FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP))
		{
			return false;
		}

		if (m_property.isBold)
		{
			::FT_GlyphSlot_Embolden(face->glyph);
		}

		if (m_property.isItalic)
		{
			::FT_GlyphSlot_Oblique(face->glyph);
		}

		if (!m_image)
		{
			const int32 baseWidth =
				(m_property.baseSize <= 16) ? 512 :
				(m_property.baseSize <= 32) ? 768 :
				(m_property.baseSize <= 48) ? 1024 :
				(m_property.baseSize <= 64) ? 1536 : 2048;
			m_image.resize(baseWidth, 256, BackgroundColor);
		}

		m_penPos.x += ImagePadding;

		msdfgen::Shape shape;
		FtContext context = { };
		context.shape = &shape;
		FT_Outline_Funcs ftFunctions;
		ftFunctions.move_to = &ftMoveTo;
		ftFunctions.line_to = &ftLineTo;
		ftFunctions.conic_to = &ftConicTo;
		ftFunctions.cubic_to = &ftCubicTo;
		ftFunctions.shift = 0;
		ftFunctions.delta = 0;

		const FT_GlyphSlot slot = face->glyph;

		if (const FT_Error error = FT_Outline_Decompose(&slot->outline, &ftFunctions, &context))
		{
			return false;
		}

		shape.normalize();
		edgeColoringSimple(shape, 3.0);
		
		FT_BBox box;
		FT_Outline_Get_CBox(&slot->outline, &box);
		const double l = box.xMin / 64.0;
		const double b = box.yMin / 64.0;
		//const double r = box.xMax / 64.0;
		//const double t = box.yMax / 64.0;

		const double scale = m_property.baseSize / m_property.scale;
		const double boundingWidth = slot->metrics.width * scale / 64;
		const double boundingHeight = slot->metrics.height * scale / 64;
		const double paddingPixel = 1.5;
		const double scaledPadding = (paddingPixel * scale);
		const int32 width = static_cast<int32>(boundingWidth + (scaledPadding * 2) + 0.5);
		const int32 height = static_cast<int32>(boundingHeight + (scaledPadding * 2) + 0.5);
		const Vec2 offset(-l + paddingPixel, -b + paddingPixel);
		msdfgen::Bitmap<msdfgen::FloatRGB> bitmap(width, height);
		msdfgen::generateMSDF(bitmap, shape, 2.0, scale, msdfgen::Vector2(offset.x, offset.y));

		Image result(width, height, Color(BackgroundColor, 255));
		Color* pDst = result.data();

		for (int32 y = height - 1; y >= 0; --y)
		{
			for (int32 x = 0; x < width; ++x)
			{
				const auto& pixel = bitmap(x, y);
				pDst->r = Clamp(int32(pixel.r * 0x100), 0, 255);
				pDst->g = Clamp(int32(pixel.g * 0x100), 0, 255);
				pDst->b = Clamp(int32(pixel.b * 0x100), 0, 255);
				++pDst;
			}
		}

		const int32 bitmapWidth = result.width();
		const int32 bitmapHeight = result.height();

		if (m_penPos.x + (bitmapWidth + ImagePadding) > m_image.width())
		{
			m_penPos.x = ImagePadding;

			const int32 advanceY = static_cast<int32>(slot->metrics.vertAdvance * scale / 64);

			m_penPos.y += advanceY + static_cast<int32>(std::ceil(scaledPadding * 2)) + ImagePadding * 2;
		}

		if (m_penPos.y + (bitmapHeight + ImagePadding) > m_image.height())
		{
			const int32 newHeight = ((m_penPos.y + (bitmapHeight + ImagePadding)) + 255) / 256 * 256;

			if (newHeight > 4096)
			{
				return false;
			}

			m_image.resizeRows(newHeight, BackgroundColor);
		}

		GlyphInfoF info;
		info.bitmapRect.set(m_penPos, bitmapWidth, bitmapHeight);
		info.offset.set(slot->metrics.horiBearingX * scale / 64, m_property.ascender - (slot->metrics.horiBearingY * scale / 64));
		info.bearingY = (slot->metrics.horiBearingY * scale / 64);
		info.xAdvance = (slot->metrics.horiAdvance * scale / 64);
		info.yAdvance = (slot->metrics.vertAdvance * scale / 64);
		info.offset -= Vec2::All(scaledPadding);

		//{
		//	String s = U"***SDF glyphIndex [{}]***\n"_fmt(glyphIndex);
		//	s += U"bitmapRect: {}\n"_fmt(info.bitmapRect);
		//	s += U"offset: {}\n"_fmt(info.offset);
		//	s += U"bearingY: {}\n"_fmt(info.bearingY);
		//	s += U"xAdvance: {}\n"_fmt(info.xAdvance);
		//	s += U"yAdvance: {}\n"_fmt(info.yAdvance);
		//	s += U"height: {}\n"_fmt(slot->metrics.height * scale /64);
		//	LOG_INFO(s);
		//}

		result.overwrite(m_image, m_penPos);

		m_penPos.x += bitmapWidth + ImagePadding;

		m_glyphInfos.push_back(info);

		return true;
	}
}
