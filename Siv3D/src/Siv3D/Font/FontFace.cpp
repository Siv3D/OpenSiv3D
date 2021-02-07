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

# include "FontFace.hpp"

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(5054)
# include "mapbox/glyph_foundry_impl.hpp"
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	FontFace::~FontFace()
	{
		release();
	}

	bool FontFace::load(const FT_Library library, const void* data, const size_t size, const int32 pixelSize, const FontStyle style)
	{
		release();

		if (const FT_Error error = ::FT_New_Memory_Face(library, static_cast<const FT_Byte*>(data), static_cast<FT_Long>(size), 0, &m_face))
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

		if (not init(pixelSize, style))
		{
			return false;
		}

		return true;
	}

	bool FontFace::load(const FT_Library library, const FilePathView path, const int32 pixelSize, const FontStyle style)
	{
		release();

		if (const FT_Error error = ::FT_New_Face(library, path.narrow().c_str(), 0, &m_face))
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

		if (not init(pixelSize, style))
		{
			return false;
		}

		return true;
	}

	const FontFaceProperty& FontFace::getProperty() const noexcept
	{
		return m_property;
	}

	HBGlyphInfo FontFace::getHBGlyphInfo(const StringView s)
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

		::hb_shape(m_hbFont, m_hbBuffer, nullptr, 0);

		uint32 glyphCount = 0;
		const hb_glyph_info_t* glyphInfo = ::hb_buffer_get_glyph_infos(m_hbBuffer, &glyphCount);

		return{ glyphInfo, glyphCount };
	}

	GlyphInfo FontFace::getGlyphInfo(const GlyphIndex glyphIndex)
	{
		if (not LoadGlyph(m_face, glyphIndex, m_property.style))
		{
			return{};
		}

		const GlyphBBox bbox = GetGlyphBound(m_face);

		return GlyphInfo{
			.glyphIndex	= glyphIndex,
			.buffer		= 0,
			.left		= static_cast<int32>(bbox.xMin),
			.top		= static_cast<int32>(bbox.yMax),
			.width		= static_cast<int32>(bbox.xMax - bbox.xMin),
			.height		= static_cast<int32>(bbox.yMax - bbox.yMin),
			.ascender	= m_property.ascender,
			.descender	= m_property.descender,
			.xAdvance	= (m_face->glyph->metrics.horiAdvance / 64.0),
			.yAdvance	= (m_face->glyph->metrics.vertAdvance / 64.0),
		};
	}

	OutlineGlyph FontFace::renderOutline(const GlyphIndex glyphIndex, const CloseRing closeRing)
	{
		if (not LoadGlyph(m_face, glyphIndex, m_property.style))
		{
			return{};
		}

		GlyphBBox bbox;
		Array<LineString> rings = GetGlyphOutline(m_face, bbox, closeRing);

		OutlineGlyph result;
		result.glyphIndex	= glyphIndex;
		result.left			= static_cast<int32>(bbox.xMin);
		result.top			= static_cast<int32>(bbox.yMax);
		result.width		= static_cast<int32>(bbox.xMax - bbox.xMin);
		result.height		= static_cast<int32>(bbox.yMax - bbox.yMin);
		result.ascender		= m_property.ascender;
		result.descender	= m_property.descender;
		result.xAdvance		= (m_face->glyph->metrics.horiAdvance / 64.0);
		result.yAdvance		= (m_face->glyph->metrics.vertAdvance / 64.0);
		result.rings		= std::move(rings);
		return result;
	}

	SDFGlyph FontFace::renderSDF(const GlyphIndex glyphIndex, int32 buffer)
	{
		buffer = Max(buffer, 0);
		sdf_glyph_foundry::glyph_info gi{ .glyph_index = glyphIndex };
		sdf_glyph_foundry::RenderSDF(gi, buffer, 0.5f, m_face);

		SDFGlyph result;
		result.glyphIndex	= glyphIndex;
		result.buffer		= buffer;
		result.left			= gi.left;
		result.top			= gi.top;
		result.width		= gi.width;
		result.height		= gi.height;
		result.ascender		= m_property.ascender;
		result.descender	= m_property.descender;
		result.xAdvance		= gi.xAdvance;
		result.yAdvance		= gi.yAdvance;
		result.image		= RenderSDF(gi.bitmap, (gi.width + 2 * buffer), (gi.height + 2 * buffer));
		return result;
	}

	MSDFGlyph FontFace::renderMSDF(const GlyphIndex glyphIndex, int32 buffer)
	{
		buffer = Max(buffer, 0);

		if (not LoadGlyph(m_face, glyphIndex, m_property.style))
		{
			return{};
		}

		msdfgen::Shape shape;	
		if (not GetShape(m_face, shape))
		{
			return{};
		}

		const GlyphBBox bbox = GetGlyphBound(shape);
		const int32 width	= static_cast<int32>(bbox.xMax - bbox.xMin);
		const int32 height	= static_cast<int32>(bbox.yMax - bbox.yMin);
		const Vec2 offset{ (-bbox.xMin+ buffer), (-bbox.yMin + buffer) };

		msdfgen::Bitmap<float, 3> bitmap{ (width + (2 * buffer)), (height + (2 * buffer)) };
		msdfgen::generateMSDF(bitmap, shape, 4.0, 1.0, msdfgen::Vector2(offset.x, offset.y));

		MSDFGlyph result;
		result.glyphIndex	= glyphIndex;
		result.buffer		= buffer;
		result.left			= static_cast<int32>(bbox.xMin);
		result.top			= static_cast<int32>(bbox.yMax);
		result.width		= width;
		result.height		= height;
		result.xAdvance		= (m_face->glyph->metrics.horiAdvance / 64.0);
		result.yAdvance		= (m_face->glyph->metrics.vertAdvance / 64.0);
		result.ascender		= m_property.ascender;
		result.descender	= m_property.descender;
		result.image		= RenderMSDF(bitmap);
		return result;
	}

	bool FontFace::init(const int32 pixelSize, const FontStyle style)
	{
		assert(m_face != nullptr);
		assert(m_hbBuffer == nullptr);

		if (const FT_Error error = ::FT_Set_Pixel_Sizes(m_face, 0, pixelSize))
		{
			return false;
		}

		// HarfBuzz objects
		{
			m_hbFont	= ::hb_ft_font_create_referenced(m_face);
			m_hbBuffer	= ::hb_buffer_create();

			if (not ::hb_buffer_allocation_successful(m_hbBuffer))
			{
				return false;
			}

			//::hb_buffer_set_replacement_codepoint(m_hbBuffer, (hb_codepoint_t)-1);
		}

		// Font property
		{
			m_property.familiyName		= Unicode::Widen(m_face->family_name);
			m_property.styleName		= Unicode::Widen(m_face->style_name);
			m_property.fontPixelSize	= pixelSize;
			m_property.style			= style;
			m_property.ascender			= static_cast<int32>(m_face->size->metrics.ascender / 64);
			m_property.descender		= -static_cast<int32>(m_face->size->metrics.descender / 64);
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
