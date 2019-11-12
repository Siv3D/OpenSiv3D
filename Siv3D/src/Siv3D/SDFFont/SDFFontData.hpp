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
# include <Siv3D/SDFFont.hpp>
# include <Font/FontData.hpp>
# include <Font/FontFace.hpp>

namespace s3d
{
	struct SDFFontProperty
	{
		String familyName;

		String styleName;

		int32 baseSize = 0;

		double scale = 1.0;

		double ascender = 0;

		double descender = 0;

		double height = 0;

		double tabWidth = 0;

		bool isBold = false;

		bool isItalic = false;
	};

	struct GlyphInfoF
	{
		RectF bitmapRect = { 0,0,0,0 };

		Vec2 offset = { 0,0 };

		double bearingY = 0;

		double xAdvance = 0;

		double yAdvance = 0;
	};

	class SDFFontData
	{
	private:

		using CodePointVH = uint32;
		static constexpr uint32 Horizontal = 0;
		static constexpr uint32 Vertical = 1u << 31u;
		using GlyphIndex = uint32;

	# if SIV3D_PLATFORM(WINDOWS)

		FontResourceHolder m_resource;

	# endif

		FontFace m_faceText;

		FontFace m_faceEmoji;

		SDFFontProperty m_property;

		Image m_image;
		static constexpr Color BackgroundColor = Color(0, 0);
		static constexpr int32 ImagePadding = 1;
		Point m_penPos = { 0, ImagePadding };

		DynamicTexture m_texture;

		HashTable<CodePointVH, GlyphIndex> m_glyphTable;

		Array<GlyphInfoF> m_glyphInfos;

		Optional<GlyphIndex> m_tofuIndex;

		bool m_initialized = false;

		[[nodiscard]] bool renderGlyphs(StringView codePoints);

		[[nodiscard]] bool renderGlyph(FT_Face face, FT_UInt glyphIndex);

	public:

		struct Null {};

		SDFFontData() = default;

		SDFFontData(Null, FT_Library library);

		SDFFontData(FT_Library library, const FilePath& filePath, const FilePath& emojiFilePath, int32 baseSize, FontStyle style);

		~SDFFontData();

		[[nodiscard]] bool isInitialized() const noexcept;

		[[nodiscard]] bool load(const FilePath& imagePath, const FilePath& glyphPath);

		[[nodiscard]] const SDFFontProperty& getProperty() const noexcept;

		[[nodiscard]] const Texture& getTexture() const;

		RectF getBoundingRect(double fontSize, StringView codePoints, double lineSpacingScale);

		RectF getRegion(double fontSize, StringView codePoints, double lineSpacingScale);

		Array<double> getXAdvances(double fontSize, StringView codePoints);

		void preload(StringView codePoints);

		bool saveGlyphs(FilePathView imagePath, FilePathView jsonPath);

		[[nodiscard]] Array<GlyphF> getGlyphs(StringView codePoints);

		RectF draw(double fontSize, StringView codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale);
	};
}
