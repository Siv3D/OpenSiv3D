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
# include "../PredefinedYesNo.hpp"
# include "P2Fwd.hpp"
# include "P2Shape.hpp"

namespace s3d
{
	class P2Line : public P2Shape
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2Line(b2Body& body, const Line& localPos, OneSided oneSided, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2ShapeType getShapeType() const noexcept override;

		[[nodiscard]]
		bool isOneSided() const noexcept;

		const P2Shape& draw(const ColorF& color = Palette::White) const override;

		const P2Shape& drawFrame(double thickness, const ColorF& color = Palette::White) const override;

		const P2Shape& drawWireframe(double thickness, const ColorF& color = Palette::White) const override;

		[[nodiscard]]
		Line getLine() const;

	private:

		std::unique_ptr<b2EdgeShape> m_pShape;

		bool m_oneSided = false;
	};
}
