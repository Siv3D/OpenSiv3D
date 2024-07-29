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

# include <Siv3D/Physics2D/P2Quad.hpp>
# include "P2Common.hpp"

namespace s3d
{
	P2Quad::P2Quad(b2Body& body, const Quad& quad, const P2Material& material, const P2Filter& filter, bool const isSensor)
		: m_pShape{ std::make_unique<b2PolygonShape>() }
	{
		const b2Vec2 points[4] = { detail::ToB2Vec2(quad.p0), detail::ToB2Vec2(quad.p1), detail::ToB2Vec2(quad.p2), detail::ToB2Vec2(quad.p3) };

		m_pShape->Set(points, 4);

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter, isSensor);

		m_fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Quad::getShapeType() const noexcept
	{
		return P2ShapeType::Quad;
	}

	const P2Shape& P2Quad::draw(const ColorF& color) const
	{
		getQuad().draw(color);

		return *this;
	}

	const P2Shape& P2Quad::drawFrame(const double thickness, const ColorF& color) const
	{
		getQuad().drawFrame(detail::AdjustThickness(thickness), color);

		return *this;
	}

	const P2Shape& P2Quad::drawWireframe(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness, color);
	}

	Quad P2Quad::getQuad() const
	{
		const b2Transform& transform = m_fixtures.front()->GetBody()->GetTransform();
		return{
			detail::CalcVec2(m_pShape->m_vertices[0], transform),
			detail::CalcVec2(m_pShape->m_vertices[1], transform),
			detail::CalcVec2(m_pShape->m_vertices[2], transform),
			detail::CalcVec2(m_pShape->m_vertices[3], transform) };
	}
}
