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

# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "MSDFGlyphCache.hpp"

namespace s3d
{
	RectF MSDFGlyphCache::draw(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		return draw(font, s, clusters, pos, size, textStyle, color, false, lineHeightScale);
	}

	RectF MSDFGlyphCache::drawBase(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		return draw(font, s, clusters, pos, size, textStyle, color, true, lineHeightScale);
	}

	RectF MSDFGlyphCache::drawFallback(const FontData& font, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, const double lineHeightScale)
	{
		return drawFallback(font, cluster, pos, size, color, false, lineHeightScale);
	}

	RectF MSDFGlyphCache::drawBaseFallback(const FontData& font, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, const double lineHeightScale)
	{
		return drawFallback(font, cluster, pos, size, color, true, lineHeightScale);
	}

	RectF MSDFGlyphCache::region(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return region(font, s, clusters, pos, size, false, lineHeightScale);
	}

	RectF MSDFGlyphCache::regionBase(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return region(font, s, clusters, pos, size, true, lineHeightScale);
	}

	RectF MSDFGlyphCache::regionFallback(const FontData& font, const GlyphCluster& cluster, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return regionFallback(font, cluster, pos, size, false, lineHeightScale);
	}

	RectF MSDFGlyphCache::regionBaseFallback(const FontData& font, const GlyphCluster& cluster, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return regionFallback(font, cluster, pos, size, true, lineHeightScale);
	}

	Array<double> MSDFGlyphCache::getXAdvances(const FontData& font, StringView s, const Array<GlyphCluster>& clusters)
	{
		if (not prerender(font, clusters))
		{
			return{};
		}

		const auto& prop = font.getProperty();
		Array<double> xAdvances(Arg::reserve = clusters.size());

		for (const auto& cluster : clusters)
		{
			const char32 ch = s[cluster.pos];

			if (IsControl(ch))
			{
				if (ch == U'\t')
				{
					xAdvances << (prop.spaceWidth * 4);
				}
				else
				{
					xAdvances << 0.0;
				}

				continue;
			}

			if (cluster.fontIndex != 0)
			{
				const size_t fallbackIndex = (cluster.fontIndex - 1);

				xAdvances << SIV3D_ENGINE(Font)->xAdvanceFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
					cluster);

				continue;
			}

			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			xAdvances << cache.info.xAdvance;
		}

		return xAdvances;
	}

	double MSDFGlyphCache::xAdvanceFallback(const FontData& font, const GlyphCluster& cluster)
	{
		if (not prerender(font, { cluster }))
		{
			return 0.0;
		}

		const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
		return cache.info.xAdvance;
	}

	void MSDFGlyphCache::setBufferWidth(const int32 width)
	{
		m_buffer.bufferWidth = Max(width, 0);
	}

	int32 MSDFGlyphCache::getBufferWidth() const noexcept
	{
		return m_buffer.bufferWidth;
	}

	bool MSDFGlyphCache::preload(const FontData& font, const StringView s)
	{
		return prerender(font, font.getGlyphClusters(s, false));
	}

	const Texture& MSDFGlyphCache::getTexture() const noexcept
	{
		return m_texture;
	}

	bool MSDFGlyphCache::prerender(const FontData& font, const Array<GlyphCluster>& clusters)
	{
		bool hasDirty = false;

		if (m_glyphTable.empty())
		{
			const MSDFGlyph glyph = font.renderMSDFByGlyphIndex(0, m_buffer.bufferWidth);

			if (not CacheGlyph(font, glyph.image, glyph, m_buffer, m_glyphTable))
			{
				return false;
			}

			hasDirty = true;
		}

		for (const auto& cluster : clusters)
		{
			if (m_glyphTable.contains(cluster.glyphIndex))
			{
				continue;
			}

			const MSDFGlyph glyph = font.renderMSDFByGlyphIndex(cluster.glyphIndex, m_buffer.bufferWidth);

			if (m_glyphTable.contains(glyph.glyphIndex))
			{
				continue;
			}

			if (not CacheGlyph(font, glyph.image, glyph, m_buffer, m_glyphTable))
			{
				return false;
			}

			hasDirty = true;
		}

		if (hasDirty)
		{
			m_texture = Texture{ m_buffer.image };
		}

		return true;
	}

	RectF MSDFGlyphCache::draw(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const TextStyle& textStyle, const ColorF& color, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, clusters))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const bool noScaling = (size == prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		for (const auto& cluster : clusters)
		{
			if (ProcessControlCharacter(s[cluster.pos], penPos, lineCount, basePos, scale, lineHeightScale, prop))
			{
				xMax = Max(xMax, penPos.x);
				continue;
			}

			if (cluster.fontIndex != 0)
			{
				const size_t fallbackIndex = (cluster.fontIndex - 1);
				RectF rect;

				if (usebasePos)
				{
					rect = SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos, size, textStyle, color, lineHeightScale);
				}
				else
				{
					rect = SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos.movedBy(0, prop.ascender * scale), size, textStyle, color, lineHeightScale);
				}

				penPos.x += rect.w;
				xMax = Max(xMax, penPos.x);
				continue;
			}

			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			{
				const TextureRegion textureRegion = m_texture(cache.textureRegionLeft, cache.textureRegionTop, cache.textureRegionWidth, cache.textureRegionHeight);
				const Vec2 posOffset = usebasePos ? cache.info.getBase(scale) : cache.info.getOffset(scale);
				const Vec2 drawPos = (penPos + posOffset);
				RectF rect;

				if (noScaling)
				{
					rect = textureRegion
						.draw(drawPos, color);
				}
				else
				{
					rect = textureRegion
						.scaled(scale)
						.draw(drawPos, color);
				}
			}

			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}

	RectF MSDFGlyphCache::drawFallback(const FontData& font, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, { cluster }))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const bool noScaling = (size == prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		{
			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			{
				const TextureRegion textureRegion = m_texture(cache.textureRegionLeft, cache.textureRegionTop, cache.textureRegionWidth, cache.textureRegionHeight);
				const Vec2 posOffset = usebasePos ? cache.info.getBase(scale) : cache.info.getOffset(scale);
				const Vec2 drawPos = (penPos + posOffset);
				RectF rect;

				if (noScaling)
				{
					rect = textureRegion
						.draw(drawPos, color);
				}
				else
				{
					rect = textureRegion
						.scaled(scale)
						.draw(drawPos, color);
				}
			}

			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}

	RectF MSDFGlyphCache::region(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, clusters))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		for (const auto& cluster : clusters)
		{
			if (ProcessControlCharacter(s[cluster.pos], penPos, lineCount, basePos, scale, lineHeightScale, prop))
			{
				xMax = Max(xMax, penPos.x);
				continue;
			}

			if (cluster.fontIndex != 0)
			{
				const size_t fallbackIndex = (cluster.fontIndex - 1);
				RectF rect;

				if (usebasePos)
				{
					rect = SIV3D_ENGINE(Font)->regionBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos, size, lineHeightScale);
				}
				else
				{
					rect = SIV3D_ENGINE(Font)->regionBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos.movedBy(0, prop.ascender * scale), size, lineHeightScale);
				}

				penPos.x += rect.w;
				xMax = Max(xMax, penPos.x);
				continue;
			}

			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}

	RectF MSDFGlyphCache::regionFallback(const FontData& font, const GlyphCluster& cluster, const Vec2& pos, const double size, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, { cluster }))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		{
			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}
}
