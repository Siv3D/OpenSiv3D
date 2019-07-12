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

# pragma once
# include <atomic>
# include <Siv3D/Physics2D.hpp>
# include <Box2D/Box2D.h>
# include "P2ContactListner.hpp"

namespace s3d
{
	class P2World::P2WorldDetail
	{
	private:

		b2World m_world;

		P2ContactListener m_contactListner;

		std::atomic<P2BodyID> m_currentID = 0;

		P2BodyID generateNextID();

	public:

		P2WorldDetail(const Vec2& gravity);

		void update(double timeStep, int32 velocityIterations, int32 positionIterations);

		[[nodiscard]] P2Body createDummy(P2World& world, const Vec2& center, P2BodyType bodyType);

		[[nodiscard]] P2Body createLine(P2World& world, const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2Body createLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2Body createClosedLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2Body createCircle(P2World& world, const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2Body createRect(P2World& world, const Vec2& center, const RectF& rect, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2Body createTriangle(P2World& world, const Vec2& center, const Triangle& triangle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2Body createQuad(P2World& world, const Vec2& center, const Quad& quad, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2Body createPolygon(P2World& world, const Vec2& center, const Polygon& polygon, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		[[nodiscard]] P2PivotJoint createPivotJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);

		[[nodiscard]] P2DistanceJoint createDistanceJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double length);

		[[nodiscard]] P2RopeJoint createRopeJoint(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double maxLength);

		[[nodiscard]] P2SliderJoint createSliderJoint(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis);

		[[nodiscard]] const HashTable<P2ContactPair, P2Collision>& getCollisions() const;

		[[nodiscard]] b2World& getData();

		[[nodiscard]] const b2World& getData() const;

		[[nodiscard]] b2World* getWorldPtr();
	};
}
