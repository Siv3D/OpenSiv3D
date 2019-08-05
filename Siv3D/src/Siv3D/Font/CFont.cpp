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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Compression.hpp>
# include <Siv3D/Image.hpp>
# include <EngineDirectory/EngineDirectory.hpp>
# include "CFont.hpp"

namespace s3d
{
	namespace detail
	{
		enum class StandardFont
		{
			MPlusThin,
			MPlusLight,
			MPlusRegular,
			MPlusMedium,
			MPlusBold,
			MPlusHeavy,
			MPlusBlack,
			NotoEmojiRegular,
			NotoColorEmoji,
			AwesomeSolid,
			AwesomeBrands,
		};

		static constexpr std::array<FilePathView, 11> StandardFontNames =
		{
			U"mplus/mplus-1p-thin.ttf"_sv,
			U"mplus/mplus-1p-light.ttf"_sv,
			U"mplus/mplus-1p-regular.ttf"_sv,
			U"mplus/mplus-1p-medium.ttf"_sv,
			U"mplus/mplus-1p-bold.ttf"_sv,
			U"mplus/mplus-1p-heavy.ttf"_sv,
			U"mplus/mplus-1p-black.ttf"_sv,
			U"noto/NotoEmoji-Regular.ttf"_sv,
			U"noto/NotoColorEmoji.ttf"_sv,
			U"fontawesome/fontawesome-solid.otf"_sv,
			U"fontawesome/fontawesome-brands.otf"_sv,
		};

		[[nodiscard]] static FilePath GetEngineFontDirectory()
		{
			return EngineDirectory::CurrectVersionCommon() + U"font/";
		}

		[[nodiscard]] FilePath GetEngineFontPath(const Typeface typeface)
		{
			return GetEngineFontDirectory() + StandardFontNames[FromEnum(typeface)];
		}

		[[nodiscard]] static bool ExtractFontFiles()
		{
			const FilePath fontDirectory = EngineDirectory::CurrectVersionCommon() + U"font/";

			for (const auto& fontName : detail::StandardFontNames)
			{
				const FilePath fontResourcePath = Resource(U"engine/font/" + fontName + U".zstdcmp");

				if (!FileSystem::Exists(fontDirectory + fontName)
					&& FileSystem::Exists(fontResourcePath))
				{
					if (!Compression::DecompressFileToFile(fontResourcePath, fontDirectory + fontName))
					{
						return false;
					}
				}
			}

			return true;
		}
	}

	CFont::CFont()
	{

	}

	CFont::~CFont()
	{
		LOG_TRACE(U"CFont::~CFont()");

		m_fonts.destroy();

		m_awesomeIconBrands.destroy();
		m_awesomeIconSolid.destroy();
		m_colorEmoji.destroy();

		if (m_freeType)
		{
			::FT_Done_FreeType(m_freeType);
		}
	}

	void CFont::init()
	{
		LOG_TRACE(U"CFont::init()");

		if (const FT_Error error = ::FT_Init_FreeType(&m_freeType))
		{
			throw EngineError(U"FT_Init_FreeType() faild");
		}

		if (!detail::ExtractFontFiles())
		{
			throw EngineError(U"ExtractFontFiles() faild");
		}

		if (!loadColorEmojiFace())
		{
			LOG_INFO(U"ℹ️ ColorEmoji not included");
		}

		if (!loadAwesomeIconFace())
		{
			LOG_INFO(U"ℹ️ Icon font not included");
		}

		auto nullFont = std::make_unique<FontData>(FontData::Null{}, m_freeType);

		if (!nullFont->isInitialized())
		{
			throw EngineError(U"Null Font initialization failed");
		}

		m_fonts.setNullData(std::move(nullFont));

		LOG_INFO(U"ℹ️ CFont initialized");
	}

