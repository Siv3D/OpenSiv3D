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
# include <Siv3D/Font.hpp>
# include <Siv3D/DynamicTexture.hpp>
# include <Siv3D/HashTable.hpp>
# include "IGlyphCache.hpp"
# include "GlyphCacheCommon.hpp"

namespace s3d
{
	class MSDFGlyphCache : public IGlyphCache
	{
	public:

		MSDFGlyphCache() = default;

		RectF draw(const FontData & font, StringView s, const Array<GlyphCluster>&clusters, bool usebasePos, const Vec2 & pos, double size, const TextStyle & textStyle, const ColorF & color, double lineHeightScale) override;

		bool fits(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const RectF& area, double size, double lineHeightScale);

		bool draw(const FontData & font, StringView s, const Array<GlyphCluster>&clusters, const RectF & area, double size, const TextStyle & textStyle, const ColorF & color, double lineHeightScale) override;

		[[nodiscard]]
		RectF drawFallback(const FontData & font, const GlyphCluster & cluster, bool usebasePos, const Vec2 & pos, double size, const ColorF & color, double lineHeightScale) override;

		[[nodiscard]]
		Array<double> getXAdvances(const FontData & font, StringView s, const Array<GlyphCluster>&clusters, double fontSize) override;

		[[nodiscard]]
		double xAdvanceFallback(const FontData & font, const GlyphCluster & cluster, double fontSize) override;

		[[nodiscard]]
		RectF region(const FontData & font, StringView s, const Array<GlyphCluster>&clusters, bool usebasePos, const Vec2 & pos, double size, double lineHeightScale) override;

		[[nodiscard]]
		RectF regionFallback(const FontData & font, const GlyphCluster & cluster, bool usebasePos, const Vec2 & pos, double size, double lineHeightScale) override;

		void setBufferWidth(int32 width) override;

		[[nodiscard]]
		int32 getBufferWidth() const noexcept override;

		bool preload(const FontData & font, StringView s) override;

		[[nodiscard]]
		const Texture& getTexture() noexcept override;

		[[nodiscard]]
		TextureRegion getTextureRegion(const FontData& font, GlyphIndex glyphIndex) override;

		[[nodiscard]]
		int32 getBufferThickness(GlyphIndex glyphIndex) override;

	private:

		static constexpr int32 DefaultBuffer = 2;

		HashTable<GlyphIndex, GlyphCache> m_glyphTable;

		DynamicTexture m_texture;

		bool m_hasDirty = false;

		BufferImage m_buffer = { .image = {}, .backgroundColor = Color{ 0, 0 } };

		[[nodiscard]]
		bool prerender(const FontData& font, const Array<GlyphCluster>& clusters, bool isMainFont);

		void updateTexture();
	};
}
