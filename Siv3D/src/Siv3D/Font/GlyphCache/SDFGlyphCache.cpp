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
# include "SDFGlyphCache.hpp"

namespace s3d
{
	RectF SDFGlyphCache::draw(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		return draw(font, s, clusters, pos, size, textStyle, color, false, lineHeightScale);
	}

	RectF SDFGlyphCache::drawBase(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		return draw(font, s, clusters, pos, size, textStyle, color, true, lineHeightScale);
	}

	RectF SDFGlyphCache::drawFallback(const FontData& font, const StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, const double lineHeightScale)
	{
		return drawFallback(font, s, cluster, pos, size, color, false, lineHeightScale);
	}

	RectF SDFGlyphCache::drawBaseFallback(const FontData& font, const StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, const double lineHeightScale)
	{
		return drawFallback(font, s, cluster, pos, size, color, true, lineHeightScale);
	}

	RectF SDFGlyphCache::region(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return region(font, s, clusters, pos, size, false, lineHeightScale);
	}

	RectF SDFGlyphCache::regionBase(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return region(font, s, clusters, pos, size, true, lineHeightScale);
	}

	RectF SDFGlyphCache::regionFallback(const FontData& font, const StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return regionFallback(font, s, cluster, pos, size, false, lineHeightScale);
	}

	RectF SDFGlyphCache::regionBaseFallback(const FontData& font, const StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const double lineHeightScale)
	{
		return regionFallback(font, s, cluster, pos, size, true, lineHeightScale);
	}

	void SDFGlyphCache::setBufferWidth(const int32 width)
	{
		m_buffer.bufferWidth = Max(width, 0);
	}

	int32 SDFGlyphCache::getBufferWidth() const noexcept
	{
		return m_buffer.bufferWidth;
	}

	bool SDFGlyphCache::preload(const FontData& font, const StringView s)
	{
		return prerender(font, s, font.getGlyphClusters(s, false));
	}

	const Texture& SDFGlyphCache::getTexture() const noexcept
	{
		return m_texture;
	}

	bool SDFGlyphCache::prerender(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters)
	{
		bool hasDirty = false;

		if (m_glyphTable.empty())
		{
			const SDFGlyph glyph = font.renderSDFByGlyphIndex(0, m_buffer.bufferWidth);

			if (not CacheGlyph(font, glyph.image, glyph, m_buffer, m_glyphTable))
			{
				return false;
			}

			hasDirty = true;
		}

		for (const auto& cluster : clusters)
		{
			if ((cluster.glyphIndex == 0)
				&& IsControl(s[cluster.pos]))
			{
				continue;
			}

			if (m_glyphTable.contains(cluster.glyphIndex))
			{
				continue;
			}

			const SDFGlyph glyph = font.renderSDFByGlyphIndex(cluster.glyphIndex, m_buffer.bufferWidth);

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

	RectF SDFGlyphCache::draw(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const TextStyle& textStyle, const ColorF& color, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, s, clusters))
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
						s.substr(cluster.pos), cluster, penPos, size, textStyle, color, lineHeightScale);
				}
				else
				{
					rect = SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						s.substr(cluster.pos), cluster, penPos.movedBy(0, prop.ascender * scale), size, textStyle, color, lineHeightScale);
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

	RectF SDFGlyphCache::drawFallback(const FontData& font, const StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const ColorF& color, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, s, { cluster }))
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

	RectF SDFGlyphCache::region(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double size, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, s, clusters))
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
						s.substr(cluster.pos), cluster, penPos, size, lineHeightScale);
				}
				else
				{
					rect = SIV3D_ENGINE(Font)->regionBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						s.substr(cluster.pos), cluster, penPos.movedBy(0, prop.ascender * scale), size, lineHeightScale);
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

	RectF SDFGlyphCache::regionFallback(const FontData& font, const StringView s, const GlyphCluster& cluster, const Vec2& pos, const double size, const bool usebasePos, const double lineHeightScale)
	{
		if (not prerender(font, s, { cluster }))
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
