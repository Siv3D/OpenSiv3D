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

# include "P2WheelJointDetail.hpp"
# include "Physics2DUtility.hpp"

namespace s3d
{
	P2WheelJoint::P2WheelJointDetail::P2WheelJointDetail(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchor, const Vec2& axis)
		: m_world(world)
	{
		b2WheelJointDef def;
		def.Initialize(bodyA.getBodyPtr(), bodyB.getBodyPtr(), detail::ToB2Vec2(anchor), detail::ToB2Vec2(axis));
		m_joint = static_cast<b2WheelJoint*>(world.getWorldPtr()->CreateJoint(&def));
	}

	P2WheelJoint::P2WheelJointDetail::~P2WheelJointDetail()
	{
		if (!m_joint)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyJoint(m_joint);
	}

	b2WheelJoint& P2WheelJoint::P2WheelJointDetail::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2WheelJoint& P2WheelJoint::P2WheelJointDetail::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}
}
