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
	class P2Triangle : public P2Shape
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2Triangle(b2Body& body, const Triangle& triangle, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2ShapeType getShapeType() const noexcept override;

		const P2Shape& draw(const ColorF& color = Palette::White) const override;

		const P2Shape& drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		const P2Shape& drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]]
		Triangle getTriangle() const;

	private:

		std::unique_ptr<b2PolygonShape> m_pShape;
	};
}
