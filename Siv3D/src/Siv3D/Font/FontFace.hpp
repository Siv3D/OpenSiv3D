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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FontStyle.hpp>
# include "FontFaceProperty.hpp"
# include <ThirdParty/harfbuzz/hb.h>
# include <ThirdParty/harfbuzz/hb-ft.h>

namespace s3d
{
	struct HBGlyphInfo
	{
		const hb_glyph_info_t* info = nullptr;
		
		size_t count = 0;
	};

	class FontFace
	{
	public:

		FontFace() = default;

		~FontFace();

		bool load(FT_Library library, const void* data, size_t size, int32 pixelSize, FontStyle style);

		bool load(FT_Library library, FilePathView path, int32 pixelSize, FontStyle style);

		[[nodiscard]]
		FT_Face getFT_Face() const noexcept;

		[[nodiscard]]
		const FontFaceProperty& getProperty() const noexcept;

		[[nodiscard]]
		HBGlyphInfo getHBGlyphInfo(StringView s) const;

	private:

		bool init(int32 pixelSize, FontStyle style);

		void release();

		FT_Face m_face = nullptr;

		hb_font_t* m_hbFont = nullptr;

		hb_buffer_t* m_hbBuffer = nullptr;

		FontFaceProperty m_property;
	};
}
