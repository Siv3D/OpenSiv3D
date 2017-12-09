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

		TexturedQuad(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Quad& _quad,
			const Float2& _center)
			: quad(_quad)
			, texture(_texture)
			, uvRect(l, t, r, b)
			, center(_center) {}

		TexturedQuad(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Quad& _quad,
			const Float2& _center)
			: quad(_quad)
			, texture(_texture)
			, uvRect(_uvRect)
			, center(_center) {}

		const Quad& draw(const ColorF& diffuse = Palette::White) const;

		Quad draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		Quad draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const
		{
			return draw(pos.x, pos.y, diffuse);
		}

		Quad drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		Quad drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const
		{
			return drawAt(pos.x, pos.y, diffuse);
		}
	};
}
