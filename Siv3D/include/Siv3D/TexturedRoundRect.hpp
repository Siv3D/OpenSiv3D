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
	struct TexturedRoundRect
	{
		RoundRect rect;

		Texture texture;

		FloatRect uvRect;

		SIV3D_NODISCARD_CXX20
		TexturedRoundRect() = default;

		SIV3D_NODISCARD_CXX20
		TexturedRoundRect(const Texture& _texture, float l, float t, float r, float b, const RoundRect& _rect);

		SIV3D_NODISCARD_CXX20
		TexturedRoundRect(const Texture& _texture, const FloatRect& _uvRect, const RoundRect& _rect);

		const RoundRect& draw(const ColorF& diffuse = Palette::White) const;

		RoundRect draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		RoundRect draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RoundRect drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		RoundRect drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;
	};
}
