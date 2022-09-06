//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "IFont.hpp"
# include "FontData.hpp"
# include "EmojiData.hpp"
# include "IconData.hpp"

namespace s3d
{
	class CFont_Headless final : public ISiv3DFont
	{
	public:

		CFont_Headless();

		~CFont_Headless();

		void init() override;

		size_t getFontCount() const override;

		Font::IDType create(FilePathView path, size_t faceIndex, FontMethod fontMethod, int32 fontSize, FontStyle style) override;

		Font::IDType create(Typeface typeface, FontMethod fontMethod, int32 fontSize, FontStyle style) override;

		void release(Font::IDType handleID) override;

		bool addFallbackFont(Font::IDType handleID, const std::weak_ptr<AssetHandle<Font>::AssetIDWrapperType>& font) override;

		void setIndentSize(Font::IDType handleID, int32 indentSize) override;

		const FontFaceProperty& getProperty(Font::IDType handleID) override;

		FontMethod getMethod(Font::IDType handleID) override;

		void setBufferThickness(Font::IDType handleID, int32 thickness) override;

		int32 getBufferThickness(Font::IDType handleID) override;

		bool hasGlyph(Font::IDType handleID, StringView ch) override;

		GlyphIndex getGlyphIndex(Font::IDType handleID, StringView ch) override;

		Array<GlyphCluster> getGlyphClusters(Font::IDType handleID, StringView s, bool recursive, Ligature ligature) override;

		GlyphInfo getGlyphInfo(Font::IDType handleID, StringView ch) override;

		GlyphInfo getGlyphInfoByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) override;

		OutlineGlyph renderOutline(Font::IDType handleID, StringView ch, CloseRing closeRing) override;

		OutlineGlyph renderOutlineByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, CloseRing closeRing) override;

		Array<OutlineGlyph> renderOutlines(Font::IDType handleID, StringView s, CloseRing closeRing, Ligature ligature) override;

		PolygonGlyph renderPolygon(Font::IDType handleID, StringView ch) override;

		PolygonGlyph renderPolygonByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) override;

		Array<PolygonGlyph> renderPolygons(Font::IDType handleID, StringView s, Ligature ligature) override;

		BitmapGlyph renderBitmap(Font::IDType handleID, StringView s) override;

		BitmapGlyph renderBitmapByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex) override;

		SDFGlyph renderSDF(Font::IDType handleID, StringView s, int32 buffer) override;

		SDFGlyph renderSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) override;

		MSDFGlyph renderMSDF(Font::IDType handleID, StringView s, int32 buffer) override;

		MSDFGlyph renderMSDFByGlyphIndex(Font::IDType handleID, GlyphIndex glyphIndex, int32 buffer) override;
	
		bool preload(Font::IDType handleID, StringView chars) override;

		const Texture& getTexture(Font::IDType handleID) override;

		Glyph getGlyph(Font::IDType handleID, StringView ch) override;

		Array<Glyph> getGlyphs(Font::IDType handleID, StringView s, Ligature ligature) override;

		Array<double> getXAdvances(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, double fontSize) override;

		RectF region(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, double lineHeightScale) override;

		RectF regionBase(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, double lineHeightScale) override;

		RectF draw(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) override;

		bool draw(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const RectF& area, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) override;

		RectF drawBase(Font::IDType handleID, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) override;
	
		RectF drawFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) override;

		RectF drawBaseFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) override;

		RectF regionFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, double lineHeightScale) override;

		RectF regionBaseFallback(Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, double fontSize, double lineHeightScale) override;
	
		double xAdvanceFallback(Font::IDType handleID, const GlyphCluster& cluster, double fontSize) override;


		bool hasEmoji(StringView emoji) override;

		GlyphIndex getEmojiGlyphIndex(StringView emoji) override;

		Image renderEmojiBitmap(GlyphIndex glyphIndex) override;


		bool hasIcon(Icon::Type iconType, char32 codePoint) override;

		GlyphIndex getIconGlyphIndex(Icon::Type iconType, char32 codePoint) override;

		Image renderIconBitmap(Icon::Type iconType, char32 codePoint, int32 fontPixelSize) override;

		Image renderIconSDF(Icon::Type iconType, char32 codePoint, int32 fontPixelSize, int32 buffer) override;

		Image renderIconMSDF(Icon::Type iconType, char32 codePoint, int32 fontPixelSize, int32 buffer) override;
	
		const PixelShader& getFontShader(FontMethod method, TextStyle::Type type, HasColor hasColor) const override;

		bool isAvailable(Typeface typeface) const override;

	private:

		FT_Library m_freeType = nullptr;

		AssetHandleManager<Font::IDType, FontData> m_fonts{ U"Font" };

		std::unique_ptr<EmojiData> m_defaultEmoji;

		Array<std::unique_ptr<IconData>> m_defaultIcons;

		std::unique_ptr<PixelShader> m_emptyPixelShader;
	};
}
