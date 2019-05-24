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
	class P2SliderJoint::P2SliderJointDetail
	{
	private:

		b2PrismaticJoint* m_joint = nullptr;

		P2World m_world;

	public:

		P2SliderJointDetail(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis);

		~P2SliderJointDetail();

		[[nodiscard]] b2PrismaticJoint& getJoint();

		[[nodiscard]] const b2PrismaticJoint& getJoint() const;
	};
}
