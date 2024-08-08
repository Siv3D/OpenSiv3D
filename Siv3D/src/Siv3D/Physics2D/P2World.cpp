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

# include <Siv3D/Physics2D/P2World.hpp>
# include <Siv3D/MultiPolygon.hpp>
# include "P2WorldDetail.hpp"

namespace s3d
{
	P2World::P2World(const double gravity)
		: P2World{ Vec2{ 0.0, gravity } } {}

	P2World::P2World(const Vec2 gravity)
		: pImpl{ std::make_shared<detail::P2WorldDetail>(gravity) } {}

	void P2World::update(const double timeStep, const int32 velocityIterations, const int32 positionIterations) const
	{
		return pImpl->update(timeStep, velocityIterations, positionIterations);
	}

	void P2World::setSleepEnabled(const bool enabled)
	{
		pImpl->getData().SetAllowSleeping(enabled);
	}

	bool P2World::getSleepEnabled() const
	{
		return pImpl->getData().GetAllowSleeping();
	}

	void P2World::setGravity(const double gravity)
	{
		setGravity(Vec2{ 0.0, gravity });
	}

	void P2World::setGravity(const Vec2& gravity)
	{
		pImpl->getData().SetGravity(detail::ToB2Vec2(gravity));
	}

	Vec2 P2World::getGravity() const
	{
		return detail::ToVec2(pImpl->getData().GetGravity());
	}

	void P2World::shiftOrigin(const Vec2& newOrigin)
	{
		pImpl->getData().ShiftOrigin(detail::ToB2Vec2(newOrigin));
	}

	P2Body P2World::createPlaceholder(const P2BodyType bodyType, const Vec2& worldPos)
	{
		return pImpl->createPlaceholder(pImpl, bodyType, worldPos);
	}

	P2Body P2World::createLine(const P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		if (bodyType == P2BodyType::Dynamic)
		{
			throw Error{ U"P2World::createLine(): bodyType must be either P2BodyType::Static or P2BodyType::Kinematic" };
		}

		return pImpl->createLine(pImpl, bodyType, worldPos, localPos, oneSided, material, filter);
	}

