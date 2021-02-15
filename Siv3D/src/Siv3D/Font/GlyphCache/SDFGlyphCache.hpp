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
# include <Siv3D/Font.hpp>
# include <Siv3D/HashTable.hpp>
# include "IGlyphCache.hpp"
# include "GlyphCacheCommon.hpp"

namespace s3d
{
	class SDFGlyphCache : public IGlyphCache
	{
	public:

		SDFGlyphCache() = default;

		RectF draw(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double size, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) override;

		RectF drawBase(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double size, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) override;

		RectF drawFallback(const FontData& font, StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, double lineHeightScale) override;

		RectF drawBaseFallback(const FontData& font, StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, double lineHeightScale) override;

		[[nodiscard]]
		Array<double> getXAdvances(const FontData& font, StringView s, const Array<GlyphCluster>& clusters) override;

		[[nodiscard]]
		double xAdvanceFallback(const FontData& font, StringView s, const GlyphCluster& cluster) override;

		[[nodiscard]]
		RectF region(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double size, double lineHeightScale) override;

		[[nodiscard]]
		RectF regionBase(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double size, double lineHeightScale) override;

		[[nodiscard]]
		RectF regionFallback(const FontData& font, StringView s, const GlyphCluster& cluster, const Vec2& pos, double size, double lineHeightScale) override;

		[[nodiscard]]
		RectF regionBaseFallback(const FontData& font, StringView s, const GlyphCluster& cluster, const Vec2& pos, double size, double lineHeightScale) override;

		void setBufferWidth(int32 width) override;

		[[nodiscard]]
		int32 getBufferWidth() const noexcept override;

		bool preload(const FontData& font, StringView s) override;

		[[nodiscard]]
		const Texture& getTexture() const noexcept override;

	private:

		[[nodiscard]]
		bool prerender(const FontData& font, StringView s, const Array<GlyphCluster>& clusters);

		[[nodiscard]]
		RectF draw(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double size, const TextStyle& textStyle, const ColorF& color, bool usebasePos, double lineHeightScale);

		[[nodiscard]]
		RectF drawFallback(const FontData& font, StringView s, const GlyphCluster& cluster, const Vec2& pos, double size, const ColorF& color, bool usebasePos, double lineHeightScale);

		[[nodiscard]]
		RectF region(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, double size, bool usebasePos, double lineHeightScale);

		[[nodiscard]]
		RectF regionFallback(const FontData& font, StringView s, const GlyphCluster& cluster, const Vec2& pos, double size, bool usebasePos, double lineHeightScale);

		HashTable<GlyphIndex, GlyphCache> m_glyphTable;

		Texture m_texture;

		BufferImage m_buffer = {};
	};
}
