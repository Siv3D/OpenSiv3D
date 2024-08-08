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

# pragma once
# include "../Common.hpp"
# include "../2DShapes.hpp"
# include "P2Fwd.hpp"
# include "P2Shape.hpp"

namespace s3d
{
	class P2Quad : public P2Shape
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2Quad(b2Body& body, const Quad& quad, const P2Material& material, const P2Filter& filter, bool isSensor);

		[[nodiscard]]
		P2ShapeType getShapeType() const noexcept override;

		const P2Shape& draw(const ColorF& color = Palette::White) const override;

		const P2Shape& drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		const P2Shape& drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]]
		Quad getQuad() const;

	private:

		std::unique_ptr<b2PolygonShape> m_pShape;
	};
}
