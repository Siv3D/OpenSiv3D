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

# include "P2SliderJointDetail.hpp"
# include "Physics2DUtility.hpp"

namespace s3d
{
	P2SliderJoint::P2SliderJointDetail::P2SliderJointDetail(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis)
		: m_world(world)
	{
		b2PrismaticJointDef def;
		def.Initialize(bodyA.getBodyPtr(), bodyB.getBodyPtr(), detail::ToB2Vec2(anchorPos), detail::ToB2Vec2(normalizedAxis));
		m_joint = static_cast<b2PrismaticJoint*>(world.getWorldPtr()->CreateJoint(&def));
	}

	P2SliderJoint::P2SliderJointDetail::~P2SliderJointDetail()
	{
		if (!m_joint)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyJoint(m_joint);
	}

	b2PrismaticJoint& P2SliderJoint::P2SliderJointDetail::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2PrismaticJoint& P2SliderJoint::P2SliderJointDetail::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}
}
