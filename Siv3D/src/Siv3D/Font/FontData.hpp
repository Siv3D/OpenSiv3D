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
# include <freetype/ft2build.h>
# include FT_FREETYPE_H
# include FT_SYNTHESIS_H
# include FT_TRUETYPE_TABLES_H
# include "../../ThirdParty/harfbuzz/hb.h"
# include "../../ThirdParty/harfbuzz/hb-ft.h"
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DynamicTexture.hpp>

namespace s3d
{
	struct GlyphInfo
	{
		Rect bitmapRect = { 0,0,0,0 };

		Point offset = { 0,0 };

		int32 bearingY = 0;

		int32 xAdvance = 0;

		int32 width = 0;
	};

	struct FontFace
	{
		FT_Face face = nullptr;

		hb_font_t* hbFont = nullptr;

		hb_buffer_t* buffer = nullptr;

		FontFace()
			: buffer(::hb_buffer_create())
		{

		}

		~FontFace()
		{
			destroy();
		}

		explicit operator bool() const noexcept
		{
			return face != nullptr;
			//return face && hbFont;
		}

		std::pair<const hb_glyph_info_t*, size_t> get(const StringView view)
		{
			::hb_buffer_reset(buffer);

			::hb_buffer_add_utf32(buffer, reinterpret_cast<const uint32*>(view.data()), static_cast<int32>(view.length()), 0, static_cast<int32>(view.length()));

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

	class FontData
	{
	private:

		using CommonGlyphIndex = uint32;

		HashTable<char32, CommonGlyphIndex> m_glyphIndexTable;

		FontFace m_faceText;

		FontFace m_faceEmoji;

		Array<GlyphInfo> m_glyphs;

		Optional<CommonGlyphIndex> m_tofuIndex;

		static constexpr int32 padding = 2;

		String m_familyName;

		String m_styleName;

		int32 m_fontSize = 0;

		int32 m_lineSpacing = 0;

		int32 m_ascender = 0;

		int32 m_descender = 0;

		int32 m_tabWidth = 0;

		bool m_bold = false;

		bool m_italic = false;

		bool m_noBitmap = true;

		Point m_penPos = { 0, padding };

		Image m_image;

		DynamicTexture m_texture;

		bool m_initialized = false;

		//bool loadFromFile(const FilePath& path)
		//{
		//	return true;
		//}

		//bool loadFromResource(const FilePath& path)
		//{
		//	return true;
		//}

		bool render(const String& codePoints);

		bool renderGlyph(FT_Face face, FT_UInt glyphIndex);

	public:

		struct Null {};

		FontData() = default;

		FontData(Null, FT_Library library);

		FontData(FT_Library library, const FilePath& filePath, const FilePath& emojiFilePath, const int32 fontSize, FontStyle style);

		~FontData();

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		const String& getFamilyName() const
		{
			return m_familyName;
		}

		const String& getStyleName() const
		{
			return m_styleName;
		}

		int32 getFontSize() const noexcept
		{
			return m_fontSize;
		}

		int32 getAscent() const noexcept
		{
			return m_ascender;
		}

		int32 getDescent() const noexcept
		{
			return m_descender;
		}

		Array<Glyph> getGlyphs(const String& codePoints);

		RectF getBoundingRect(const String& codePoints, double lineSpacingScale);

		RectF getRegion(const String& codePoints, double lineSpacingScale);

		Array<int32> getXAdvances(const String& codePoints);

		RectF draw(const String& codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale);

		bool draw(const String& codePoints, const RectF& area, const ColorF& color, double lineSpacingScale);
	};
}
