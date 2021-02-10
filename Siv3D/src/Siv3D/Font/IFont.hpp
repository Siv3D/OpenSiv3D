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
# include "FontFaceProperty.hpp"

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DFont
	{
	public:

		static ISiv3DFont* Create();

		virtual ~ISiv3DFont() = default;

		virtual void init() = 0;

		virtual Font::IDType create(FilePathView path, FontMethod fontMethod, int32 fontSize, FontStyle style) = 0;

		virtual void release(Font::IDType handleID) = 0;

		virtual const FontFaceProperty& getProperty(Font::IDType handleID) = 0;

		virtual bool hasGlyph(Font::IDType handleID, StringView ch) = 0;

		virtual GlyphIndex getGlyphIndex(Font::IDType handleID, StringView ch) = 0;

		virtual Array<GlyphCluster> getGlyphClusters(Font::IDType handleID, StringView s) = 0;

		virtual GlyphInfo getGlyphInfo(Font::IDType handleID, StringView ch) = 0;

		virtual OutlineGlyph renderOutline(Font::IDType handleID, StringView ch, CloseRing closeRing) = 0;

		virtual OutlineGlyph renderOutlineByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, CloseRing closeRing) = 0;

		virtual Array<OutlineGlyph> renderOutlines(Font::IDType handleID, StringView s, CloseRing closeRing) = 0;

		virtual BitmapGlyph renderBitmap(Font::IDType handleID, StringView s) = 0;

		virtual BitmapGlyph renderBitmapByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) = 0;

		virtual SDFGlyph renderSDF(Font::IDType handleID, StringView s, int32 buffer) = 0;

		virtual SDFGlyph renderSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) = 0;

		virtual MSDFGlyph renderMSDF(Font::IDType handleID, StringView s, int32 buffer) = 0;

		virtual MSDFGlyph renderMSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) = 0;
	};
}
