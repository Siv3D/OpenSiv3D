//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Font.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CFont.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		constexpr StringView ToString(const FontStyle style) noexcept
		{
			switch (style)
			{
			case FontStyle::Default:
				return U"Default";
			case FontStyle::Bold:
				return U"Bold";
			case FontStyle::Italic:
				return U"Italic";
			case FontStyle::BoldItalic:
				return U"BoldItalic";
			case FontStyle::Bitmap:
				return U"Bitmap";
			case FontStyle::BoldBitmap:
				return U"BoldBitmap";
			case FontStyle::ItalicBitmap:
				return U"ItalicBitmap";
			default:
				return U"BoldItalicBitmap";
			}
		}
	}

	CFont::CFont()
	{
		// do nothing
	}

	CFont::~CFont()
	{
		LOG_SCOPED_TRACE(U"CFont::~CFont()");

		m_fonts.destroy();

		if (m_freeType)
		{
			FT_Done_FreeType(m_freeType);
		}
	}

	void CFont::init()
	{
		LOG_SCOPED_TRACE(U"CFont::init()");

		if (const FT_Error error = FT_Init_FreeType(&m_freeType))
		{
			throw EngineError{ U"FT_Init_FreeType() failed" };
		}

		// null Font を管理に登録
		{
			// null Font を作成
			auto nullFont = std::make_unique<FontData>(FontData::Null{});

			if (not nullFont->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null Font initialization failed");
			}

			// 管理に登録
			m_fonts.setNullData(std::move(nullFont));
		}
	}

	Font::IDType CFont::create(const FilePathView path, const int32 fontSize, const FontStyle style)
	{
		// Font を作成
		auto font = std::make_unique<FontData>(m_freeType, path, fontSize, style);

		if (not font->isInitialized()) // もし作成に失敗していたら
		{
			return Font::IDType::NullAsset();
		}

		const auto& prop = font->getProperty();
		const String fontName = (prop.styleName) ? (prop.familiyName + U' ' + prop.styleName) : (prop.familiyName);
		const String info = U"(`{0}`, size: {1}, style: {2}, ascent: {3}, descent: {4})"_fmt(fontName, prop.fontPixelSize, detail::ToString(prop.style), prop.ascent, prop.descent);

		// Font を管理に登録
		return m_fonts.add(std::move(font), info);
	}

	void CFont::release(const Font::IDType handleID)
	{
		m_fonts.erase(handleID);
	}

	const String& CFont::getFamilyName(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty().familiyName;
	}

	const String& CFont::getStyleName(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty().styleName;
	}

	FontStyle CFont::getStyle(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty().style;
	}

	int32 CFont::getFontSize(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty().fontPixelSize;
	}

	int32 CFont::getAscent(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty().ascent;
	}

	int32 CFont::getDescent(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty().descent;
	}

	int32 CFont::getHeight(const Font::IDType handleID)
	{
		const auto& prop = m_fonts[handleID]->getProperty();

		return (prop.ascent + prop.descent);
	}

	bool CFont::hasGlyph(const Font::IDType handleID, StringView ch)
	{
		return m_fonts[handleID]->hasGlyph(ch);
	}

	GlyphInfo CFont::getGlyphInfo(const Font::IDType handleID, const StringView ch)
	{
		return m_fonts[handleID]->getGlyphInfo(ch);
	}
}
