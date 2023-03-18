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

# include "FontFace.hpp"
# include "FreeType.hpp"
# include "GlyphRenderer/GlyphRenderer.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	FontFace::~FontFace()
	{
		release();
	}

	bool FontFace::load(const FT_Library library, const void* data, const size_t size, const size_t faceIndex, const int32 pixelSize, const FontStyle style, const FontMethod method)
	{
		release();

		if (const FT_Error error = ::FT_New_Memory_Face(library, static_cast<const FT_Byte*>(data), static_cast<FT_Long>(size), static_cast<FT_Long>(faceIndex), &m_face))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else
			{
				// failed to open or load
			}

			return false;
		}

		if (not init(pixelSize, style, method))
		{
			return false;
		}

		return true;
	}

	bool FontFace::load(const FT_Library library, const FilePathView path, const size_t faceIndex, const int32 pixelSize, const FontStyle style, const FontMethod method)
	{
		release();

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

			return false;
		}

		if (not init(pixelSize, style, method))
		{
			return false;
		}

		return true;
	}

	FT_Face FontFace::getFT_Face() const noexcept
	{
		return m_face;
	}

	void FontFace::setIndentSize(const int32 indentSize) noexcept
	{
		m_property.indentSize = indentSize;
	}

	const FontFaceProperty& FontFace::getProperty() const noexcept
	{
		return m_property;
	}

	HBGlyphInfo FontFace::getHBGlyphInfo(const StringView s, const Ligature ligature) const
	{
		if (not m_hbBuffer)
		{
			return{};
		}

		::hb_buffer_clear_contents(m_hbBuffer);

		::hb_buffer_add_utf32(m_hbBuffer,
			reinterpret_cast<const uint32*>(s.data()),
			static_cast<int32>(s.length()), 0, static_cast<int32>(s.length()));

		::hb_buffer_guess_segment_properties(m_hbBuffer);

		if (ligature)
		{
			::hb_shape(m_hbFont, m_hbBuffer, nullptr, 0);
		}
		else
		{
			::hb_shape(m_hbFont, m_hbBuffer, m_noLigatureFeatures.data(), static_cast<uint32>(m_noLigatureFeatures.size()));
		}

		uint32 glyphCount = 0;
		const hb_glyph_info_t* glyphInfo = ::hb_buffer_get_glyph_infos(m_hbBuffer, &glyphCount);

		return{ glyphInfo, glyphCount };
	}

	bool FontFace::init(int32 pixelSize, const FontStyle style, FontMethod method)
	{
		assert(m_face != nullptr);
		assert(m_hbBuffer == nullptr);

		if (::FT_Set_Pixel_Sizes(m_face, 0, pixelSize))
		{
			// FontFace has fixed pixel size

			FT_ULong length = 0;
			if (::FT_Load_Sfnt_Table(m_face, FT_MAKE_TAG('C', 'B', 'D', 'T'), 0, nullptr, &length))
			{
				return false;
			}

			if (length == 0)
			{
				return false;
			}

			if (m_face->num_fixed_sizes == 0)
			{
				return false;
			}

			int32 bestMatch = 0;
			int32 diff = std::abs(pixelSize - m_face->available_sizes[0].width);

			for (int32 i = 1; i < m_face->num_fixed_sizes; ++i)
			{
				const int32 ndiff = std::abs(pixelSize - m_face->available_sizes[i].width);

				if (ndiff < diff)
				{
					bestMatch = i;
					diff = ndiff;
				}
			}

			if (::FT_Select_Size(m_face, bestMatch))
			{
				return false;
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
				return false;
			}
		}

		// features to disable ligatures
		{
			m_noLigatureFeatures[0].tag = ::hb_tag_from_string("liga", 4);
			m_noLigatureFeatures[0].start = 0;
			m_noLigatureFeatures[0].end = (unsigned int)-1;
			m_noLigatureFeatures[0].value = 0;

			m_noLigatureFeatures[1].tag = ::hb_tag_from_string("rlig", 4);
			m_noLigatureFeatures[1].start = 0;
			m_noLigatureFeatures[1].end = (unsigned int)-1;
			m_noLigatureFeatures[1].value = 0;

			m_noLigatureFeatures[2].tag = ::hb_tag_from_string("dlig", 4);
			m_noLigatureFeatures[2].start = 0;
			m_noLigatureFeatures[2].end = (unsigned int)-1;
			m_noLigatureFeatures[2].value = 0;

			m_noLigatureFeatures[3].tag = ::hb_tag_from_string("calt", 4);
			m_noLigatureFeatures[3].start = 0;
			m_noLigatureFeatures[3].end = (unsigned int)-1;
			m_noLigatureFeatures[3].value = 0;
		}

		// Font property
		{
			m_property.familiyName		= Unicode::Widen(m_face->family_name);
			m_property.styleName		= Unicode::Widen(m_face->style_name);
			m_property.numGlyphs		= static_cast<uint32>(m_face->num_glyphs);
			m_property.hasColor			= FT_HAS_COLOR(m_face);
			m_property.fontPixelSize	= pixelSize;
			m_property.style			= style;
			m_property.ascender			= static_cast<int16>(m_face->size->metrics.ascender / 64);
			m_property.descender		= -static_cast<int16>(m_face->size->metrics.descender / 64);
		}

		{
			const HBGlyphInfo glyphInfo = getHBGlyphInfo(U" ", Ligature::Yes);

			if (glyphInfo.count < 1)
			{
				return false;
			}

			{
				const GlyphIndex spaceGlyphIndex = glyphInfo.info[0].codepoint;

				if (((method == FontMethod::SDF) || (method == FontMethod::MSDF))
					&& (not FT_IS_SCALABLE(m_face)))
				{
					method = FontMethod::Bitmap;
				}

				m_property.spaceWidth = GetGlyphInfo(m_face, spaceGlyphIndex, m_property, method).xAdvance;
			}
		}

		return true;
	}

	void FontFace::release()
	{
		m_property = {};

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
}
