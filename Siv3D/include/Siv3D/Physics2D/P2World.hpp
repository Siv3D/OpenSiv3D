//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "../Common.hpp"
# include "../PointVector.hpp"
# include "../HashTable.hpp"
# include "../Scene.hpp"
# include "P2Fwd.hpp"
# include "P2BodyType.hpp"
# include "P2Material.hpp"
# include "P2Filter.hpp"
# include "P2Body.hpp"
# include "P2PivotJoint.hpp"
# include "P2DistanceJoint.hpp"
# include "P2SliderJoint.hpp"
# include "P2WheelJoint.hpp"

namespace s3d
{
	class P2World
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit P2World(double gravity = 980);

		SIV3D_NODISCARD_CXX20
		explicit P2World(Vec2 gravity);

		void update(double timeStep = Scene::DeltaTime(), int32 velocityIterations = 6, int32 positionIterations = 2) const;

		void setSleepEnabled(bool enabled);

		[[nodiscard]]
		bool getSleepEnabled() const;

		void setGravity(double gravity);

		void setGravity(const Vec2& gravity);

		[[nodiscard]]
		Vec2 getGravity() const;

		void shiftOrigin(const Vec2& newOrigin);

		[[nodiscard]]
		P2Body createPlaceholder(P2BodyType bodyType, const Vec2& worldPos);

		[[nodiscard]]
		P2Body createLine(P2BodyType bodyType, const Vec2& worldPos, const Line& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createLineString(P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createClosedLineString(P2BodyType bodyType, const Vec2& worldPos, const LineString& localPos, OneSided oneSided = OneSided::No, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createCircle(P2BodyType bodyType, const Vec2& worldPos, double r, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createCircle(P2BodyType bodyType, const Vec2& worldPos, const Circle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, double size, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, const SizeF& size, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createRect(P2BodyType bodyType, const Vec2& worldPos, const RectF& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createTriangle(P2BodyType bodyType, const Vec2& worldPos, const Triangle& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createQuad(P2BodyType bodyType, const Vec2& worldPos, const Quad& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createPolygon(P2BodyType bodyType, const Vec2& worldPos, const Polygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2Body createPolygons(P2BodyType bodyType, const Vec2& worldPos, const MultiPolygon& localPos, const P2Material& material = {}, const P2Filter& filter = {});

		[[nodiscard]]
		P2PivotJoint createPivotJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos);
		
		[[nodiscard]]
		P2DistanceJoint createDistanceJoint(const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, double length);

		[[nodiscard]]
		P2SliderJoint createSliderJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis);

		[[nodiscard]]
		P2WheelJoint createWheelJoint(const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& axis);

		[[nodiscard]]
		const HashTable<P2ContactPair, P2Collision>& getCollisions() const noexcept;

	private:

		std::shared_ptr<detail::P2WorldDetail> pImpl;
	};
}
