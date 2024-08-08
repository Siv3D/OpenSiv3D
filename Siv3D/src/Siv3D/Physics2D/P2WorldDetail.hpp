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

# pragma once
# include <Siv3D/Physics2D/P2World.hpp>
# include "P2Common.hpp"
# include "P2ContactListener.hpp"

namespace s3d
{
	class detail::P2WorldDetail
	{
	public:

		explicit P2WorldDetail(Vec2 gravity);

		void update(double timeStep, int32 velocityIterations, int32 positionIterations);

		[[nodiscard]]
		P2Body createPlaceholder(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos);

		[[nodiscard]]
		P2Body createLine(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, OneSided oneSided, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createLineSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2Body createLineString(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createLineStringSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2Body createClosedLineString(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createClosedLineStringSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2Body createCircle(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createCircleSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2Body createRect(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createRectSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2Body createTriangle(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createTriangleSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2Body createQuad(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createQuadSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2Body createPolygon(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Material& material, const P2Filter& filter);

		[[nodiscard]]
		P2Body createPolygonSensor(const std::shared_ptr<P2WorldDetail>& world, P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Filter& filter);

		[[nodiscard]]
		P2PivotJoint createPivotJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, EnableCollision enableCollision);

		[[nodiscard]]
		P2DistanceJoint createDistanceJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, double length, EnableCollision enableCollision);

		[[nodiscard]]
		P2SliderJoint createSliderJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, EnableCollision enableCollision);

		[[nodiscard]]
		P2WheelJoint createWheelJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& axis, EnableCollision enableCollision);

		[[nodiscard]]
		P2MouseJoint createMouseJoint(const std::shared_ptr<P2WorldDetail>& world, const P2Body& body, const Vec2& worldTargetPos);

		[[nodiscard]]
		const HashTable<P2ContactPair, P2Collision>& getCollisions() const noexcept;

		[[nodiscard]]
		b2World& getData() noexcept;

		[[nodiscard]]
		const b2World& getData() const noexcept;

		[[nodiscard]]
		b2World* getWorldPtr() noexcept;

	private:

		b2World m_world;

		P2ContactListener m_contactListner;

		std::atomic<P2BodyID> m_currentID = { 0 };

		[[nodiscard]]
		P2BodyID generateNextID() noexcept;
	};
}
