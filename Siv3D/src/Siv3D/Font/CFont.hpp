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
# include <Siv3D/Common.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "IFont.hpp"
# include "FontData.hpp"

namespace s3d
{
	class CFont final : public ISiv3DFont
	{
	private:

		FT_Library m_freeType = nullptr;

		AssetHandleManager<Font::IDType, FontData> m_fonts{ U"Font" };

	public:

		CFont();

		~CFont();

		void init() override;

		Font::IDType create(FilePathView path, FontMethod fontMethod, int32 fontSize, FontStyle style) override;

		void release(Font::IDType handleID) override;

		const FontFaceProperty& getProperty(Font::IDType handleID) override;

		bool hasGlyph(Font::IDType handleID, StringView ch) override;

		GlyphIndex getGlyphIndex(Font::IDType handleID, StringView ch) override;

		Array<GlyphCluster> getGlyphClusters(Font::IDType handleID, StringView s) override;

		GlyphInfo getGlyphInfo(Font::IDType handleID, StringView ch) override;

		OutlineGlyph renderOutline(Font::IDType handleID, StringView ch, CloseRing closeRing) override;

		OutlineGlyph renderOutlineByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, CloseRing closeRing) override;

		Array<OutlineGlyph> renderOutlines(Font::IDType handleID, StringView s, CloseRing closeRing) override;

		BitmapGlyph renderBitmap(Font::IDType handleID, StringView s) override;

		BitmapGlyph renderBitmapByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) override;

		SDFGlyph renderSDF(Font::IDType handleID, StringView s, int32 buffer) override;

		SDFGlyph renderSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) override;

		MSDFGlyph renderMSDF(Font::IDType handleID, StringView s, int32 buffer) override;

		MSDFGlyph renderMSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) override;
	};
}
