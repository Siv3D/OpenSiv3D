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

# include <Siv3D/Physics2D/P2Body.hpp>
# include "P2WheelJointDetail.hpp"
# include "P2WorldDetail.hpp"
# include "P2BodyDetail.hpp"

namespace s3d
{
	detail::P2WheelJointDetail::P2WheelJointDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchor, const Vec2& axis)
		: m_world{ world }
		, m_bodyA{ bodyA.getWeakPtr() }
		, m_bodyB{ bodyB.getWeakPtr() }
	{
		b2WheelJointDef def;
		def.Initialize(m_bodyA.lock()->getBodyPtr(), m_bodyB.lock()->getBodyPtr(), detail::ToB2Vec2(anchor), detail::ToB2Vec2(axis));
		m_joint = static_cast<b2WheelJoint*>(m_world->getWorldPtr()->CreateJoint(&def));
	}

	detail::P2WheelJointDetail::~P2WheelJointDetail()
	{
		if (not m_joint)
		{
			return;
		}

		if (m_bodyA.expired() || m_bodyB.expired())
		{
			return;
		}

		m_world->getWorldPtr()->DestroyJoint(m_joint);
	}
}
