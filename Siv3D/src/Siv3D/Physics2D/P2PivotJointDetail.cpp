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

# include "P2PivotJointDetail.hpp"
# include "Physics2DUtility.hpp"

namespace s3d
{
	P2PivotJoint::P2PivotJointDetail::P2PivotJointDetail(P2World& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos)
		: m_world(world)
	{
		b2RevoluteJointDef def;
		def.Initialize(bodyA.getBodyPtr(), bodyB.getBodyPtr(), detail::ToB2Vec2(anchorPos));
		m_joint = static_cast<b2RevoluteJoint*>(world.getWorldPtr()->CreateJoint(&def));
	}

	P2PivotJoint::P2PivotJointDetail::~P2PivotJointDetail()
	{
		if (!m_joint)
		{
			return;
		}

		m_world.getWorldPtr()->DestroyJoint(m_joint);
	}

	b2RevoluteJoint& P2PivotJoint::P2PivotJointDetail::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2RevoluteJoint& P2PivotJoint::P2PivotJointDetail::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}
}
