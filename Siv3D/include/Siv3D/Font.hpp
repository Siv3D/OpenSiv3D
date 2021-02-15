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
# include "GlyphCluster.hpp"
# include "OutlineGlyph.hpp"
# include "BitmapGlyph.hpp"
# include "SDFGlyph.hpp"
# include "MSDFGlyph.hpp"
# include "FontMethod.hpp"
# include "Typeface.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	struct DrawableText;

	class Font : public AssetHandle<Font>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Font();

		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		SIV3D_NODISCARD_CXX20
		Font(int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);

		SIV3D_NODISCARD_CXX20
		Font(FontMethod fontMethod, int32 fontSize, FilePathView path, FontStyle style = FontStyle::Default);

		SIV3D_NODISCARD_CXX20
		Font(FontMethod fontMethod, int32 fontSize, FilePathView path, size_t faceIndex, FontStyle style = FontStyle::Default);

		SIV3D_NODISCARD_CXX20
		Font(FontMethod fontMethod, int32 fontSize, Typeface typeface = Typeface::Regular, FontStyle style = FontStyle::Default);

		virtual ~Font();

		bool addFallback(const Font& font) const;

		bool addFallback(Font&& font) const = delete;

		[[nodiscard]]
		const String& familyName() const;

		[[nodiscard]]
		const String& styleName() const;

		[[nodiscard]]
		bool hasColor() const;

		[[nodiscard]]
		FontStyle style() const;

		[[nodiscard]]
		FontMethod method() const;

		[[nodiscard]]
		int32 fontSize() const;

		[[nodiscard]]
		int32 ascender() const;

		[[nodiscard]]
		int32 descender() const;

		[[nodiscard]]
		int32 height() const;

		[[nodiscard]]
		double spaceWidth() const;

		void setBufferThickness(int32 thickness) const;

		[[nodiscard]]
		int32 getBufferThickness() const;

		[[nodiscard]]
		bool hasGlyph(char32 ch) const;

		[[nodiscard]]
		bool hasGlyph(StringView ch) const;

		[[nodiscard]]
		uint32 num_glyphs() const;

		[[nodiscard]]
		GlyphIndex getGlyphIndex(char32 ch) const;

		[[nodiscard]]
		GlyphIndex getGlyphIndex(StringView ch) const;

		[[nodiscard]]
		Array<GlyphCluster> getGlyphClusters(StringView s, bool useFallback = true) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfo(char32 ch) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfo(StringView ch) const;

		[[nodiscard]]
		OutlineGlyph renderOutline(char32 ch, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		OutlineGlyph renderOutline(StringView ch, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		OutlineGlyph renderOutlineByGlyphIndex(GlyphIndex glyphIndex, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		Array<OutlineGlyph> renderOutlines(StringView s, CloseRing closeRing = CloseRing::No) const;

		[[nodiscard]]
		BitmapGlyph renderBitmap(char32 ch) const;

		[[nodiscard]]
		BitmapGlyph renderBitmap(StringView ch) const;

		[[nodiscard]]
		BitmapGlyph renderBitmapByGlyphIndex(GlyphIndex glyphIndex) const;

		[[nodiscard]]
		SDFGlyph renderSDF(char32 ch, int32 buffer = 3) const;

		[[nodiscard]]
		SDFGlyph renderSDF(StringView ch, int32 buffer = 3) const;

		[[nodiscard]]
		SDFGlyph renderSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer = 3) const;

		[[nodiscard]]
		MSDFGlyph renderMSDF(char32 ch, int32 buffer = 3) const;

		[[nodiscard]]
		MSDFGlyph renderMSDF(StringView ch, int32 buffer = 3) const;

		[[nodiscard]]
		MSDFGlyph renderMSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer = 3) const;

		bool preload(StringView chars) const;

		[[nodiscard]]
		const Texture& getTexture() const;

		[[nodiscard]]
		DrawableText operator()(const String& text) const;

		[[nodiscard]]
		DrawableText operator()(String&& text) const;

		template <class ... Args>
		[[nodiscard]]
		DrawableText operator()(const Args& ... args) const;
	};
}
