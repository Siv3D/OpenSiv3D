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
# include "MSDFGlyphCache.hpp"

namespace s3d
{
	RectF MSDFGlyphCache::draw(const FontData& font, const StringView s, const Vec2& pos, const double size, const ColorF& color)
	{
		return draw(font, s, pos, size, color, false);
	}

	RectF MSDFGlyphCache::drawBase(const FontData& font, const StringView s, const Vec2& pos, const double size, const ColorF& color)
	{
		return draw(font, s, pos, size, color, true);
	}

	RectF MSDFGlyphCache::region(const FontData& font, const StringView s, const Vec2& pos, const double size)
	{
		return region(font, s, pos, size, false);
	}

	RectF MSDFGlyphCache::regionBase(const FontData& font, const StringView s, const Vec2& pos, const double size)
	{
		return region(font, s, pos, size, true);
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
		return prerender(font, s, font.getGlyphClusters(s));
	}

	const Texture& MSDFGlyphCache::getTexture() const noexcept
	{
		return m_texture;
	}

	bool MSDFGlyphCache::prerender(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters)
	{
		bool hasDirty = false;

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

	RectF MSDFGlyphCache::draw(const FontData& font, const StringView s, const Vec2& pos, const double size, const ColorF& color, const bool usebasePos)
	{
		const Array<GlyphCluster> clusters = font.getGlyphClusters(s);

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
			if (ProcessControlCharacter(s[cluster.pos], penPos, lineCount, basePos, scale, font))
			{
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

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender) : pos);
		return{ topLeft, (xMax - basePos.x), static_cast<double>(lineCount * prop.height()) };
	}

	RectF MSDFGlyphCache::region(const FontData& font, const StringView s, const Vec2& pos, const double size, const bool usebasePos)
	{
		const Array<GlyphCluster> clusters = font.getGlyphClusters(s);

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
			if (ProcessControlCharacter(s[cluster.pos], penPos, lineCount, basePos, scale, font))
			{
				xMax = Max(xMax, penPos.x);
				continue;
			}

			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender) : pos);
		return{ topLeft, (xMax - basePos.x), static_cast<double>(lineCount * prop.height()) };
	}
}
