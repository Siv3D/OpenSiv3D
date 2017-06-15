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

# include "CFont.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Compression.hpp>
# include <Siv3D/CharacterSet.hpp>
# include "../EngineDirectory/EngineDirectory.hpp"

namespace s3d
{
	namespace detail
	{
		FilePath GetEngineFontDirectory()
		{
			return EngineDirectory::CurrectVersionCommon() + S3DSTR("font/");
		}

		FilePath GetEngineFontPath(const Typeface typeface)
		{
			const FilePath fontDirectory = GetEngineFontDirectory();

			switch (typeface)
			{
			case Typeface::Thin:
				return fontDirectory + L"mplus/mplus-1p-thin.ttf";
			case Typeface::Light:
				return fontDirectory + L"mplus/mplus-1p-light.ttf";
			case Typeface::Regular:
				return fontDirectory + L"mplus/mplus-1p-regular.ttf";
			case Typeface::Medium:
				return fontDirectory + L"mplus/mplus-1p-medium.ttf";
			case Typeface::Bold:
				return fontDirectory + L"mplus/mplus-1p-bold.ttf";
			case Typeface::Heavy:
				return fontDirectory + L"mplus/mplus-1p-heavy.ttf";
			default:
				return fontDirectory + L"mplus/mplus-1p-black.ttf";
			}
		}
	}

	CFont::CFont()
	{
		
	}

	CFont::~CFont()
	{
		m_fonts.destroy();

		m_awesomeIcon.destroy();

		m_colorEmoji.destroy();

		if (m_library)
		{
			::FT_Done_FreeType(m_library);
		}
	}

	bool CFont::init()
	{
		if (const FT_Error error = ::FT_Init_FreeType(&m_library))
		{
			return false;
		}

		const auto nullFont = std::make_shared<FontData>(FontData::Null{}, m_library);

		if (!nullFont->isInitialized())
		{
			return false;
		}

		m_fonts.setNullData(nullFont);

		const FilePath fontNames[10] =
		{
			L"mplus/mplus-1p-thin.ttf",			
			L"mplus/mplus-1p-light.ttf",		
			L"mplus/mplus-1p-regular.ttf",		
			L"mplus/mplus-1p-medium.ttf",		
			L"mplus/mplus-1p-bold.ttf",		
			L"mplus/mplus-1p-heavy.ttf",
			L"mplus/mplus-1p-black.ttf",
			L"noto/NotoEmoji-Regular.ttf",
			L"noto/NotoColorEmoji.ttf",
			L"fontawesome/FontAwesome.otf",
		};

		const FilePath fontDirectory = EngineDirectory::CurrectVersionCommon() + S3DSTR("font/");
		
		for (const auto& fontName : fontNames)
		{
			const FilePath fontResourcePath = Resource(S3DSTR("engine/font/") + fontName + L".zst");

			if (!FileSystem::Exists(fontDirectory + fontName)
				&& FileSystem::Exists(fontResourcePath))
			{
				Compression::DecompressFileToFile(fontResourcePath, fontDirectory + fontName);
			}
		}
	
		if (!loadColorEmojiFace())
		{
			
		}

		if (!loadAwesomeIconFace())
		{

		}

		return true;
	}

	Font::IDType CFont::create(const Typeface typeface, const int32 fontSize, const FontStyle style)
	{
		return create(detail::GetEngineFontPath(typeface), fontSize, style);
	}

	Font::IDType CFont::create(const FilePath& path, const int32 fontSize, const FontStyle style)
	{
		const FilePath emojiPath = detail::GetEngineFontDirectory() + L"noto/NotoEmoji-Regular.ttf";

		const auto font = std::make_shared<FontData>(m_library, path, emojiPath, fontSize, style);

		if (!font->isInitialized())
		{
			return Font::NullHandleID;
		}

		return m_fonts.add(font);
	}

	void CFont::release(const Font::IDType handleID)
	{
		m_fonts.erase(handleID);
	}

	const String& CFont::getFamilyName(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getFamilyName();
	}

	const String& CFont::getStyleName(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getStyleName();
	}

	int32 CFont::getFontSize(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getFontSize();
	}

	int32 CFont::getAscent(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getAscent();
	}

	int32 CFont::getDescent(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getDescent();
	}

	Array<Glyph> CFont::getGlyphs(Font::IDType handleID, const U32String& codePoints)
	{
		return m_fonts[handleID]->getGlyphs(codePoints);
	}

	RectF CFont::getBoundingRect(Font::IDType handleID, const U32String& codePoints, double lineSpacingScale)
	{
		return m_fonts[handleID]->getBoundingRect(codePoints, lineSpacingScale);
	}

	RectF CFont::getRegion(Font::IDType handleID, const U32String& codePoints, double lineSpacingScale)
	{
		return m_fonts[handleID]->getRegion(codePoints, lineSpacingScale);
	}

	Array<int32> CFont::getXAdvances(Font::IDType handleID, const U32String& codePoints)
	{
		return m_fonts[handleID]->getXAdvances(codePoints);
	}

	RectF CFont::draw(const Font::IDType handleID, const U32String& codePoints, const Vec2& pos, const ColorF& color, const double lineSpacingScale)
	{
		return m_fonts[handleID]->draw(codePoints, pos, color, lineSpacingScale);
	}

	bool CFont::draw(Font::IDType handleID, const U32String& codePoints, const RectF& area, const ColorF& color, double lineSpacingScale)
	{
		return m_fonts[handleID]->draw(codePoints, area, color, lineSpacingScale);
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

			if (0 < a && a < 254)
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
		if (!m_awesomeIcon || size < 1)
		{
			return Image();
		}

		size = std::max(size - 2, 1);

		const FT_Face face = m_awesomeIcon.face;

		if (const FT_Error error = ::FT_Set_Pixel_Sizes(face, 0, size))
		{
			return Image();
		}

		const FT_UInt glyphIndex = ::FT_Get_Char_Index(face, code);

		if(glyphIndex == 0)
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
				image[y + 1][x + 1] = Color(255, bitmapBuffer[y * bitmapWidth + x]);
			}
		}

		return image;
	}

	bool CFont::loadColorEmojiFace()
	{
		const FilePath path = detail::GetEngineFontDirectory() + L"noto/NotoColorEmoji.ttf";

		if (!FileSystem::Exists(path))
		{
			return false;
		}

		if (const FT_Error error = ::FT_New_Face(m_library, path.narrow().c_str(), 0, &m_colorEmoji.face))
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
		const FilePath path = detail::GetEngineFontDirectory() + L"fontawesome/FontAwesome.otf";

		if (!FileSystem::Exists(path))
		{
			return false;
		}

		if (const FT_Error error = ::FT_New_Face(m_library, path.narrow().c_str(), 0, &m_awesomeIcon.face))
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

		return true;
	}
}
