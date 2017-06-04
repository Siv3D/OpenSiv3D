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

namespace s3d
{
	class CFont : public ISiv3DFont
	{
	private:

		FT_Library m_library = nullptr;

		AssetHandleManager<Texture::IDType, std::shared_ptr<FontData>> m_fonts{ S3DSTR("Font") };

		FontFace m_colorEmoji;

		FontFace m_awesomeIcon;

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

		Array<int32> getXAdvances(Font::IDType handleID, const String& text) override;

		RectF draw(Font::IDType handleID, const String& text, const Vec2& pos, const ColorF& color, double lineSpacingScale) override;

		bool draw(Font::IDType handleID, const String& text, const RectF& area, const ColorF& color, double lineSpacingScale) override;

		Image getColorEmoji(StringView emoji) override;
	};
}
