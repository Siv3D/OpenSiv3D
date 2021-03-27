//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
	class P2Circle : public P2Shape
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2Circle(b2Body& body, const Circle& circle, const P2Material& material, const P2Filter& filter, bool isSensor);

		[[nodiscard]]
		P2ShapeType getShapeType() const noexcept override;

		void draw(const ColorF& color = Palette::White) const override;

		void drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		void drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]]
		Circle getCircle() const;

	private:

		std::unique_ptr<b2CircleShape> m_pShape;
	};
}
