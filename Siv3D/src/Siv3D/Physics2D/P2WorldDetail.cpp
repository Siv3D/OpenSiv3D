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

# include "P2WorldDetail.hpp"
# include "Physics2DUtility.hpp"

namespace s3d
{
	P2World::P2WorldDetail::P2WorldDetail(const Vec2& gravity)
		: m_world(detail::ToB2Vec2(gravity))
	{
		m_world.SetContactListener(&m_contactListner);
	}

	void P2World::P2WorldDetail::update(const double timeStep, const int32 velocityIterations, const int32 positionIterations)
	{
		m_contactListner.clearContacts();

		m_world.Step(static_cast<float32>(timeStep), velocityIterations, positionIterations);
	}

	P2Body P2World::P2WorldDetail::createDummy(P2World& world, const Vec2& center, const P2BodyType bodyType)
	{
		return P2Body(world, generateNextID(), center, bodyType);
	}

	P2Body P2World::P2WorldDetail::createLine(P2World& world, const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addLine(line, material, filter);

		return body;
	}

	P2Body P2World::P2WorldDetail::createLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addLineString(lines, material, filter);

		return body;
	}

	P2Body P2World::P2WorldDetail::createClosedLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addClosedLineString(lines, material, filter);

		return body;
	}

	P2Body P2World::P2WorldDetail::createCircle(P2World& world, const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addCircle(circle, material, filter);

		return body;
	}

	P2Body P2World::P2WorldDetail::createRect(P2World& world, const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addRect(rect, material, filter);

		return body;
	}

	P2Body P2World::P2WorldDetail::createTriangle(P2World& world, const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addTriangle(triangle, material, filter);

		return body;
	}

	P2Body P2World::P2WorldDetail::createQuad(P2World& world, const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addQuad(quad, material, filter);

		return body;
	}

	P2Body P2World::P2WorldDetail::createPolygon(P2World& world, const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, const P2BodyType bodyType)
	{
		P2Body body(world, generateNextID(), center, bodyType);

		body.addPolygon(polygon, material, filter);

		return body;
	}

	P2PivotJoint P2World::P2WorldDetail::createPivotJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
	{
		return P2PivotJoint(world, bodyA, bodyB, anchorPos);
	}

	P2DistanceJoint P2World::P2WorldDetail::createDistanceJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double length)
	{
		return P2DistanceJoint(world, bodyA, anchorPosA, bodyB, anchorPosB, length);
	}

	P2RopeJoint P2World::P2WorldDetail::createRopeJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double maxLength)
	{
		return P2RopeJoint(world, bodyA, anchorPosA, bodyB, anchorPosB, maxLength);
	}

	P2SliderJoint P2World::P2WorldDetail::createSliderJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis)
	{
		return P2SliderJoint(world, bodyA, bodyB, anchorPos, normalizedAxis);
	}

	const HashTable<P2ContactPair, P2Collision>& P2World::P2WorldDetail::getCollisions() const
	{
		return m_contactListner.getCollisions();
	}

	b2World& P2World::P2WorldDetail::getData()
	{
		return m_world;
	}

	const b2World& P2World::P2WorldDetail::getData() const
	{
		return m_world;
	}

	b2World* P2World::P2WorldDetail::getWorldPtr()
	{
		return &m_world;
	}

	P2BodyID P2World::P2WorldDetail::generateNextID()
	{
		return ++m_currentID;
	}
}
