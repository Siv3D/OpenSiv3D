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
# include "P2DistanceJointDetail.hpp"
# include "P2WorldDetail.hpp"
# include "P2BodyDetail.hpp"

namespace s3d
{
	detail::P2DistanceJointDetail::P2DistanceJointDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, const double length, const EnableCollision enableCollision)
		: m_world{ world }
		, m_bodyA{ bodyA.getWeakPtr() }
		, m_bodyB{ bodyB.getWeakPtr() }
	{
		b2DistanceJointDef def;
		def.Initialize(m_bodyA.lock()->getBodyPtr(), m_bodyB.lock()->getBodyPtr(), detail::ToB2Vec2(worldAnchorPosA), detail::ToB2Vec2(worldAnchorPosB));
		def.collideConnected = enableCollision.getBool();
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

	b2DistanceJoint& detail::P2DistanceJointDetail::getJoint() noexcept
	{
		assert(m_joint);

		return *m_joint;
	}

	const b2DistanceJoint& detail::P2DistanceJointDetail::getJoint() const noexcept
	{
		assert(m_joint);

		return *m_joint;
	}

	void detail::P2DistanceJointDetail::setLinearStiffness(const double frequencyHz, const double dampingRatio) noexcept
	{
		assert(m_joint);

		auto pA = m_bodyA.lock();
		auto pB = m_bodyB.lock();

		if (not pA || not pB)
		{
			return;
		}

		float stiffness, damping;
		b2LinearStiffness(stiffness, damping, static_cast<float>(frequencyHz), static_cast<float>(dampingRatio),
			pA->getBodyPtr(), pB->getBodyPtr());

		m_joint->SetStiffness(stiffness);
		m_joint->SetDamping(damping);
	}
}
