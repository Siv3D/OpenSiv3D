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

# include <Siv3D/Physics2D/P2Body.hpp>
# include <Siv3D/Physics2D/P2Line.hpp>
# include <Siv3D/Physics2D/P2LineString.hpp>
# include <Siv3D/Physics2D/P2Circle.hpp>
# include <Siv3D/Physics2D/P2Rect.hpp>
# include <Siv3D/Physics2D/P2Triangle.hpp>
# include <Siv3D/Physics2D/P2Quad.hpp>
# include <Siv3D/Physics2D/P2Polygon.hpp>
# include "P2BodyDetail.hpp"
# include "P2WorldDetail.hpp"
# include "P2Common.hpp"

void b2Body::SetUserData(void* pointer)
{
	m_userData.pBody = pointer;
}

namespace s3d
{
	P2Body::P2BodyDetail::P2BodyDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2BodyID id, const Vec2& center, const P2BodyType bodyType)
		: m_world{ world }
		, m_id{ id }
	{
		b2BodyDef bodyDef;
		bodyDef.type		= static_cast<b2BodyType>(bodyType);
		bodyDef.position	= detail::ToB2Vec2(center);
		m_body = m_world->getWorldPtr()->CreateBody(&bodyDef);
		m_body->SetUserData(this);
	}

	P2Body::P2BodyDetail::~P2BodyDetail()
	{
		if (not m_body)
		{
			return;
		}

		m_world->getWorldPtr()->DestroyBody(m_body);
	}

	P2BodyID P2Body::P2BodyDetail::id() const noexcept
	{
		return m_id;
	}

	void P2Body::P2BodyDetail::addLine(const Line& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Line>(*m_body, localPos, oneSided, material, filter, false));
	}

	void P2Body::P2BodyDetail::addLineSensor(const Line& localPos, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Line>(*m_body, localPos, OneSided::No, P2Material{}, filter, true));
	}

	void P2Body::P2BodyDetail::addLineString(const LineString& localPos, const CloseRing closeRing, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2LineString>(*m_body, localPos, closeRing, oneSided, material, filter, false));
	}

	void P2Body::P2BodyDetail::addLineStringSensor(const LineString& localPos, const CloseRing closeRing, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2LineString>(*m_body, localPos, closeRing, OneSided::No, P2Material{}, filter, true));
	}

	void P2Body::P2BodyDetail::addCircle(const Circle& localPos, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Circle>(*m_body, localPos, material, filter, false));
	}

	void P2Body::P2BodyDetail::addCircleSensor(const Circle& localPos, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Circle>(*m_body, localPos, P2Material{}, filter, true));
	}

	void P2Body::P2BodyDetail::addRect(const RectF& localPos, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Rect>(*m_body, localPos, material, filter, false));
	}

	void P2Body::P2BodyDetail::addRectSensor(const RectF& localPos, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Rect>(*m_body, localPos, P2Material{}, filter, true));
	}

	void P2Body::P2BodyDetail::addTriangle(const Triangle& localPos, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Triangle>(*m_body, localPos, material, filter, false));
	}

	void P2Body::P2BodyDetail::addTriangleSensor(const Triangle& localPos, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Triangle>(*m_body, localPos, P2Material{}, filter, true));
	}

	void P2Body::P2BodyDetail::addQuad(const Quad& localPos, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Quad>(*m_body, localPos, material, filter, false));
	}

	void P2Body::P2BodyDetail::addQuadSensor(const Quad& localPos, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Quad>(*m_body, localPos, P2Material{}, filter, true));
	}

	void P2Body::P2BodyDetail::addPolygon(const Polygon& localPos, const P2Material& material, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Polygon>(*m_body, localPos, material, filter, false));
	}

	void P2Body::P2BodyDetail::addPolygonSensor(const Polygon& localPos, const P2Filter& filter)
	{
		assert(m_body);

		m_shapes.push_back(std::make_shared<P2Polygon>(*m_body, localPos, P2Material{}, filter, true));
	}

	b2Body& P2Body::P2BodyDetail::getBody() noexcept
	{
		assert(m_body);

		return *m_body;
	}

	const b2Body& P2Body::P2BodyDetail::getBody() const noexcept
	{
		assert(m_body);

		return *m_body;
	}

	b2Body* P2Body::P2BodyDetail::getBodyPtr() const
	{
		assert(m_body);

		return m_body;
	}

	const Array<std::shared_ptr<P2Shape>>& P2Body::P2BodyDetail::getShapes() const noexcept
	{
		return m_shapes;
	}
}
