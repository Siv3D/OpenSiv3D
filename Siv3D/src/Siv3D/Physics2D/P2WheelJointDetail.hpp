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
	class P2WheelJoint::P2WheelJointDetail
	{
	private:

		b2WheelJoint* m_joint = nullptr;

		P2World m_world;

	public:

		P2WheelJointDetail(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchor, const Vec2& axis);

		~P2WheelJointDetail();

		[[nodiscard]] b2WheelJoint& getJoint();

		[[nodiscard]] const b2WheelJoint& getJoint() const;
	};
}
