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

# include <Siv3D/TexturedCircle.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	TexturedCircle::TexturedCircle(const Texture& _texture, const float l, const float t, const float r, const float b, const Circle& _circle)
		: circle{ _circle }
		, texture{ _texture }
		, uvRect{ l, t, r, b } {}

	TexturedCircle::TexturedCircle(const Texture& _texture, const FloatRect& _uvRect, const Circle& _circle)
		: circle{ _circle }
		, texture{ _texture }
		, uvRect{ _uvRect } {}

	const Circle& TexturedCircle::draw(const ColorF& diffuse) const
	{
		SIV3D_ENGINE(Renderer2D)->addTexturedCircle(texture, circle, uvRect, diffuse.toFloat4());

		return circle;
	}

	Circle TexturedCircle::draw(const double x, const double y, const ColorF& diffuse) const
	{
		const Circle c{ x, y, circle.r };

		SIV3D_ENGINE(Renderer2D)->addTexturedCircle(texture, c, uvRect, diffuse.toFloat4());

		return c;
	}

	Circle TexturedCircle::draw(const Vec2& pos, const ColorF& diffuse) const
	{
		return draw(pos.x, pos.y, diffuse);
	}
}
