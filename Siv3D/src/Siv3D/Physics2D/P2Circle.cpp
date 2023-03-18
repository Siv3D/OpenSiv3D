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

# include <Siv3D/Physics2D/P2Circle.hpp>
# include "P2Common.hpp"

namespace s3d
{
	P2Circle::P2Circle(b2Body& body, const Circle& circle, const P2Material& material, const P2Filter& filter, const bool isSensor)
		: m_pShape{ std::make_unique<b2CircleShape>() }
	{
		m_pShape->m_radius = static_cast<float>(circle.r);

		m_pShape->m_p.Set(static_cast<float>(circle.x), static_cast<float>(circle.y));

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter, isSensor);

		m_fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Circle::getShapeType() const noexcept
	{
		return P2ShapeType::Circle;
	}

	const P2Shape& P2Circle::draw(const ColorF& color) const
	{
		getCircle().draw(color);

		return *this;
	}

	const P2Shape& P2Circle::drawFrame(const double thickness, const ColorF& color) const
	{
		getCircle().drawFrame(detail::AdjustThickness(thickness), color);

		return *this;
	}

	const P2Shape& P2Circle::drawWireframe(double thickness, const ColorF& color) const
	{
		const Circle circle = getCircle();
		const double angle = m_fixtures.front()->GetBody()->GetAngle();
		thickness = detail::AdjustThickness(thickness);
		circle.drawFrame(thickness, color);
		Line{ circle.center, circle.getPointByAngle(angle) }.draw(thickness, color);

		return *this;
	}

	Circle P2Circle::getCircle() const
	{
		return{ detail::CalcVec2(m_pShape->m_p, m_fixtures.front()->GetBody()->GetTransform()), m_pShape->m_radius };
	}
}
