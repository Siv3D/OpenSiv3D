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

# include "SDFFontData.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Char.hpp>
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
		m_property.ascender		= static_cast<int32>(m_faceText.face->size->metrics.ascender / 64);
		m_property.descender	= -static_cast<int32>(m_faceText.face->size->metrics.descender / 64);
		m_property.height		= (m_property.ascender + m_property.descender);
		m_property.isBold		= static_cast<bool>(FromEnum(style) & FromEnum(FontStyle::Bold));
		m_property.isItalic		= static_cast<bool>(FromEnum(style) & FromEnum(FontStyle::Italic));

		// Tab 幅を設定
		{
			const FT_UInt spaceGlyphIndex = ::FT_Get_Char_Index(m_faceText.face, U' ');

			if (const FT_Error error = ::FT_Load_Glyph(m_faceText.face, spaceGlyphIndex, FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP))
			{
				m_property.tabWidth = 0;
			}
			else
			{
				m_property.tabWidth = static_cast<int32>((m_faceText.face->glyph->advance.x * 4) / 64);
			}
		}

		String info = U"familyName: {}\n"_fmt(m_property.familyName);
		info += U"styleName: {}\n"_fmt(m_property.styleName);
		info += U"scale: {}\n"_fmt(m_property.scale);
		info += U"baseSize: {}\n"_fmt(m_property.baseSize);
		info += U"ascender: {}\n"_fmt(m_property.ascender);
		info += U"descender: {}\n"_fmt(m_property.descender);
		info += U"height: {}\n"_fmt(m_property.height);
		info += U"isBold: {}\n"_fmt(m_property.isBold);
		info += U"isItalic: {}\n"_fmt(m_property.isItalic);
		info += U"tabWidth: {}"_fmt(m_property.tabWidth);
		LOG_INFO(info);

		m_initialized = true;
	}

	SDFFontData::~SDFFontData()
	{

	}

	bool SDFFontData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const SDFFontProperty& SDFFontData::getProperty() const noexcept
	{
		return m_property;
	}

	const Texture& SDFFontData::getTexture() const
	{
		return m_texture;
	}

	Array<Glyph> SDFFontData::getGlyphs(const StringView codePoints)
	{
		if (!renderGlyphs(codePoints))
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

				m_texture = DynamicTexture(m_image);

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
			m_image.resize(baseWidth, 256, Color(0, 0));
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
			//LOG_TEST(U"E3");
			return false;
		}

		shape.normalize();
		double l = 0, b = 0, r = 0, t = 0;
		shape.bounds(l, b, r, t);
		edgeColoringSimple(shape, 3.0);

		const double scale = m_property.baseSize / m_property.scale;
		const int32 margin = 2;
		const int32 width = static_cast<int32>((std::ceil(r - l) + (margin * 2)) * scale);
		const int32 height = static_cast<int32>((std::ceil(t - b) + (margin * 2)) * scale);
		LOG_INFO(U"{} {} #{}"_fmt(std::ceil((r - l) * scale), std::ceil((t - b) * scale), ((margin * 2) * scale)));
		const Vec2 offset(-l + margin, -b + margin);
		msdfgen::Bitmap<msdfgen::FloatRGB> bitmap(width, height);
		msdfgen::generateMSDF(bitmap, shape, 4.0, scale, msdfgen::Vector2(offset.x, offset.y));

		Image result(width, height, Color(0, 255));
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

			const int32 advanceY = static_cast<int32>(slot->metrics.vertAdvance / 64);

			m_penPos.y += advanceY + ImagePadding * 2;
		}

		if (m_penPos.y + (bitmapHeight + ImagePadding) > m_image.height())
		{
			const int32 newHeight = ((m_penPos.y + (bitmapHeight + ImagePadding)) + 255) / 256 * 256;

			if (newHeight > 4096)
			{
				return false;
			}

			m_image.resizeRows(newHeight, Color(255, 0));
		}

		GlyphInfo info;
		info.bitmapRect.set(m_penPos, bitmapWidth, bitmapHeight);
		info.offset.set(static_cast<int32>(slot->metrics.horiBearingX * scale / 64), static_cast<int32>(m_property.ascender - (slot->metrics.horiBearingY * scale / 64)));
		info.bearingY = static_cast<int32>(slot->metrics.horiBearingY * scale / 64);
		info.xAdvance = static_cast<int32>(slot->metrics.horiAdvance * scale / 64);
		info.yAdvance = static_cast<int32>(slot->metrics.vertAdvance * scale / 64);

		{
			String s = U"glyphIndex [{}]\n"_fmt(glyphIndex);
			s += U"bitmapRect: {}\n"_fmt(info.bitmapRect);
			s += U"offset: {}\n"_fmt(info.offset);
			s += U"bearingY: {}\n"_fmt(info.bearingY);
			s += U"xAdvance: {}\n"_fmt(info.xAdvance);
			s += U"yAdvance: {}\n"_fmt(info.yAdvance);
			LOG_INFO(s);
		}

		result.overwrite(m_image, m_penPos);

		m_penPos.x += bitmapWidth + ImagePadding;

		m_glyphInfos.push_back(info);

		return true;
	}
}
