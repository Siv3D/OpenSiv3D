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
# include <Siv3D/Physics2D/P2MouseJoint.hpp>
# include "P2Common.hpp"

namespace s3d
{
	class detail::P2MouseJointDetail
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2MouseJointDetail(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& body, const Vec2& worldTargetPos);

		~P2MouseJointDetail();

		[[nodiscard]]
		b2MouseJoint& getJoint();

		[[nodiscard]]
		const b2MouseJoint& getJoint() const;

		void setLinearStiffness(double frequencyHz, double dampingRatio) noexcept;

	private:

		b2MouseJoint* m_joint = nullptr;

		std::shared_ptr<detail::P2WorldDetail> m_world;

		std::weak_ptr<P2Body::P2BodyDetail> m_body;

		b2Body* m_placeholderBody = nullptr;
	};
}
