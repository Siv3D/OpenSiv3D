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
# include "RoundRect.hpp"
# include "FloatRect.hpp"

namespace s3d
{
	struct TexturedRoundRect
	{
		RoundRect rect;

		Texture texture;

		FloatRect uvRect;

		TexturedRoundRect();

		TexturedRoundRect(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const RoundRect& _rect);

		TexturedRoundRect(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const RoundRect& _rect);

		const RoundRect& draw(const ColorF& diffuse = Palette::White) const;

		RoundRect drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		RoundRect drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;
	};
}
