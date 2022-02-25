//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "../Common.hpp"
# include "../2DShapesFwd.hpp"
# include "../ColorHSV.hpp"
# include "P2Fwd.hpp"

namespace s3d
{
	class P2MouseJoint
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2MouseJoint() = default;

		void release();

		[[nodiscard]]
		Vec2 getAnchorPos() const;

		[[nodiscard]]
		Vec2 getReactionForce(double timeStep) const;

		[[nodiscard]]
		double getReactionTorque(double timeStep) const;

		P2MouseJoint& setTargetPos(const Vec2& pos);

		[[nodiscard]]
		Vec2 getTargetPos() const;

		P2MouseJoint& setMaxForce(double force);

		[[nodiscard]]
		double getMaxForce() const;

		P2MouseJoint& setStiffness(double stiffness);

		[[nodiscard]]
		double getStiffness() const;

		P2MouseJoint& setDamping(double damping);

		[[nodiscard]]
		double getDamping() const;

		P2MouseJoint& setLinearStiffness(double frequencyHz, double dampingRatio);

		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2MouseJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2MouseJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& body, const Vec2& worldTargetPos);
	};
}
