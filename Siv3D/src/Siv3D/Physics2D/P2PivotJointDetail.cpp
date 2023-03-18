//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Physics2D/P2Body.hpp>
# include "P2PivotJointDetail.hpp"
# include "P2WorldDetail.hpp"
# include "P2BodyDetail.hpp"

namespace s3d
{
	detail::P2PivotJointDetail::P2PivotJointDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const EnableCollision enableCollision)
		: m_world{ world }
		, m_bodyA{ bodyA.getWeakPtr() }
		, m_bodyB{ bodyB.getWeakPtr() }
	{
		b2RevoluteJointDef def;
		def.Initialize(m_bodyA.lock()->getBodyPtr(), m_bodyB.lock()->getBodyPtr(), detail::ToB2Vec2(worldAnchorPos));
		def.collideConnected = enableCollision.getBool();
		m_joint = static_cast<b2RevoluteJoint*>(m_world->getWorldPtr()->CreateJoint(&def));
	}

	detail::P2PivotJointDetail::~P2PivotJointDetail()
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

	b2RevoluteJoint& detail::P2PivotJointDetail::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2RevoluteJoint& detail::P2PivotJointDetail::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}
}