	Image CFont::getColorEmoji(const StringView emoji)
	{
		if (!m_colorEmoji)
		{
			return Image();
		}

		const auto glyphs = m_colorEmoji.get(emoji);

		if (glyphs.second != 1)
		{
			return Image();
		}

		const uint32_t glyphIndex = glyphs.first[0].codepoint;

		if (glyphIndex == 0)
		{
			return Image();
		}

		const FT_Face face = m_colorEmoji.face;

		if (const FT_Error error = ::FT_Load_Glyph(face, glyphIndex, FT_LOAD_COLOR))
		{
			return Image();
		}

		if (const FT_Error error = ::FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
		{
			return Image();
		}

		const int32 bitmapWidth = face->glyph->bitmap.width;
		const int32 bitmapHeight = face->glyph->bitmap.rows;

		Image image(bitmapWidth, bitmapHeight);

		Color* pDst = image.data();
		Color* const pDstEnd = pDst + image.num_pixels();
		const uint8_t* pSrc = face->glyph->bitmap.buffer;

		while (pDst != pDstEnd)
		{
			uint8 r = pSrc[2], g = pSrc[1], b = pSrc[0], a = pSrc[3];

			if (0 < a&& a < 254)
			{
				const float t = 255.0f / a;
				r = static_cast<uint8>(r * t);
				g = static_cast<uint8>(g * t);
				b = static_cast<uint8>(b * t);
			}

			pDst->set(r, g, b, a);

			++pDst;
			pSrc += 4;
		}

		return image;
	}

	Image CFont::getColorEmojiSilhouette(const StringView emoji)
	{
		if (!m_colorEmoji)
		{
			return Image();
		}

		const auto glyphs = m_colorEmoji.get(emoji);

		if (glyphs.second != 1)
		{
			return Image();
		}

		const uint32_t glyphIndex = glyphs.first[0].codepoint;

		if (glyphIndex == 0)
		{
			return Image();
		}

		const FT_Face face = m_colorEmoji.face;

		if (const FT_Error error = ::FT_Load_Glyph(face, glyphIndex, FT_LOAD_COLOR))
		{
			return Image();
		}

		if (const FT_Error error = ::FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
		{
			return Image();
		}

		const int32 bitmapWidth = face->glyph->bitmap.width;
		const int32 bitmapHeight = face->glyph->bitmap.rows;

		Image image(bitmapWidth, bitmapHeight, Palette::White);

		Color* pDst = image.data();
		Color* const pDstEnd = pDst + image.num_pixels();
		const uint8_t* pSrc = face->glyph->bitmap.buffer + 3;

		while (pDst != pDstEnd)
		{
			pDst->setA(*pSrc);
			++pDst;
			pSrc += 4;
		}

		return image;
	}

	Image CFont::getAwesomeIcon(const uint16 code, int32 size)
	{
		if (!m_awesomeIconSolid || !m_awesomeIconBrands || size < 1)
		{
			return Image();
		}

		size = std::max(size - 2, 1);

		FT_Face face = m_awesomeIconSolid.face;

		FT_UInt glyphIndex = ::FT_Get_Char_Index(face, code);

		if (glyphIndex == 0)
		{
			face = m_awesomeIconBrands.face;

			glyphIndex = ::FT_Get_Char_Index(face, code);

			if (glyphIndex == 0)
			{
				return Image();
			}
		}

		if (const FT_Error error = ::FT_Set_Pixel_Sizes(face, 0, size))
		{
			return Image();
		}

		if (const FT_Error error = ::FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP))
		{
			return Image();
		}

		const FT_GlyphSlot slot = face->glyph;

		if (const FT_Error error = ::FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
		{
			return Image();
		}

		const int32 bitmapWidth = slot->bitmap.width;
		const int32 bitmapHeight = slot->bitmap.rows;

		Image image(bitmapWidth + 2, bitmapHeight + 2, Color(255, 0));
		const uint8* bitmapBuffer = slot->bitmap.buffer;

		for (int32 y = 0; y < bitmapHeight; ++y)
		{
			for (int32 x = 0; x < bitmapWidth; ++x)
			{
				image[y + 1][x + 1].a = bitmapBuffer[y * bitmapWidth + x];
			}
		}

		return image;
	}

	Optional<const FontFace&> CFont::getAwesomeIconFontFaceFotCode(const uint16 code) const
	{
		if (!m_awesomeIconSolid || !m_awesomeIconBrands)
		{
			return none;
		}

		if (::FT_Get_Char_Index(m_awesomeIconSolid.face, code))
		{
			return m_awesomeIconSolid;
		}
		else if (::FT_Get_Char_Index(m_awesomeIconBrands.face, code))
		{
			return m_awesomeIconBrands;
		}
		else
		{
			return none;
		}
	}

	FontID CFont::create(const Typeface typeface, const int32 fontSize, const FontStyle style)
	{
		return create(detail::GetEngineFontPath(typeface), fontSize, style);
	}

	FontID CFont::create(const FilePath& path, const int32 fontSize, const FontStyle style)
	{
		const FilePath emojiPath = detail::GetEngineFontDirectory()
			+ detail::StandardFontNames[FromEnum(detail::StandardFont::NotoEmojiRegular)];

		auto font = std::make_unique<FontData>(m_freeType, path, emojiPath, fontSize, style);

		if (!font->isInitialized())
		{
			return FontID::NullAsset();
		}

		const String info = U"(`{0} {1}` size: {2})"_fmt(font->getFamilyName(), font->getStyleName(), fontSize);

		return m_fonts.add(std::move(font), info);
	}

	void CFont::release(const FontID handleID)
	{
		m_fonts.erase(handleID);
	}

	const String& CFont::getFamilyName(const FontID handleID)
	{
		return m_fonts[handleID]->getFamilyName();
	}

	const String& CFont::getStyleName(const FontID handleID)
	{
		return m_fonts[handleID]->getStyleName();
	}

	int32 CFont::getFontSize(const FontID handleID)
	{
		return m_fonts[handleID]->getFontSize();
	}

	int32 CFont::getAscent(const FontID handleID)
	{
		return m_fonts[handleID]->getAscent();
	}

	int32 CFont::getDescent(const FontID handleID)
	{
		return m_fonts[handleID]->getDescent();
	}

	Array<Glyph> CFont::getGlyphs(const FontID handleID, const String& codePoints)
	{
		return m_fonts[handleID]->getGlyphs(codePoints);
	}

	Array<Glyph> CFont::getVerticalGlyphs(FontID handleID, const String& codePoints)
	{
		return m_fonts[handleID]->getVerticalGlyphs(codePoints);
	}

	OutlineGlyph CFont::getOutlineGlyph(const FontID handleID, const char32 codePoint)
	{
		return m_fonts[handleID]->getOutlineGlyph(codePoint);
	}

	const Texture& CFont::getTexture(const FontID handleID)
	{
		return m_fonts[handleID]->getTexture();
	}

	RectF CFont::getBoundingRect(FontID handleID, const String& codePoints, const double lineSpacingScale)
	{
		return m_fonts[handleID]->getBoundingRect(codePoints, lineSpacingScale);
	}

	RectF CFont::getRegion(FontID handleID, const String& codePoints, const double lineSpacingScale)
	{
		return m_fonts[handleID]->getRegion(codePoints, lineSpacingScale);
	}

	Array<int32> CFont::getXAdvances(FontID handleID, const String& codePoints)
	{
		return m_fonts[handleID]->getXAdvances(codePoints);
	}

	RectF CFont::draw(const FontID handleID, const String& codePoints, const Vec2& pos, const ColorF& color, const double lineSpacingScale)
	{
		return m_fonts[handleID]->draw(codePoints, pos, color, lineSpacingScale);
	}

	bool CFont::draw(const FontID handleID, const String& codePoints, const RectF& area, const ColorF& color, const double lineSpacingScale)
	{
		return m_fonts[handleID]->draw(codePoints, area, color, lineSpacingScale);
	}

	Rect CFont::paint(const FontID handleID, Image& dst, const String& codePoints, const Point& pos, const Color& color, const double lineSpacingScale)
	{
		return m_fonts[handleID]->paint(dst, false, codePoints, pos, color, lineSpacingScale);
	}

	Rect CFont::overwrite(const FontID handleID, Image& dst, const String& codePoints, const Point& pos, const Color& color, const double lineSpacingScale)
	{
		return m_fonts[handleID]->paint(dst, true, codePoints, pos, color, lineSpacingScale);
	}

	bool CFont::loadColorEmojiFace()
	{
		const FilePath path = detail::GetEngineFontDirectory()
			+ detail::StandardFontNames[FromEnum(detail::StandardFont::NotoColorEmoji)];

		if (!FileSystem::Exists(path))
		{
			return false;
		}

		if (const FT_Error error = ::FT_New_Face(m_freeType, path.narrow().c_str(), 0, &m_colorEmoji.face))
		{
			return false;
		}

		FT_ULong length = 0;

		const FT_Face face = m_colorEmoji.face;

		if (const FT_Error error = ::FT_Load_Sfnt_Table(face, FT_MAKE_TAG('C', 'B', 'D', 'T'), 0, nullptr, &length))
		{
			return false;
		}

		if (!length)
		{
			return false;
		}

		if (face->num_fixed_sizes == 0)
		{
			return false;
		}

		int32 bestMatch = 0;
		int32 diff = std::abs(128 - face->available_sizes[0].width);

		for (int32 i = 1; i < face->num_fixed_sizes; ++i)
		{
			const int32 ndiff = std::abs(128 - face->available_sizes[i].width);

			if (ndiff < diff)
			{
				bestMatch = i;
				diff = ndiff;
			}
		}

		if (const FT_Error error = ::FT_Select_Size(face, bestMatch))
		{
			return false;
		}

		m_colorEmoji.hbFont = ::hb_ft_font_create_referenced(face);

		if (!m_colorEmoji.hbFont)
		{
			return false;
		}

		return true;
	}

	bool CFont::loadAwesomeIconFace()
	{
		// solid
		{
			const FilePath path = detail::GetEngineFontDirectory()
				+ detail::StandardFontNames[FromEnum(detail::StandardFont::AwesomeSolid)];

			if (!FileSystem::Exists(path))
			{
				return false;
			}

			if (const FT_Error error = ::FT_New_Face(m_freeType, path.narrow().c_str(), 0, &m_awesomeIconSolid.face))
			{
				if (error == FT_Err_Unknown_File_Format)
				{
					// unsupported format
				}
				else if (error)
				{
					// failed to open or load
				}

				return false;
			}
		}

		// brands
		{
			const FilePath path = detail::GetEngineFontDirectory()
				+ detail::StandardFontNames[FromEnum(detail::StandardFont::AwesomeBrands)];

			if (!FileSystem::Exists(path))
			{
				return false;
			}

			if (const FT_Error error = ::FT_New_Face(m_freeType, path.narrow().c_str(), 0, &m_awesomeIconBrands.face))
			{
				if (error == FT_Err_Unknown_File_Format)
				{
					// unsupported format
				}
				else if (error)
				{
					// failed to open or load
				}

				return false;
			}
		}

		return true;
	}
}
