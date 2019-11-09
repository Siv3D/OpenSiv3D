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
# include <Siv3D/SDFFont.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include "SDFFontData.hpp"
//# include "FontFace.hpp"
# include "ISDFFont.hpp"

namespace s3d
{
	class CSDFFont : public ISiv3DSDFFont
	{
	private:

		FT_Library m_freeType = nullptr;

		AssetHandleManager<SDFFontID, SDFFontData> m_fonts{ U"SDFFont" };

	public:

		CSDFFont();

		~CSDFFont() override;

		void init() override;

		[[nodiscard]] SDFFontID create(Typeface typeface, int32 baseSize, FontStyle style) override;

		[[nodiscard]] SDFFontID create(const FilePath& path, int32 baseSize, FontStyle style) override;

		void release(SDFFontID handleID) override;

		[[nodiscard]] const String& getFamilyName(SDFFontID handleID) override;

		[[nodiscard]] const String& getStyleName(SDFFontID handleID) override;

		[[nodiscard]] int32 getBaseSize(SDFFontID handleID) override;

		[[nodiscard]] int32 getAscent(SDFFontID handleID) override;

		[[nodiscard]] int32 getDescent(SDFFontID handleID) override;

		[[nodiscard]] int32 getHeight(SDFFontID handleID) override;

		[[nodiscard]] Array<Glyph> getGlyphs(SDFFontID handleID, StringView codePoints) override;

		[[nodiscard]] const Texture& getTexture(SDFFontID handleID) override;
	};
}
