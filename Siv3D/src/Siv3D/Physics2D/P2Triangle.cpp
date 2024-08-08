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

# include <Siv3D/Physics2D/P2Triangle.hpp>
# include "P2Common.hpp"

namespace s3d
{
	P2Triangle::P2Triangle(b2Body& body, const Triangle& triangle, const P2Material& material, const P2Filter& filter, bool const isSensor)
		: m_pShape{ std::make_unique<b2PolygonShape>() }
	{
		const b2Vec2 points[3] = { detail::ToB2Vec2(triangle.p0), detail::ToB2Vec2(triangle.p1), detail::ToB2Vec2(triangle.p2) };

		m_pShape->Set(points, 3);

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter, isSensor);

		m_fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Triangle::getShapeType() const noexcept
	{
		return P2ShapeType::Triangle;
	}

	const P2Shape& P2Triangle::draw(const ColorF& color) const
	{
		getTriangle().draw(color);

		return *this;
	}

	const P2Shape& P2Triangle::drawFrame(const double thickness, const ColorF& color) const
	{
		getTriangle().drawFrame(detail::AdjustThickness(thickness), color);

		return *this;
	}

	const P2Shape& P2Triangle::drawWireframe(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness, color);
	}

	Triangle P2Triangle::getTriangle() const
	{
		const b2Transform& transform = m_fixtures.front()->GetBody()->GetTransform();
		return{
			detail::CalcVec2(m_pShape->m_vertices[0], transform),
			detail::CalcVec2(m_pShape->m_vertices[1], transform),
			detail::CalcVec2(m_pShape->m_vertices[2], transform) };
	}
}
