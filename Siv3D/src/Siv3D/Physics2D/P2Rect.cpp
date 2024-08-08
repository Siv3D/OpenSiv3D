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

# include <Siv3D/Physics2D/P2Rect.hpp>
# include "P2Common.hpp"

namespace s3d
{
	P2Rect::P2Rect(b2Body& body, const RectF& rect, const P2Material& material, const P2Filter& filter, const bool isSensor)
		: m_pShape{ std::make_unique<b2PolygonShape>() }
	{
		m_pShape->SetAsBox(static_cast<float>(rect.w * 0.5), static_cast<float>(rect.h * 0.5), detail::ToB2Vec2(rect.center()), 0.0f);

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter, isSensor);

		m_fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2Rect::getShapeType() const noexcept
	{
		return P2ShapeType::Rect;
	}

	const P2Shape& P2Rect::draw(const ColorF& color) const
	{
		getQuad().draw(color);

		return *this;
	}

	const P2Shape& P2Rect::draw(const ColorF(&colors)[4]) const
	{
		getQuad().draw(colors[0], colors[1], colors[2], colors[3]);

		return *this;
	}

	const P2Shape& P2Rect::draw(const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		draw({ *topColor, *topColor, *bottomColor, *bottomColor });

		return *this;
	}

	const P2Shape& P2Rect::draw(const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
	{
		draw({ *leftColor, *rightColor, *rightColor, *leftColor });

		return *this;
	}

	const P2Shape& P2Rect::drawFrame(const double thickness, const ColorF& color) const
	{
		getQuad().drawFrame(detail::AdjustThickness(thickness), color);

		return *this;
	}

	const P2Shape& P2Rect::drawWireframe(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness, color);
	}

	Quad P2Rect::getQuad() const
	{
		const b2Transform& transform = m_fixtures.front()->GetBody()->GetTransform();
		const float x0 = m_pShape->m_vertices[0].x;
		const float x1 = m_pShape->m_vertices[1].x;
		const float y0 = m_pShape->m_vertices[0].y;
		const float y1 = m_pShape->m_vertices[2].y;

		return Quad{
			detail::CalcVec2(b2Vec2{ x0, y0 }, transform),
			detail::CalcVec2(b2Vec2{ x1, y0 }, transform),
			detail::CalcVec2(b2Vec2{ x1, y1 }, transform),
			detail::CalcVec2(b2Vec2{ x0, y1 }, transform) };
	}
}
