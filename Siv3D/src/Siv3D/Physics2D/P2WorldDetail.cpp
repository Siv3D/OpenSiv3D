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
# include "P2WorldDetail.hpp"
# include "P2Common.hpp"

namespace s3d
{
	detail::P2WorldDetail::P2WorldDetail(const Vec2 gravity)
		: m_world{ detail::ToB2Vec2(gravity) }
	{
		m_world.SetContactListener(&m_contactListner);
	}

	void detail::P2WorldDetail::update(const double timeStep, const int32 velocityIterations, const int32 positionIterations)
	{
		m_contactListner.clearContacts();

		m_world.Step(static_cast<float>(timeStep), velocityIterations, positionIterations);
	}

	P2Body detail::P2WorldDetail::createPlaceholder(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& center)
	{
		return P2Body{ world, generateNextID(), center, bodyType };
	}

	P2Body detail::P2WorldDetail::createLine(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addLine(localPos, oneSided, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createLineSensor(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addLineSensor(localPos, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createLineString(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addLineString(localPos, oneSided, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createLineStringSensor(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addLineStringSensor(localPos, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createClosedLineString(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addClosedLineString(localPos, oneSided, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createClosedLineStringSensor(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addClosedLineStringSensor(localPos, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createCircle(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addCircle(localPos, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createCircleSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addCircleSensor(localPos, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createRect(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addRect(localPos, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createRectSensor(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addRectSensor(localPos, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createTriangle(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addTriangle(localPos, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createTriangleSensor(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addTriangleSensor(localPos, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createQuad(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addQuad(localPos, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createQuadSensor(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addQuadSensor(localPos, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createPolygon(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Material& material, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addPolygon(localPos, material, filter);

		return body;
	}

	P2Body detail::P2WorldDetail::createPolygonSensor(const std::shared_ptr<P2WorldDetail>& world, const P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Filter& filter)
	{
		P2Body body{ world, generateNextID(), worldPos, bodyType };

		body.addPolygonSensor(localPos, filter);

		return body;
	}

	P2PivotJoint detail::P2WorldDetail::createPivotJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const EnableCollision enableCollision)
	{
		return P2PivotJoint{ world, bodyA, bodyB, worldAnchorPos, enableCollision };
	}

	P2DistanceJoint detail::P2WorldDetail::createDistanceJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, const double length, const EnableCollision enableCollision)
	{
		return P2DistanceJoint{ world, bodyA, worldAnchorPosA, bodyB, worldAnchorPosB, length, enableCollision };
	}

	P2SliderJoint detail::P2WorldDetail::createSliderJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, const EnableCollision enableCollision)
	{
		return P2SliderJoint{ world, bodyA, bodyB, worldAnchorPos, normalizedAxis, enableCollision };
	}

	P2WheelJoint detail::P2WorldDetail::createWheelJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, const EnableCollision enableCollision)
	{
		return P2WheelJoint{ world, bodyA, bodyB, worldAnchorPos, normalizedAxis, enableCollision };
	}

	P2MouseJoint detail::P2WorldDetail::createMouseJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& body, const Vec2& worldTargetPos)
	{
		return P2MouseJoint{ world, body, worldTargetPos };
	}

	const HashTable<P2ContactPair, P2Collision>& detail::P2WorldDetail::getCollisions() const noexcept
	{
		return m_contactListner.getCollisions();
	}

	b2World& detail::P2WorldDetail::getData() noexcept
	{
		return m_world;
	}

	const b2World& detail::P2WorldDetail::getData() const noexcept
	{
		return m_world;
	}

	b2World* detail::P2WorldDetail::getWorldPtr() noexcept
	{
		return &m_world;
	}

	P2BodyID detail::P2WorldDetail::generateNextID() noexcept
	{
		return ++m_currentID;
	}
}
