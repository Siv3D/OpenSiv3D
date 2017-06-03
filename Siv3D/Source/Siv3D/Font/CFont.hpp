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

# pragma once
# include "IFont.hpp"
# include "../AssetHandleManager/AssetHandleManager.hpp"
# include "FontData.hpp"
# include "../../ThirdParty/harfbuzz/hb.h"
# include "../../ThirdParty/harfbuzz/hb-ft.h"

namespace s3d
{
	struct FontFace
	{
		FT_Face face = nullptr;

		hb_font_t* hbFont = nullptr;

		hb_buffer_t* buffer = nullptr;

		FontFace()
			: buffer(::hb_buffer_create())
		{

		}

		std::pair<const hb_glyph_info_t*, size_t> get(const StringView view)
		{
			::hb_buffer_reset(buffer);

		# if defined(SIV3D_TARGET_WINDOWS)
	
			::hb_buffer_add_utf16(buffer, reinterpret_cast<const uint16*>(view.data()), static_cast<int32>(view.length()), 0, static_cast<int32>(view.length()));

		# else

			::hb_buffer_add_utf32(buffer, reinterpret_cast<const uint32*>(view.data()), static_cast<int32>(view.length()), 0, static_cast<int32>(view.length()));

		# endif	

			::hb_buffer_guess_segment_properties(buffer);

			::hb_shape(hbFont, buffer, nullptr, 0);

			uint32 glyphCount = 0;

			const hb_glyph_info_t* glyphInfo = ::hb_buffer_get_glyph_infos(buffer, &glyphCount);

			return{ glyphInfo, glyphCount };
		}

		void destroy()
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
	};

	class CFont : public ISiv3DFont
	{
	private:

		FT_Library m_library = nullptr;

		AssetHandleManager<Texture::IDType, std::shared_ptr<FontData>> m_fonts{ S3DSTR("Font") };

		FontFace m_colorEmoji;

		bool m_hasColorEmoji = false;

		bool loadColorEmojiFace();

	public:

		CFont();

		~CFont() override;

		bool init() override;

		Font::IDType create(Typeface typeface, int32 fontSize, FontStyle style) override;

		Font::IDType create(const FilePath& path, int32 fontSize, FontStyle style) override;

		void release(Font::IDType handleID) override;

		int32 getAscender(Font::IDType handleID);

		int32 getDescender(Font::IDType handleID);

		RectF getBoundingRect(Font::IDType handleID, const String& text, double lineSpacingScale) override;

		RectF getRegion(Font::IDType handleID, const String& text, double lineSpacingScale) override;

		RectF draw(Font::IDType handleID, const String& text, const Vec2& pos, const ColorF& color, double lineSpacingScale) override;

		bool draw(Font::IDType handleID, const String& text, const RectF& area, const ColorF& color, double lineSpacingScale) override;

		Image getColorEmoji(StringView emoji) override;
	};
}
