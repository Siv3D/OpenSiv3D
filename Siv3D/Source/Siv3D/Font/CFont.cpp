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
		m_fonts.destroy();
	}

	CFont::~CFont()
	{
		if (m_colorEmojiFace)
		{
			::FT_Done_Face(m_colorEmojiFace);
		}

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

		const FilePath fontNames[9] =
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

	int32 CFont::getAscender(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getAscender();
	}

	int32 CFont::getDescender(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getDescender();
	}

	RectF CFont::getBoundingRect(Font::IDType handleID, const String& text, double lineSpacingScale)
	{
		return m_fonts[handleID]->getBoundingRect(text, lineSpacingScale);
	}

	RectF CFont::getRegion(Font::IDType handleID, const String& text, double lineSpacingScale)
	{
		return m_fonts[handleID]->getRegion(text, lineSpacingScale);
	}

	RectF CFont::draw(const Font::IDType handleID, const String& text, const Vec2& pos, const ColorF& color, const double lineSpacingScale)
	{
		return m_fonts[handleID]->draw(text, pos, color, lineSpacingScale);
	}

	Image CFont::getColorEmoji(const uint32 codePoint)
	{
		const uint32_t glyphIndex = ::FT_Get_Char_Index(m_colorEmojiFace, codePoint);

		if (glyphIndex == 0)
		{
			return Image();
		}

		if (const FT_Error error = ::FT_Load_Glyph(m_colorEmojiFace, glyphIndex, FT_LOAD_COLOR))
		{
			return Image();
		}

		if (const FT_Error error = ::FT_Render_Glyph(m_colorEmojiFace->glyph, FT_RENDER_MODE_NORMAL))
		{
			return Image();
		}

		const int32 bitmapWidth = m_colorEmojiFace->glyph->bitmap.width;
		const int32 bitmapHeight = m_colorEmojiFace->glyph->bitmap.rows;

		Image image(bitmapWidth, bitmapHeight);

		Color* pDst = image.data();
		Color* const pDstEnd = pDst + image.num_pixels();
		const uint8_t* pSrc = m_colorEmojiFace->glyph->bitmap.buffer;

		while (pDst != pDstEnd)
		{
			pDst->set(pSrc[2], pSrc[1], pSrc[0], pSrc[3]);
			++pDst;
			pSrc += 4;
		}

		return image;
	}

	bool CFont::loadColorEmojiFace()
	{
		const FilePath colorEmojiPath = detail::GetEngineFontDirectory() + L"noto/NotoColorEmoji.ttf";

		if (!FileSystem::Exists(colorEmojiPath))
		{
			return false;
		}

		if (const FT_Error error = ::FT_New_Face(m_library, colorEmojiPath.narrow().c_str(), 0, &m_colorEmojiFace))
		{
			return false;
		}

		FT_ULong length = 0;

		if (const FT_Error error = ::FT_Load_Sfnt_Table(m_colorEmojiFace, FT_MAKE_TAG('C', 'B', 'D', 'T'), 0, nullptr, &length))
		{
			return false;
		}

		if (!length)
		{
			return false;
		}

		if (m_colorEmojiFace->num_fixed_sizes == 0)
		{
			return false;
		}

		int32 bestMatch = 0;
		int32 diff = std::abs(128 - m_colorEmojiFace->available_sizes[0].width);
		
		for (int32 i = 1; i < m_colorEmojiFace->num_fixed_sizes; ++i)
		{
			const int32 ndiff = std::abs(128 - m_colorEmojiFace->available_sizes[i].width);
			
			if (ndiff < diff)
			{
				bestMatch = i;
				diff = ndiff;
			}
		}

		if (const FT_Error error = ::FT_Select_Size(m_colorEmojiFace, bestMatch))
		{
			return false;
		}

		m_hasColorEmoji = true;

		return true;
	}
}
