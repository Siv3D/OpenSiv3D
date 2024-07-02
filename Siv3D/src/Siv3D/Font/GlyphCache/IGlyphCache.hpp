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
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/Font.hpp>
# include "../FontData.hpp"

namespace s3d
{
	class IGlyphCache
	{
	public:

		virtual ~IGlyphCache() = default;

		virtual RectF draw(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, bool useBasePos, const Vec2& pos, double size, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) = 0;

		virtual bool fits(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const RectF& area, double size, double lineHeightScale) = 0;

		virtual bool draw(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, const RectF& area, double size, const TextStyle& textStyle, const ColorF& color, double lineHeightScale) = 0;

		virtual RectF drawFallback(const FontData& font, const GlyphCluster& cluster, bool useBasePos, const Vec2& pos, const double size, const ColorF& color, double lineHeightScale) = 0;

		[[nodiscard]]
		virtual Array<double> getXAdvances(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, double fontSize) = 0;

		[[nodiscard]]
		virtual double xAdvanceFallback(const FontData& font, const GlyphCluster& cluster, double fontSize) = 0;

		[[nodiscard]]
		virtual RectF region(const FontData& font, StringView s, const Array<GlyphCluster>& clusters, bool useBasePos, const Vec2& pos, const double size, double lineHeightScale) = 0;

		[[nodiscard]]
		virtual RectF regionFallback(const FontData& font, const GlyphCluster& cluster, bool useBasePos, const Vec2& pos, const double size, double lineHeightScale) = 0;

		virtual void setBufferWidth(int32 width) = 0;

		virtual int32 getBufferWidth() const noexcept = 0;

		virtual bool preload(const FontData& font, StringView s) = 0;

		[[nodiscard]]
		virtual const Texture& getTexture() noexcept = 0;

		[[nodiscard]]
		virtual TextureRegion getTextureRegion(const FontData& font, GlyphIndex glyphIndex) = 0;

		[[nodiscard]]
		virtual int32 getBufferThickness(GlyphIndex glyphIndex) = 0;
	};
}
