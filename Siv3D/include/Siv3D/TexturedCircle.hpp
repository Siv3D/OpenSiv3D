//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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

		TexturedCircle();

		TexturedCircle(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Circle& _circle);

		TexturedCircle(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Circle& _circle);

		const Circle& draw(const ColorF& diffuse = Palette::White) const;

		Circle draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		Circle draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const;
	};
}
