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
# include "EmojiDatabase.hpp"

namespace s3d
{
	class CFont : public ISiv3DFont
	{
	private:

		FT_Library m_library = nullptr;

		AssetHandleManager<Font::IDType, std::shared_ptr<FontData>> m_fonts{ S3DSTR("Font") };

		FontFace m_colorEmoji;

		FontFace m_awesomeIcon;

		//EmojiDatabase m_emojiDataBase;

		//EmojiDatabase2 m_emojiDataBase2;

		bool loadColorEmojiFace();

		bool loadAwesomeIconFace();

	public:

		CFont();

		~CFont() override;

		bool init() override;

		Font::IDType create(Typeface typeface, int32 fontSize, FontStyle style) override;

		Font::IDType create(const FilePath& path, int32 fontSize, FontStyle style) override;

		void release(Font::IDType handleID) override;

		const String& getFamilyName(Font::IDType handleID) override;

		const String& getStyleName(Font::IDType handleID) override;

		int32 getFontSize(Font::IDType handleID) override;

		int32 getAscent(Font::IDType handleID) override;

		int32 getDescent(Font::IDType handleID) override;

		Array<Glyph> getGlyphs(Font::IDType handleID, const U32String& codePoints) override;

		RectF getBoundingRect(Font::IDType handleID, const U32String& codePoints, double lineSpacingScale) override;

		RectF getRegion(Font::IDType handleID, const U32String& codePoints, double lineSpacingScale) override;

		Array<int32> getXAdvances(Font::IDType handleID, const U32String& codePoints) override;

		RectF draw(Font::IDType handleID, const U32String& codePoints, const Vec2& pos, const ColorF& color, double lineSpacingScale) override;

		bool draw(Font::IDType handleID, const U32String& codePoints, const RectF& area, const ColorF& color, double lineSpacingScale) override;

		Image getColorEmoji(StringView emoji) override;

		Image getColorEmojiSilhouette(StringView emoji) override;

		Image getAwesomeIcon(uint16 code, int32 size) override;

		//size_t checkEmoji(std::vector<char32_t>::const_iterator it, std::vector<char32_t>::const_iterator itEnd) const override;
	};
}
