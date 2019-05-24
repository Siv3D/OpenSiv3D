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
# include <Siv3D/Font.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include "FontData.hpp"
# include "FontFace.hpp"
# include "IFont.hpp"

namespace s3d
{
	class CFont : public ISiv3DFont
	{
	private:

		FT_Library m_freeType = nullptr;

		FontFace m_colorEmoji;

		FontFace m_awesomeIconSolid;

		FontFace m_awesomeIconBrands;

		AssetHandleManager<FontID, FontData> m_fonts{ U"Font" };

		bool loadColorEmojiFace();

		bool loadAwesomeIconFace();

	public:

		CFont();

		~CFont() override;

		void init() override;

		Image getColorEmoji(StringView emoji) override;

		Image getColorEmojiSilhouette(StringView emoji) override;

		Image getAwesomeIcon(uint16 code, int32 size) override;

		Optional<const FontFace&> getAwesomeIconFontFaceFotCode(uint16 code) const override;

		FontID create(Typeface typeface, int32 fontSize, FontStyle style) override;

		FontID create(const FilePath& path, int32 fontSize, FontStyle style) override;

		void release(FontID handleID) override;

		const String& getFamilyName(FontID handleID) override;

		const String& getStyleName(FontID handleID) override;

		int32 getFontSize(FontID handleID) override;

		int32 getAscent(FontID handleID) override;

		int32 getDescent(FontID handleID) override;

		Array<Glyph> getGlyphs(FontID handleID, const String& codePoints) override;

		Array<Glyph> getVerticalGlyphs(FontID handleID, const String& codePoints) override;

		OutlineGlyph getOutlineGlyph(FontID handleID, char32 codePoint) override;

		const Texture& getTexture(FontID handleID) override;

		RectF getBoundingRect(FontID handleID, const String& codePoints, double lineSpacingScale) override;

		RectF getRegion(FontID handleID, const String& codePoints, double lineSpacingScale) override;

		Array<int32> getXAdvances(FontID handleID, const String& codePoints) override;

		RectF draw(FontID handleID, const String& codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale) override;

		bool draw(FontID handleID, const String& codePoints, const RectF& area, const ColorF& color, double lineSpacingScale) override;

		Rect paint(FontID handleID, Image& dst, const String& codePoints, const Point& pos, const Color& color, double lineSpacingScale) override;

		Rect overwrite(FontID handleID, Image& dst, const String& codePoints, const Point& pos, const Color& color, double lineSpacingScale) override;
	};
}
