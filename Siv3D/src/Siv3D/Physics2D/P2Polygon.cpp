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

# include <Siv3D/Physics2D/P2Polygon.hpp>
# include <Siv3D/Polygon.hpp>
# include "P2Common.hpp"

namespace s3d
{
	P2Polygon::P2Polygon(b2Body& body, const Polygon& polygon, const P2Material& material, const P2Filter& filter, const bool isSensor)
		: m_basePolygon{ polygon }
	{
		b2PolygonShape m_shape;

		for (size_t i = 0; i < polygon.num_triangles(); ++i)
		{
			const auto triangle = polygon.triangle(i);

			const b2Vec2 points[3] = { detail::ToB2Vec2(triangle.p0), detail::ToB2Vec2(triangle.p1), detail::ToB2Vec2(triangle.p2) };

			m_shape.Set(points, 3);

			const b2FixtureDef fixtureDef = detail::MakeFixtureDef(&m_shape, material, filter, isSensor);

			m_fixtures.push_back(body.CreateFixture(&fixtureDef));
		}
	}

	P2ShapeType P2Polygon::getShapeType() const noexcept
	{
		return P2ShapeType::Polygon;
	}

	const P2Shape& P2Polygon::draw(const ColorF& color) const
	{
		const b2Transform& transform = m_fixtures.front()->GetBody()->GetTransform();

		m_basePolygon.drawTransformed(transform.q.s, transform.q.c, Vec2(transform.p.x, transform.p.y), color);
	
		return *this;
	}

	const P2Shape& P2Polygon::drawFrame(const double thickness, const ColorF& color) const
	{
		getPolygon().drawFrame(detail::AdjustThickness(thickness), color);

		return *this;
	}

	const P2Shape& P2Polygon::drawWireframe(const double thickness, const ColorF& color) const
	{
		getPolygon().drawWireframe(detail::AdjustThickness(thickness), color);

		return *this;
	}

	Polygon P2Polygon::getPolygon() const
	{
		if (m_fixtures.isEmpty())
		{
			return m_basePolygon;
		}

		const b2Transform& transform = m_fixtures.front()->GetBody()->GetTransform();

		return m_basePolygon.transformed(transform.q.s, transform.q.c, Vec2{ transform.p.x, transform.p.y });
	}
}
