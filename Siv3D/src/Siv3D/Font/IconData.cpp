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
# include "IconData.hpp"
# include "FreeType.hpp"
# include "GlyphRenderer/BitmapGlyphRenderer.hpp"
# include "GlyphRenderer/SDFGlyphRenderer.hpp"
# include "GlyphRenderer/MSDFGlyphRenderer.hpp"

namespace s3d
{
	IconData::IconData(const FT_Library library, const FilePathView path, const size_t faceIndex)
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

		// Font property
		{
			m_property.familiyName		= Unicode::Widen(m_face->family_name);
			m_property.styleName		= Unicode::Widen(m_face->style_name);
			m_property.numGlyphs		= static_cast<uint32>(m_face->num_glyphs);
			m_property.hasColor			= false;
			m_property.fontPixelSize	= 0;
			m_property.spaceWidth		= 0;
			m_property.style			= FontStyle::Default;
			m_property.ascender			= 0;
			m_property.descender		= 0;
		}

		m_initialized = true;
	}

	IconData::~IconData()
	{
		if (m_face)
		{
			::FT_Done_Face(m_face);
			m_face = nullptr;
		}
	}

	bool IconData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	bool IconData::hasGlyph(const char32 ch)
	{
		return (getGlyphIndex(ch) != 0);
	}

	GlyphIndex IconData::getGlyphIndex(const char32 codePoint)
	{
		return ::FT_Get_Char_Index(m_face, codePoint);
	}

	BitmapGlyph IconData::renderBitmap(const GlyphIndex glyphIndex, const int32 fontPixelSize)
	{
		if (::FT_Set_Pixel_Sizes(m_face, 0, fontPixelSize))
		{
			return{};
		}

		// Font property
		{
			m_property.fontPixelSize	= fontPixelSize;
			m_property.ascender			= static_cast<int16>(m_face->size->metrics.ascender / 64);
			m_property.descender		= -static_cast<int16>(m_face->size->metrics.descender / 64);
		}

		return RenderBitmapGlyph(m_face, glyphIndex, m_property);
	}

	SDFGlyph IconData::renderSDF(const GlyphIndex glyphIndex, const int32 fontPixelSize, const int32 buffer)
	{
		if (::FT_Set_Pixel_Sizes(m_face, 0, fontPixelSize))
		{
			return{};
		}

		// Font property
		{
			m_property.fontPixelSize	= fontPixelSize;
			m_property.ascender			= static_cast<int16>(m_face->size->metrics.ascender / 64);
			m_property.descender		= -static_cast<int16>(m_face->size->metrics.descender / 64);
		}

		return RenderSDFGlyph(m_face, glyphIndex, buffer, m_property);
	}

	MSDFGlyph IconData::renderMSDF(const GlyphIndex glyphIndex, const int32 fontPixelSize, const int32 buffer)
	{
		if (::FT_Set_Pixel_Sizes(m_face, 0, fontPixelSize))
		{
			return{};
		}

		// Font property
		{
			m_property.fontPixelSize	= fontPixelSize;
			m_property.ascender			= static_cast<int16>(m_face->size->metrics.ascender / 64);
			m_property.descender		= -static_cast<int16>(m_face->size->metrics.descender / 64);
		}

		return RenderMSDFGlyph(m_face, glyphIndex, buffer, m_property);
	}
}
