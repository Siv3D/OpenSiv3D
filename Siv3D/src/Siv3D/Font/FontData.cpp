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

# include <Siv3D/FileSystem.hpp>
# include "FontData.hpp"

namespace s3d
{
	FontData::FontData(Null)
	{
		m_initialized = true;
	}

	FontData::FontData(const FT_Library library, const FilePathView path, const int32 fontSize, const FontStyle style)
	{
	# if SIV3D_PLATFORM(WINDOWS)

		if (FileSystem::IsResource(path))
		{
			m_resource = FontResourceHolder{ path };

			if (not m_fontFace.load(library, m_resource.data(), m_resource.size(), fontSize, style))
			{
				return;
			}
		}
		else
		{
			if (not m_fontFace.load(library, path, fontSize, style))
			{
				return;
			}
		}

	# else

		if (not m_fontFace.load(library, path, fontSize, style))
		{
			return;
		}

	# endif

		m_initialized = true;
	}

	FontData::~FontData()
	{

	}

	bool FontData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const FontFaceProperty& FontData::getProperty() const noexcept
	{
		return m_fontFace.getProperty();
	}

	bool FontData::hasGlyph(const StringView ch)
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(ch);

		if (glyphInfo.count != 1)
		{
			return false;
		}
		
		const uint32 glyphIndex = glyphInfo.info[0].codepoint;

		return (glyphIndex != 0);
	}

	GlyphInfo FontData::getGlyphInfo(StringView ch)
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(ch);

		if (glyphInfo.count != 1)
		{
			return{};
		}

		const uint32 glyphIndex = glyphInfo.info[0].codepoint;

		return m_fontFace.getGlyphInfo(glyphIndex);
	}

	GlyphOutline FontData::getGlyphOutline(const StringView ch)
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(ch);

		if (glyphInfo.count != 1)
		{
			return{};
		}

		const uint32 glyphIndex = glyphInfo.info[0].codepoint;

		return m_fontFace.getGlyphOutline(glyphIndex);
	}

	Array<GlyphOutline> FontData::getGlyphOutlines(const StringView s)
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(s);

		Array<GlyphOutline> results(Arg::reserve = glyphInfo.count);

		for (size_t i = 0; i < glyphInfo.count; ++i)
		{
			const uint32 glyphIndex = glyphInfo.info[i].codepoint;

			results << m_fontFace.getGlyphOutline(glyphIndex);
		}

		return results;
	}
}
