//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/TextStyle.hpp>
# include <Siv3D/Icon.hpp>
# include "FontFaceProperty.hpp"

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DFont
	{
	public:

		static ISiv3DFont* Create();

		virtual ~ISiv3DFont() = default;

		virtual void init() = 0;

		virtual size_t getFontCount() const = 0;

		virtual Font::IDType create(FilePathView path, size_t faceIndex, FontMethod fontMethod, int32 fontSize, FontStyle style) = 0;

		virtual Font::IDType create(Typeface typeface, FontMethod fontMethod, int32 fontSize, FontStyle style) = 0;

		virtual void release(Font::IDType handleID) = 0;

		virtual bool addFallbackFont(Font::IDType handleID, const std::weak_ptr<AssetHandle<Font>::AssetIDWrapperType>& font) = 0;

		virtual void setIndentSize(Font::IDType handleID, int32 indentSize) = 0;

		virtual const FontFaceProperty& getProperty(Font::IDType handleID) = 0;

		virtual FontMethod getMethod(Font::IDType handleID) = 0;

		virtual void setBufferThickness(Font::IDType handleID, int32 thickness) = 0;

		virtual int32 getBufferThickness(Font::IDType handleID) = 0;

		virtual bool hasGlyph(Font::IDType handleID, StringView ch) = 0;

		virtual GlyphIndex getGlyphIndex(Font::IDType handleID, StringView ch) = 0;

		virtual Array<GlyphCluster> getGlyphClusters(Font::IDType handleID, StringView s, bool recursive, Ligature ligature) = 0;

		virtual GlyphInfo getGlyphInfo(Font::IDType handleID, StringView ch) = 0;

		virtual GlyphInfo getGlyphInfoByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) = 0;

		virtual OutlineGlyph renderOutline(Font::IDType handleID, StringView ch, CloseRing closeRing) = 0;

		virtual OutlineGlyph renderOutlineByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, CloseRing closeRing) = 0;

		virtual Array<OutlineGlyph> renderOutlines(Font::IDType handleID, StringView s, CloseRing closeRing, Ligature ligature) = 0;

		virtual PolygonGlyph renderPolygon(Font::IDType handleID, StringView ch) = 0;

		virtual PolygonGlyph renderPolygonByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) = 0;

		virtual Array<PolygonGlyph> renderPolygons(Font::IDType handleID, StringView s, Ligature ligature) = 0;

		virtual BitmapGlyph renderBitmap(Font::IDType handleID, StringView s) = 0;

		virtual BitmapGlyph renderBitmapByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) = 0;

		virtual SDFGlyph renderSDF(Font::IDType handleID, StringView s, int32 buffer) = 0;

		virtual SDFGlyph renderSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) = 0;

		virtual MSDFGlyph renderMSDF(Font::IDType handleID, StringView s, int32 buffer) = 0;

		virtual MSDFGlyph renderMSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) = 0;

		virtual bool preload(Font::IDType handleID, StringView chars) = 0;

		virtual const Texture& getTexture(Font::IDType handleID) = 0;

		virtual Glyph getGlyph(Font::IDType handleID, StringView ch) = 0;

		virtual Array<Glyph> getGlyphs(Font::IDType handleID, StringView s, Ligature ligature) = 0;

		virtual Array<double> getXAdvances(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, double fontSize) = 0;

		virtual RectF region(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, double lineHeightScale) = 0;

		virtual RectF regionBase(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, double lineHeightScale) = 0;

		virtual RectF draw(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) = 0;

		virtual bool fits(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const RectF& area, double fontSize, double lineHeightScale) = 0;

		virtual bool draw(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const RectF& area, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) = 0;

		virtual RectF drawBase(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) = 0;
	
		virtual RectF drawFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) = 0;

		virtual RectF drawBaseFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) = 0;

		virtual RectF regionFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, double lineHeightScale) = 0;

		virtual RectF regionBaseFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, double lineHeightScale) = 0;
	
		virtual double xAdvanceFallback(Font::IDType handleID, const GlyphCluster& cluster, double fontSize) = 0;


		virtual bool hasEmoji(StringView emoji) = 0;

		virtual GlyphIndex getEmojiGlyphIndex(StringView emoji) = 0;

		virtual Image renderEmojiBitmap(GlyphIndex glyphIndex) = 0;


		virtual bool hasIcon(Icon::Type iconType, char32 codePoint) = 0;

		virtual GlyphIndex getIconGlyphIndex(Icon::Type iconType, char32 codePoint) = 0;

		virtual Image renderIconBitmap(Icon::Type iconType, char32 codePoint, int32 fontPixelSize) = 0;

		virtual Image renderIconSDF(Icon::Type iconType, char32 codePoint, int32 fontPixelSize, int32 buffer) = 0;

		virtual Image renderIconMSDF(Icon::Type iconType, char32 codePoint, int32 fontPixelSize, int32 buffer) = 0;
	
		virtual const PixelShader& getFontShader(FontMethod method, TextStyle::Type type, HasColor hasColor) const = 0;
	
		virtual bool isAvailable(Typeface typeface) const = 0;
	};
}
