//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IFont.hpp"
# include "../AssetHandleManager/AssetHandleManager.hpp"
# include "FontData.hpp"

namespace s3d
{
	class CFont : public ISiv3DFont
	{
	private:

		FT_Library m_library = nullptr;

		AssetHandleManager<FontID, FontData> m_fonts{ U"Font" };

		FontFace m_colorEmoji;

		FontFace m_awesomeIconSolid;

		FontFace m_awesomeIconBrands;

		//EmojiDatabase m_emojiDataBase;

		//EmojiDatabase2 m_emojiDataBase2;

		bool loadColorEmojiFace();

		bool loadAwesomeIconFace();

	public:

		CFont();

		~CFont() override;

		bool init() override;

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

		RectF getBoundingRect(FontID handleID, const String& codePoints, double lineSpacingScale) override;

		RectF getRegion(FontID handleID, const String& codePoints, double lineSpacingScale) override;

		Array<int32> getXAdvances(FontID handleID, const String& codePoints) override;

		RectF draw(FontID handleID, const String& codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale) override;

		bool draw(FontID handleID, const String& codePoints, const RectF& area, const ColorF& color, double lineSpacingScale) override;

		Image getColorEmoji(StringView emoji) override;

		Image getColorEmojiSilhouette(StringView emoji) override;

		Image getAwesomeIcon(uint16 code, int32 size) override;

		//size_t checkEmoji(std::vector<char32_t>::const_iterator it, std::vector<char32_t>::const_iterator itEnd) const override;
	};
}
