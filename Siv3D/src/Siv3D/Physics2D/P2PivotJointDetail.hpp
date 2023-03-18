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

# pragma once
# include <Siv3D/Physics2D/P2Body.hpp>
# include <Siv3D/Physics2D/P2PivotJoint.hpp>
# include "P2Common.hpp"

namespace s3d
{
	class detail::P2PivotJointDetail
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2PivotJointDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, EnableCollision enableCollision);

		~P2PivotJointDetail();

		[[nodiscard]]
		b2RevoluteJoint& getJoint();

		[[nodiscard]]
		const b2RevoluteJoint& getJoint() const;

	private:

		b2RevoluteJoint* m_joint = nullptr;

		std::shared_ptr<detail::P2WorldDetail> m_world;

		std::weak_ptr<P2Body::P2BodyDetail> m_bodyA;

		std::weak_ptr<P2Body::P2BodyDetail> m_bodyB;
	};
}
