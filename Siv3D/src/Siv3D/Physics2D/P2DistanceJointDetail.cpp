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
# include "P2DistanceJointDetail.hpp"
# include "P2WorldDetail.hpp"
# include "P2BodyDetail.hpp"

namespace s3d
{
	detail::P2DistanceJointDetail::P2DistanceJointDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double length)
		: m_world{ world }
		, m_bodyA{ bodyA.getWeakPtr() }
		, m_bodyB{ bodyB.getWeakPtr() }
	{
		b2DistanceJointDef def;
		def.Initialize(m_bodyA.lock()->getBodyPtr(), m_bodyB.lock()->getBodyPtr(), detail::ToB2Vec2(anchorPosA), detail::ToB2Vec2(anchorPosB));
		m_joint = static_cast<b2DistanceJoint*>(m_world->getWorldPtr()->CreateJoint(&def));
		m_joint->SetLength(static_cast<float>(length));
	}

	detail::P2DistanceJointDetail::~P2DistanceJointDetail()
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
