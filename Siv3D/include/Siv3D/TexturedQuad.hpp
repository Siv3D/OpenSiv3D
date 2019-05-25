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
# include "Texture.hpp"
# include "FloatRect.hpp"

namespace s3d
{
	struct TexturedQuad
	{
		Quad quad;

		Texture texture;

		FloatRect uvRect;

		Float2 center;

		TexturedQuad();

		TexturedQuad(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Quad& _quad,
			const Float2& _center);

		TexturedQuad(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Quad& _quad,
			const Float2& _center);

		const Quad& draw(const ColorF& diffuse = Palette::White) const;

		Quad draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		Quad draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		Quad drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		Quad drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;
	};
}
