//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Circle.hpp"
# include "Texture.hpp"
# include "FloatRect.hpp"

namespace s3d
{
	struct TexturedCircle
	{
		Circle circle;

		Texture texture;

		FloatRect uvRect;

		TexturedCircle(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Circle& _circle)
			: circle(_circle)
			, texture(_texture)
			, uvRect(l, t, r, b) {}

		TexturedCircle(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Circle& _circle)
			: circle(_circle)
			, texture(_texture)
			, uvRect(_uvRect) {}

		const Circle& draw(const ColorF& diffuse = Palette::White) const;

		Circle draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		Circle draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const
		{
			return draw(pos.x, pos.y, diffuse);
		}
	};
}
