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
	class P2PivotJoint::P2PivotJointDetail
	{
	private:

		b2RevoluteJoint* m_joint = nullptr;

		P2World m_world;

	public:

		P2PivotJointDetail(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos);

		~P2PivotJointDetail();

		[[nodiscard]] b2RevoluteJoint& getJoint();

		[[nodiscard]] const b2RevoluteJoint& getJoint() const;
	};
}
