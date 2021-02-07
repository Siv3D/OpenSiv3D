//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "AssetHandle.hpp"
# include "FontStyle.hpp"
# include "GlyphInfo.hpp"
# include "OutlineGlyph.hpp"
# include "SDFGlyph.hpp"
# include "MSDFGlyph.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	class Font : public AssetHandle<Font>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Font();

		//SIV3D_NODISCARD_CXX20
		//explicit Font(int32 fontSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		virtual ~Font();

		[[nodiscard]]
		const String& familyName() const;

		[[nodiscard]]
		const String& styleName() const;

		[[nodiscard]]
		FontStyle style() const;

		[[nodiscard]]
		int32 fontSize() const;

		[[nodiscard]]
		int32 ascender() const;

		[[nodiscard]]
		int32 descender() const;

		[[nodiscard]]
		int32 height() const;

		[[nodiscard]]
		bool hasGlyph(char32 ch) const;

		[[nodiscard]]
		bool hasGlyph(StringView ch) const;

		[[nodiscard]]
		GlyphIndex getGlyphIndex(char32 ch) const;

		[[nodiscard]]
		GlyphIndex getGlyphIndex(StringView ch) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfo(char32 ch) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfo(StringView ch) const;

		[[nodiscard]]
		OutlineGlyph renderOutline(char32 ch, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		OutlineGlyph renderOutline(StringView ch, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		Array<OutlineGlyph> renderOutlines(StringView s, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		SDFGlyph renderSDF(char32 ch, int32 buffer = 3) const;

		[[nodiscard]]
		SDFGlyph renderSDF(StringView ch, int32 buffer = 3) const;

		[[nodiscard]]
		MSDFGlyph renderMSDF(char32 ch, int32 buffer = 3) const;

		[[nodiscard]]
		MSDFGlyph renderMSDF(StringView ch, int32 buffer = 3) const;
	};
}
