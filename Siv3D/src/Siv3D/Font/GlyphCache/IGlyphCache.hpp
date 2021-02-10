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
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/Font.hpp>

namespace s3d
{
	class IGlyphCache
	{
	public:

		virtual ~IGlyphCache() = default;

		virtual RectF draw(const Font& font, StringView s, const Vec2& pos, const double size, const ColorF& color) = 0;

		virtual RectF drawBase(const Font& font, StringView s, const Vec2& pos, const double size, const ColorF& color) = 0;

		[[nodiscard]]
		virtual RectF region(const Font& font, StringView s, const Vec2& pos, const double size) = 0;

		[[nodiscard]]
		virtual RectF regionBase(const Font& font, StringView s, const Vec2& pos, const double size) = 0;

		virtual bool preload(const Font& font, StringView s) = 0;

		[[nodiscard]]
		virtual const Texture& getTexture() const noexcept = 0;
	};
}
