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

		double scale = 1.0;

		int32 baseSize = 0;

		int32 ascender = 0;

		int32 descender = 0;

		int32 height = 0;

		int32 tabWidth = 0;

		bool isBold = false;

		bool isItalic = false;
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
		static constexpr int32 ImagePadding = 1;
		Point m_penPos = { 0, ImagePadding };

		DynamicTexture m_texture;

		HashTable<CodePointVH, GlyphIndex> m_glyphTable;

		Array<GlyphInfo> m_glyphInfos;

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

		[[nodiscard]] const SDFFontProperty& getProperty() const noexcept;

		[[nodiscard]] const Texture& getTexture() const;

		[[nodiscard]] Array<Glyph> getGlyphs(StringView codePoints);
	};
}
