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

# include <Siv3D/Physics2D/P2Line.hpp>
# include "P2Common.hpp"

namespace s3d
{
	P2Line::P2Line(b2Body& body, const Line& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter, const bool isSensor)
		: m_pShape{ std::make_unique<b2EdgeShape>() }
		, m_oneSided{ oneSided }
	{
		const b2Vec2 p0 = detail::ToB2Vec2(localPos.begin);
		const b2Vec2 p1 = detail::ToB2Vec2(localPos.end);

		if (m_oneSided)
		{
			m_pShape->SetOneSided(p0, p0, p1, p1);
		}
		else
		{
			m_pShape->SetTwoSided(p0, p1);
		}

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter, isSensor);

		m_fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Line::getShapeType() const noexcept
	{
		return P2ShapeType::Line;
	}

	bool P2Line::isOneSided() const noexcept
	{
		return m_oneSided;
	}

	const P2Shape& P2Line::draw(const ColorF& color) const
	{
		getLine().draw(detail::AdjustThickness(detail::P2LineThickness), color);

		return *this;
	}

	const P2Shape& P2Line::drawFrame(const double thickness, const ColorF& color) const
	{
		getLine().draw(detail::AdjustThickness(thickness), color);

		return *this;
	}

	const P2Shape& P2Line::drawWireframe(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness, color);
	}

	Line P2Line::getLine() const
	{
		const b2Transform& transform = m_fixtures.front()->GetBody()->GetTransform();
		return{ detail::CalcVec2(m_pShape->m_vertex1, transform), detail::CalcVec2(m_pShape->m_vertex2, transform) };
	}
}