	P2Body P2World::createLineSensor(const P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, const P2Filter& filter)
	{
		if (bodyType == P2BodyType::Dynamic)
		{
			throw Error{ U"P2World::createLineSensor(): bodyType must be either P2BodyType::Static or P2BodyType::Kinematic" };
		}

		return pImpl->createLineSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createLineString(const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		if (bodyType == P2BodyType::Dynamic)
		{
			throw Error{ U"P2World::createLineString(): bodyType must be either P2BodyType::Static or P2BodyType::Kinematic" };
		}

		return pImpl->createLineString(pImpl, bodyType, worldPos, localPos, oneSided, material, filter);
	}

	P2Body P2World::createLineStringSensor(const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const P2Filter& filter)
	{
		if (bodyType == P2BodyType::Dynamic)
		{
			throw Error{ U"P2World::createLineStringSensor(): bodyType must be either P2BodyType::Static or P2BodyType::Kinematic" };
		}

		return pImpl->createLineStringSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createClosedLineString(const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const OneSided oneSided, const P2Material& material, const P2Filter& filter)
	{
		if (bodyType == P2BodyType::Dynamic)
		{
			throw Error{ U"P2World::createClosedLineString(): bodyType must be either P2BodyType::Static or P2BodyType::Kinematic" };
		}

		return pImpl->createClosedLineString(pImpl, bodyType, worldPos, localPos, oneSided, material, filter);
	}

	P2Body P2World::createClosedLineStringSensor(const P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const P2Filter& filter)
	{
		if (bodyType == P2BodyType::Dynamic)
		{
			throw Error{ U"P2World::createClosedLineStringSensor(): bodyType must be either P2BodyType::Static or P2BodyType::Kinematic" };
		}

		return pImpl->createClosedLineStringSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createCircle(const P2BodyType bodyType, const Vec2& worldPos, const double r, const P2Material& material, const P2Filter& filter)
	{
		return createCircle(bodyType, worldPos, Circle{ 0, 0, r }, material, filter);
	}

	P2Body P2World::createCircle(const P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Material& material, const P2Filter& filter)
	{
		return pImpl->createCircle(pImpl, bodyType, worldPos, localPos, material, filter);
	}

	P2Body P2World::createCircleSensor(const P2BodyType bodyType, const Vec2& worldPos, const double r, const P2Filter& filter)
	{
		return pImpl->createCircleSensor(pImpl, bodyType, worldPos, Circle{ 0, 0, r }, filter);
	}

	P2Body P2World::createCircleSensor(const P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Filter& filter)
	{
		return pImpl->createCircleSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createRect(const P2BodyType bodyType, const Vec2& worldPos, const double size, const P2Material& material, const P2Filter& filter)
	{
		return createRect(bodyType, worldPos, RectF{ Arg::center(0, 0), size }, material, filter);
	}

	P2Body P2World::createRect(const P2BodyType bodyType, const Vec2& worldPos, const SizeF& size, const P2Material& material, const P2Filter& filter)
	{
		return createRect(bodyType, worldPos, RectF{ Arg::center(0, 0), size }, material, filter);
	}

	P2Body P2World::createRect(const P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Material& material, const P2Filter& filter)
	{
		return pImpl->createRect(pImpl, bodyType, worldPos, localPos, material, filter);
	}

	P2Body P2World::createRectSensor(const P2BodyType bodyType, const Vec2& worldPos, const double size, const P2Filter& filter)
	{
		return createRectSensor(bodyType, worldPos, RectF{ Arg::center(0, 0), size }, filter);
	}

	P2Body P2World::createRectSensor(const P2BodyType bodyType, const Vec2& worldPos, const SizeF& size, const P2Filter& filter)
	{
		return createRectSensor(bodyType, worldPos, RectF{ Arg::center(0, 0), size }, filter);
	}

	P2Body P2World::createRectSensor(const P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Filter& filter)
	{
		return pImpl->createRectSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createTriangle(const P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Material& material, const P2Filter& filter)
	{
		return pImpl->createTriangle(pImpl, bodyType, worldPos, localPos, material, filter);
	}

	P2Body P2World::createTriangleSensor(const P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Filter& filter)
	{
		return pImpl->createTriangleSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createQuad(const P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Material& material, const P2Filter& filter)
	{
		return pImpl->createQuad(pImpl, bodyType, worldPos, localPos, material, filter);
	}

	P2Body P2World::createQuadSensor(const P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Filter& filter)
	{
		return pImpl->createQuadSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createPolygon(const P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Material& material, const P2Filter& filter)
	{
		return pImpl->createPolygon(pImpl, bodyType, worldPos, localPos, material, filter);
	}

	P2Body P2World::createPolygonSensor(const P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Filter& filter)
	{
		return pImpl->createPolygonSensor(pImpl, bodyType, worldPos, localPos, filter);
	}

	P2Body P2World::createPolygons(const P2BodyType bodyType, const Vec2& worldPos, const MultiPolygon& localPos, const P2Material& material, const P2Filter& filter)
	{
		const size_t num_polygons = localPos.size();

		if (num_polygons == 0)
		{
			return createPlaceholder(bodyType, worldPos);
		}
		else if (num_polygons == 1)
		{
			return createPolygon(bodyType, worldPos, localPos.front(), material, filter);
		}
		else
		{
			P2Body body = createPolygon(bodyType, worldPos, localPos.front(), material, filter);

			for (size_t i = 1; i < num_polygons; ++i)
			{
				body.addPolygon(localPos[i], material, filter);
			}

			return body;
		}
	}

	P2PivotJoint P2World::createPivotJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const EnableCollision enableCollision)
	{
		return pImpl->createPivotJoint(pImpl, bodyA, bodyB, worldAnchorPos, enableCollision);
	}

	P2DistanceJoint P2World::createDistanceJoint(const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, const double length, const EnableCollision enableCollision)
	{
		return pImpl->createDistanceJoint(pImpl, bodyA, worldAnchorPosA, bodyB, worldAnchorPosB, length, enableCollision);
	}

	P2SliderJoint P2World::createSliderJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, const EnableCollision enableCollision)
	{
		return pImpl->createSliderJoint(pImpl, bodyA, bodyB, worldAnchorPos, normalizedAxis, enableCollision);
	}

	P2WheelJoint P2World::createWheelJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, const EnableCollision enableCollision)
	{
		return pImpl->createWheelJoint(pImpl, bodyA, bodyB, worldAnchorPos, normalizedAxis, enableCollision);
	}

	P2MouseJoint P2World::createMouseJoint(const P2Body& body, const Vec2& worldTargetPos)
	{
		return pImpl->createMouseJoint(pImpl, body, worldTargetPos);
	}

	const HashTable<P2ContactPair, P2Collision>& P2World::getCollisions() const noexcept
	{
		return pImpl->getCollisions();
	}
}
