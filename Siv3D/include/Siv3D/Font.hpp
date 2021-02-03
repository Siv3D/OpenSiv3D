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
# include "GlyphOutline.hpp"

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
		int32 ascent() const;

		[[nodiscard]]
		int32 descent() const;

		[[nodiscard]]
		int32 height() const;

		[[nodiscard]]
		bool hasGlyph(char32 ch) const;

		[[nodiscard]]
		bool hasGlyph(StringView ch) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfo(char32 ch) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfo(StringView ch) const;

		[[nodiscard]]
		GlyphOutline getGlyphOutline(char32 ch) const;

		[[nodiscard]]
		GlyphOutline getGlyphOutline(StringView ch) const;

		[[nodiscard]]
		Array<GlyphOutline> getGlyphOutlines(StringView s) const;
	};
}
