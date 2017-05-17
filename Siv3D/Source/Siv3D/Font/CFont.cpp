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

namespace s3d
{
	CFont::CFont()
	{
		m_fonts.destroy();
	}

	CFont::~CFont()
	{
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

		return true;
	}

	Font::IDType CFont::create(const FilePath& path, const int32 fontSize)
	{
		const auto font = std::make_shared<FontData>(m_library, path, fontSize);

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

	RectF CFont::draw(const Font::IDType handleID, const String& text, const Vec2& pos, const ColorF& color, const double lineSpacingScale)
	{
		return m_fonts[handleID]->draw(text, pos, color, lineSpacingScale);
	}
}
