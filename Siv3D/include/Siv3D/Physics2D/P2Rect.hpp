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
# include "../Common.hpp"
# include "../2DShapes.hpp"
# include "P2Fwd.hpp"
# include "P2Shape.hpp"

namespace s3d
{
	class P2Rect : public P2Shape
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2Rect(b2Body& body, const RectF& rect, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2ShapeType getShapeType() const noexcept override;

		const P2Shape& draw(const ColorF& color = Palette::White) const override;

		const P2Shape& draw(const ColorF(&colors)[4]) const;

		const P2Shape& draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		const P2Shape& draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		const P2Shape& drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		const P2Shape& drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]]
		Quad getQuad() const;

	private:

		std::unique_ptr<b2PolygonShape> m_pShape;
	};
}