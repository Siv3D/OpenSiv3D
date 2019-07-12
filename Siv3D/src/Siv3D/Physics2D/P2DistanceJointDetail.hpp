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
# include <Siv3D/Physics2D.hpp>
# include <Box2D/Box2D.h>

namespace s3d
{
	class P2DistanceJoint::P2DistanceJointDetail
	{
	private:

		b2DistanceJoint* m_joint = nullptr;

		P2World m_world;

	public:

		P2DistanceJointDetail(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double length);

		~P2DistanceJointDetail();

		[[nodiscard]] b2DistanceJoint& getJoint();

		[[nodiscard]] const b2DistanceJoint& getJoint() const;
	};
}
