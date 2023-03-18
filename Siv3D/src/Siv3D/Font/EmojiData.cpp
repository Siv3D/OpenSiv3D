//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include "EmojiData.hpp"
# include "FreeType.hpp"
# include "GlyphRenderer/BitmapGlyphRenderer.hpp"

namespace s3d
{
	EmojiData::EmojiData(const FT_Library library, const FilePathView path, const size_t faceIndex)
	{
		if (const FT_Error error = ::FT_New_Face(library, path.narrow().c_str(), static_cast<FT_Long>(faceIndex), &m_face))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else
			{
				// failed to open or load
			}

			return;
		}

		constexpr int32 DefaultPixelSize = 128;
		int32 pixelSize = 0;

		if (::FT_Set_Pixel_Sizes(m_face, 0, DefaultPixelSize))
		{
			// FontFace has fixed pixel size

			FT_ULong length = 0;
			if (::FT_Load_Sfnt_Table(m_face, FT_MAKE_TAG('C', 'B', 'D', 'T'), 0, nullptr, &length))
			{
				return;
			}

			if (length == 0)
			{
				return;
			}

			if (m_face->num_fixed_sizes == 0)
			{
				return;
			}

			int32 bestMatch = 0;
			int32 diff = std::abs(DefaultPixelSize - m_face->available_sizes[0].width);

			for (int32 i = 1; i < m_face->num_fixed_sizes; ++i)
			{
				const int32 ndiff = std::abs(DefaultPixelSize - m_face->available_sizes[i].width);

				if (ndiff < diff)
				{
					bestMatch = i;
					diff = ndiff;
				}
			}

			if (::FT_Select_Size(m_face, bestMatch))
			{
				return;
			}

			pixelSize = m_face->available_sizes[bestMatch].width;

			LOG_TRACE(U"Available size: {}"_fmt(pixelSize));
		}

		// HarfBuzz objects
		{
			m_hbFont	= ::hb_ft_font_create_referenced(m_face);
			m_hbBuffer	= ::hb_buffer_create();

			if (not ::hb_buffer_allocation_successful(m_hbBuffer))
			{
				return;
			}
		}

		// Font property
		{
			m_property.familiyName		= Unicode::Widen(m_face->family_name);
			m_property.styleName		= Unicode::Widen(m_face->style_name);
			m_property.numGlyphs		= static_cast<uint32>(m_face->num_glyphs);
			m_property.hasColor			= FT_HAS_COLOR(m_face);
			m_property.fontPixelSize	= pixelSize;
			m_property.spaceWidth		= 0;
			m_property.style			= FontStyle::Default;
			m_property.ascender			= static_cast<int16>(m_face->size->metrics.ascender / 64);
			m_property.descender		= -static_cast<int16>(m_face->size->metrics.descender / 64);
		}

		m_initialized = true;
	}

	EmojiData::~EmojiData()
	{
		if (m_hbBuffer)
		{
			::hb_buffer_destroy(m_hbBuffer);
			m_hbBuffer = nullptr;
		}

		if (m_hbFont)
		{
			::hb_font_destroy(m_hbFont);
			m_hbFont = nullptr;
		}

		if (m_face)
		{
			::FT_Done_Face(m_face);
			m_face = nullptr;
		}
	}

	bool EmojiData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	bool EmojiData::hasGlyph(const StringView ch)
	{
		return (getGlyphIndex(ch) != 0);
	}

	GlyphIndex EmojiData::getGlyphIndex(const StringView ch)
	{
		if (not m_hbBuffer)
		{
			return 0;
		}

		::hb_buffer_clear_contents(m_hbBuffer);

		::hb_buffer_add_utf32(m_hbBuffer,
			reinterpret_cast<const uint32*>(ch.data()),
			static_cast<int32>(ch.length()), 0, static_cast<int32>(ch.length()));

		::hb_buffer_guess_segment_properties(m_hbBuffer);

		::hb_shape(m_hbFont, m_hbBuffer, nullptr, 0);

		uint32 glyphCount = 0;
		const hb_glyph_info_t* glyphInfo = ::hb_buffer_get_glyph_infos(m_hbBuffer, &glyphCount);

		if (glyphCount != 1)
		{
			return 0;
		}

		const GlyphIndex glyphIndex = glyphInfo[0].codepoint;

		return glyphIndex;
	}

	BitmapGlyph EmojiData::renderBitmap(const GlyphIndex glyphIndex)
	{
		return RenderBitmapGlyph(m_face, glyphIndex, m_property);
	}
}
