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

# pragma once
# include <utility>
# include <freetype/ft2build.h>
# include <freetype/ftoutln.h>
# include FT_FREETYPE_H
# include FT_SYNTHESIS_H
# include FT_TRUETYPE_TABLES_H
# include <harfbuzz/hb.h>
# include <harfbuzz/hb-ft.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/StringView.hpp>

namespace s3d
{
	struct FontFace
	{
		FT_Face face = nullptr;

		hb_font_t* hbFont = nullptr;

		hb_buffer_t* buffer = nullptr;

		FontFace();

		~FontFace();

		explicit operator bool() const noexcept;

		std::pair<const hb_glyph_info_t*, size_t> get(const StringView view);

		void destroy();
	};
}
