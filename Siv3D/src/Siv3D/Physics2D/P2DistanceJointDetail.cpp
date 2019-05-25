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

# include "P2DistanceJointDetail.hpp"
# include "Physics2DUtility.hpp"

namespace s3d
{
	P2DistanceJoint::P2DistanceJointDetail::P2DistanceJointDetail(P2World& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double length)
		: m_world(world)
	{
		b2DistanceJointDef def;
		def.Initialize(bodyA.getBodyPtr(), bodyB.getBodyPtr(), detail::ToB2Vec2(anchorPosA), detail::ToB2Vec2(anchorPosB));
		m_joint = static_cast<b2DistanceJoint*>(world.getWorldPtr()->CreateJoint(&def));
		m_joint->SetLength(static_cast<float32>(length));
	}

	P2DistanceJoint::P2DistanceJointDetail::~P2DistanceJointDetail()
	{
		if (!m_joint)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyJoint(m_joint);
	}

	b2DistanceJoint& P2DistanceJoint::P2DistanceJointDetail::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2DistanceJoint& P2DistanceJoint::P2DistanceJointDetail::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}
}
