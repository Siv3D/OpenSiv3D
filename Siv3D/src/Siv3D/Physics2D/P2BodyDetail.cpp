//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "P2BodyDetail.hpp"
# include "Physics2DUtility.hpp"

namespace s3d
{
	P2Body::P2BodyDetail::P2BodyDetail(P2World& world, const P2BodyID id, const Vec2& center, const P2BodyType bodyType)
		: m_world(world)
		, m_id(id)
	{
		b2BodyDef bodyDef;
		bodyDef.type = static_cast<b2BodyType>(bodyType);
		bodyDef.position = detail::ToB2Vec2(center);
		m_body = world.getWorldPtr()->CreateBody(&bodyDef);
	}

	P2Body::P2BodyDetail::~P2BodyDetail()
	{
		if (!m_body)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyBody(m_body);
	}

	P2BodyID P2Body::P2BodyDetail::id() const
	{
		return m_id;
	}

	void P2Body::P2BodyDetail::addLine(const Line& line, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Line>(*m_body, line, material, filter));
	}

	void P2Body::P2BodyDetail::addLineString(const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2LineString>(*m_body, lines, closed, material, filter));
	}

	void P2Body::P2BodyDetail::addCircle(const Circle& circle, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Circle>(*m_body, circle, material, filter));
	}

	void P2Body::P2BodyDetail::addRect(const RectF& rect, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Rect>(*m_body, rect, material, filter));
	}

	void P2Body::P2BodyDetail::addTriangle(const Triangle& triangle, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Triangle>(*m_body, triangle, material, filter));
	}

	void P2Body::P2BodyDetail::addQuad(const Quad& quad, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Quad>(*m_body, quad, material, filter));
	}

	void P2Body::P2BodyDetail::addPolygon(const Polygon& polygon, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Polygon>(*m_body, polygon, material, filter));
	}

	b2Body& P2Body::P2BodyDetail::getBody()
	{
		assert(m_body);

		return *m_body;
	}

	const b2Body& P2Body::P2BodyDetail::getBody() const
	{
		assert(m_body);

		return *m_body;
	}

	b2Body* P2Body::P2BodyDetail::getBodyPtr() const
	{
		assert(m_body);

		return m_body;
	}

	const Array<std::shared_ptr<P2Shape>>& P2Body::P2BodyDetail::getShapes() const
	{
		return m_shapes;
	}

	void P2Body::P2BodyDetail::setUserData(P2BodyDetail* data)
	{
		assert(m_body);

		m_body->SetUserData(static_cast<void*>(data));
	}
}
