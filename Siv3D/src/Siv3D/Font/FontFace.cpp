//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "FontFace.hpp"

namespace s3d
{
	FontFace::FontFace()
		: buffer(::hb_buffer_create())
	{

	}

	FontFace::~FontFace()
	{
		destroy();
	}

	FontFace::operator bool() const noexcept
	{
		return (face != nullptr);
	}

	std::pair<const hb_glyph_info_t*, size_t> FontFace::get(const StringView view)
	{
		::hb_buffer_reset(buffer);
		::hb_buffer_add_utf32(buffer, reinterpret_cast<const uint32*>(view.data()), static_cast<int32>(view.length()), 0, static_cast<int32>(view.length()));
		::hb_buffer_guess_segment_properties(buffer);
		::hb_shape(hbFont, buffer, nullptr, 0);

		uint32 glyphCount = 0;
		const hb_glyph_info_t* glyphInfo = ::hb_buffer_get_glyph_infos(buffer, &glyphCount);

		return{ glyphInfo, glyphCount };
	}

	void FontFace::destroy()
	{
		if (hbFont)
		{
			::hb_font_destroy(hbFont);
			hbFont = nullptr;
		}

		if (buffer)
		{
			::hb_buffer_destroy(buffer);
			buffer = nullptr;
		}

		if (face)
		{
			::FT_Done_Face(face);
			face = nullptr;
		}
	}
}
