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
# include "P2MouseJointDetail.hpp"
# include "P2WorldDetail.hpp"
# include "P2BodyDetail.hpp"

namespace s3d
{
	detail::P2MouseJointDetail::P2MouseJointDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& body, const Vec2& worldTargetPos)
		: m_world{ world }
		, m_body{ body.getWeakPtr() }
	{
		{
			b2BodyDef bodyDef;
			m_placeholderBody = m_world->getWorldPtr()->CreateBody(&bodyDef);
		}

		b2MouseJointDef def;
		def.bodyA		= m_placeholderBody;
		def.bodyB		= m_body.lock()->getBodyPtr();
		def.target		= detail::ToB2Vec2(worldTargetPos);
		m_joint = static_cast<b2MouseJoint*>(m_world->getWorldPtr()->CreateJoint(&def));
	}

	detail::P2MouseJointDetail::~P2MouseJointDetail()
	{
		if (not m_joint)
		{
			return;
		}

		if (m_body.expired())
		{
			return;
		}

		m_world->getWorldPtr()->DestroyJoint(m_joint);

		if (m_placeholderBody)
		{
			m_world->getWorldPtr()->DestroyBody(m_placeholderBody);
			m_placeholderBody = nullptr;
		}
	}

	b2MouseJoint& detail::P2MouseJointDetail::getJoint()
	{
		assert(m_joint);

		return *m_joint;
	}

	[[nodiscard]]
	const b2MouseJoint& detail::P2MouseJointDetail::getJoint() const
	{
		assert(m_joint);

		return *m_joint;
	}

	void detail::P2MouseJointDetail::setLinearStiffness(const double frequencyHz, const double dampingRatio) noexcept
	{
		assert(m_joint);

		auto pA = m_placeholderBody;
		auto pB = m_body.lock();

		if (not pA || not pB)
		{
			return;
		}

		float stiffness, damping;
		b2LinearStiffness(stiffness, damping, static_cast<float>(frequencyHz), static_cast<float>(dampingRatio),
			pA, pB->getBodyPtr());

		m_joint->SetStiffness(stiffness);
		m_joint->SetDamping(damping);
	}
}
