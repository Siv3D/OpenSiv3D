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
	class BitmapGlyphCache : public IGlyphCache
	{
	public:

		BitmapGlyphCache() = default;

		RectF draw(const Font& font, StringView s, const Vec2& pos, double size, const ColorF& color) override;

		RectF drawBase(const Font& font, StringView s, const Vec2& pos, double size, const ColorF& color) override;

		[[nodiscard]]
		RectF region(const Font& font, StringView s, const Vec2& pos, double size) override;

		[[nodiscard]]
		RectF regionBase(const Font& font, StringView s, const Vec2& pos, double size) override;

		bool preload(const Font& font, StringView s) override;

		[[nodiscard]]
		const Texture& getTexture() const noexcept override;

	private:

		[[nodiscard]]
		bool prerender(const Font& font, StringView s, const Array<GlyphCluster>& clusters);

		[[nodiscard]]
		RectF draw(const Font& font, StringView s, const Vec2& pos, double size, const ColorF& color, bool usebasePos);

		[[nodiscard]]
		RectF region(const Font& font, StringView s, const Vec2& pos, double size, bool usebasePos);

		HashTable<GlyphIndex, GlyphCache> m_glyphTable;

		Texture m_texture;

		BufferImage m_buffer = {};
	};
}
