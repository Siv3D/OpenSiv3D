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
# include <freetype/ft2build.h>
# include <freetype/ftoutln.h>
# include FT_FREETYPE_H
# include FT_SYNTHESIS_H
# include FT_TRUETYPE_TABLES_H
# include <harfbuzz/hb.h>
# include <harfbuzz/hb-ft.h>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/DynamicTexture.hpp>
# include "FontFace.hpp"

# if SIV3D_PLATFORM(WINDOWS)

# include <Siv3D/Windows.hpp>

namespace s3d
{
	class FontResourceHolder
	{
	private:

		int64 m_size = 0;

		const void* m_pResource = nullptr;

	public:

		FontResourceHolder() = default;

		FontResourceHolder(const FilePath& path)
		{
			HMODULE hModule = ::GetModuleHandleW(nullptr);

			const std::wstring pathW = path.toWstr();

			if (HRSRC hrs = ::FindResourceW(hModule, &pathW[1], L"FILE"))
			{
				m_pResource = ::LockResource(::LoadResource(hModule, hrs));

				m_size = ::SizeofResource(hModule, hrs);
			}
		}

		~FontResourceHolder()
		{
			m_pResource = nullptr;

			m_size = 0;
		}

		const void* data() const
		{
			return m_pResource;
		}

		int64 size() const
		{
			return m_size;
		}
	};
}

# endif

namespace s3d
{
	struct GlyphInfo
	{
		Rect bitmapRect = { 0,0,0,0 };

		Point offset = { 0,0 };

		int32 bearingY = 0;

		int32 xAdvance = 0;

		int32 yAdvance = 0;

		int32 width = 0;
	};

	class FontData
	{
	private:

		using char32VH = uint32;

		static constexpr uint32 Horizontal = 0;

		static constexpr uint32 Vertical = 1u << 31u;

		using CommonGlyphIndex = uint32;

	# if SIV3D_PLATFORM(WINDOWS)

		FontResourceHolder m_resource;

	# endif

		HashTable<char32VH, CommonGlyphIndex> m_glyphVHIndexTable;

		HashTable<uint16, uint16> m_verticalTable;

		bool m_verticalTableInitialized = false;

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

		void generateVerticalTable();

		bool render(const String& codePoints);

		bool renderVertical(const String& codePoints);

		bool renderGlyph(FT_Face face, FT_UInt glyphIndex);

		void paintGlyph(FT_Face face, FT_UInt glyphIndex, Image& image, Image& tmpImage, bool overwrite, const Point& penPos, const Color& color, int32& width, int32& xAdvance) const;

	public:

		struct Null {};

		FontData() = default;

		FontData(Null, FT_Library library);

		FontData(FT_Library library, const FilePath& filePath, const FilePath& emojiFilePath, const int32 fontSize, FontStyle style);

		~FontData();

		bool isInitialized() const noexcept;

		const String& getFamilyName() const;

		const String& getStyleName() const;

		int32 getFontSize() const noexcept;

		int32 getAscent() const noexcept;

		int32 getDescent() const noexcept;

		Array<Glyph> getGlyphs(const String& codePoints);

		Array<Glyph> getVerticalGlyphs(const String& codePoints);

		OutlineGlyph getOutlineGlyph(char32 codePoint);

		const Texture& getTexture() const;

		RectF getBoundingRect(const String& codePoints, double lineSpacingScale);

		RectF getRegion(const String& codePoints, double lineSpacingScale);

		Array<int32> getXAdvances(const String& codePoints);

		RectF draw(const String& codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale);

		bool draw(const String& codePoints, const RectF& area, const ColorF& color, double lineSpacingScale);

		Rect paint(Image& dst, bool overwrite, const String& codePoints, const Point& pos, const Color& color, double lineSpacingScale) const;
	};
}
