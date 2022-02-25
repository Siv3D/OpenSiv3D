//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Texture.hpp"
# include "FloatRect.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	struct TexturedQuad
	{
		Quad quad;

		Texture texture;

		FloatRect uvRect;

		Float2 center;

		SIV3D_NODISCARD_CXX20
		TexturedQuad() = default;

		SIV3D_NODISCARD_CXX20
		TexturedQuad(const Texture& _texture, float l, float t, float r, float b, const Quad& _quad, const Float2& _center);

		SIV3D_NODISCARD_CXX20
		TexturedQuad(const Texture& _texture, const FloatRect& _uvRect, const Quad& _quad, const Float2& _center);

		const Quad& draw(const ColorF& diffuse = Palette::White) const;

		Quad draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		Quad draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		Quad drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		Quad drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;
	};
}
