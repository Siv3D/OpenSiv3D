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

# include "P2RopeJointDetail.hpp"
# include "Physics2DUtility.hpp"

namespace s3d
{
	P2RopeJoint::P2RopeJointDetail::P2RopeJointDetail(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double maxLength)
		: m_world(world)
	{
		b2RopeJointDef def;
		def.bodyA = bodyA.getBodyPtr();
		def.bodyB = bodyB.getBodyPtr();
		def.localAnchorA = bodyA.getBodyPtr()->GetLocalPoint(detail::ToB2Vec2(anchorPosA));
		def.localAnchorB = bodyB.getBodyPtr()->GetLocalPoint(detail::ToB2Vec2(anchorPosB));
		def.maxLength = static_cast<float32>(maxLength);
		m_joint = static_cast<b2RopeJoint*>(world.getWorldPtr()->CreateJoint(&def));
	}

	P2RopeJoint::P2RopeJointDetail::~P2RopeJointDetail()
	{
		if (!m_joint)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyJoint(m_joint);
	}

	b2RopeJoint& P2RopeJoint::P2RopeJointDetail::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2RopeJoint& P2RopeJoint::P2RopeJointDetail::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}
}
