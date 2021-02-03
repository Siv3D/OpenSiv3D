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
# include "agg/agg_curves.h"
# include "agg/agg_curves_impl.hpp"
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
		struct OutlineData
		{
			Array<LineString> rings;
			
			LineString ring;
		};

		void CloseRing(LineString& ring)
		{
			const Vec2& first	= ring.front();
			const Vec2& last	= ring.back();

			if (first != last)
			{
				ring.push_back(first);
			}
		}

		int MoveTo(const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);
			
			if (user->ring)
			{
				CloseRing(user->ring);
				user->rings.push_back(user->ring);
				user->ring.clear();
			}
			
			user->ring.emplace_back((to->x / 64.0), (to->y / 64.0));
			return 0;
		}

		int LineTo(const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);
			user->ring.emplace_back((to->x / 64.0), (to->y / 64.0));
			return 0;
		}

		int ConicTo(const FT_Vector* control, const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);

			if (user->ring)
			{
				const Vec2 prev = user->ring.back();
				user->ring.pop_back();

				agg_fontnik::curve3_div curve{ prev.x, prev.y,
					(control->x / 64.0), (control->y / 64.0),
					(to->x / 64.0), (to->y / 64.0) };
				curve.rewind(0);

				double x, y;
				unsigned cmd;

				while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y)))
				{
					user->ring.emplace_back(x, y);
				}
			}

			return 0;
		}

		int CubicTo(const FT_Vector* c1, const FT_Vector* c2, const FT_Vector* to, void* ptr)
		{
			OutlineData* user = static_cast<OutlineData*>(ptr);

			if (user->ring)
			{
				const Vec2 prev = user->ring.back();
				user->ring.pop_back();

				agg_fontnik::curve4_div curve{ prev.x, prev.y,
					(c1->x / 64.0), (c1->y / 64.0),
					(c2->x / 64.0), (c2->y / 64.0),
					(to->x / 64.0), (to->y / 64.0) };
				curve.rewind(0);

				double x, y;
				unsigned cmd;

				while (agg_fontnik::path_cmd_stop != (cmd = curve.vertex(&x, &y)))
				{
					user->ring.emplace_back(x, y);
				}
			}

			return 0;
		}
	}

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
		if (const FT_Error error = FT_Load_Glyph(m_face, glyphIndex,
			(FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP)))
		{
			return{};
		}

		if (m_property.style & FontStyle::Bold)
		{
			::FT_GlyphSlot_Embolden(m_face->glyph);
		}

		if (m_property.style & FontStyle::Italic)
		{
			::FT_GlyphSlot_Oblique(m_face->glyph);
		}

		const FT_GlyphSlot slot = m_face->glyph;
		const int32 xAdvance = static_cast<int32>(slot->metrics.horiAdvance / 64);
		const int32 yAdvance = static_cast<int32>(slot->metrics.vertAdvance / 64);
		return{ glyphIndex, xAdvance, yAdvance };
	}

	GlyphOutline FontFace::getGlyphOutline(const GlyphIndex glyphIndex, const CloseRing closeRing)
	{
		if (const FT_Error error = FT_Load_Glyph(m_face, glyphIndex,
			(FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP)))
		{
			return{};
		}

		if (m_property.style & FontStyle::Bold)
		{
			::FT_GlyphSlot_Embolden(m_face->glyph);
		}

		if (m_property.style & FontStyle::Italic)
		{
			::FT_GlyphSlot_Oblique(m_face->glyph);
		}

		const FT_GlyphSlot slot = m_face->glyph;
		const int32 xAdvance = static_cast<int32>(slot->metrics.horiAdvance / 64);
		const int32 yAdvance = static_cast<int32>(slot->metrics.vertAdvance / 64);

		FT_Outline outline = m_face->glyph->outline;
		const FT_Matrix matrix = { 1 << 16 , 0 , 0 , -(1 << 16) };
		::FT_Outline_Transform(&outline, &matrix);

		const FT_Outline_Funcs outlineFuncs = {
			.move_to	= &detail::MoveTo,
			.line_to	= &detail::LineTo,
			.conic_to	= &detail::ConicTo,
			.cubic_to	= &detail::CubicTo,
			.shift = 0,
			.delta = 0
		};

		detail::OutlineData userData;

		if (const FT_Error error = FT_Outline_Decompose(&outline, &outlineFuncs, &userData))
		{
			return{};
		}

		if (userData.ring)
		{
			detail::CloseRing(userData.ring);
			userData.rings.push_back(userData.ring);
		}

		if (not userData.rings)
		{
			return{};
		}

		for (auto& ring : userData.rings)
		{
			ring.unique_consecutive();
		}

		if (not closeRing)
		{
			for (auto& ring : userData.rings)
			{
				if (ring.front() == ring.back())
				{
					ring.pop_back();
				}
			}
		}

		for (auto& ring : userData.rings)
		{
			ring.moveBy(0, m_property.ascent);
		}

		return{
			{ glyphIndex, xAdvance, yAdvance },
			std::move(userData.rings)
		};
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
			m_property.ascent			= static_cast<int32>(m_face->size->metrics.ascender / 64);
			m_property.descent			= -static_cast<int32>(m_face->size->metrics.descender / 64);
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
