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
	class P2DistanceJoint
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2DistanceJoint() = default;

		void release();

		[[nodiscard]]
		Vec2 getAnchorPosA() const;

		[[nodiscard]]
		Vec2 getAnchorPosB() const;

		[[nodiscard]]
		Vec2 getReactionForce(double timeStep) const;

		[[nodiscard]]
		double getReactionTorque(double timeStep) const;

		P2DistanceJoint& setRestLength(double length);

		[[nodiscard]]
		double getRestLength() const;

		P2DistanceJoint& setMinLength(double length);

		[[nodiscard]]
		double getMinLength() const;

		P2DistanceJoint& setMaxLength(double length);

		[[nodiscard]]
		double getMaxLength() const;

		[[nodiscard]]
		double getCurrentLength() const;

		P2DistanceJoint& setStiffness(double stiffness);

		[[nodiscard]]
		double getStiffness() const;

		P2DistanceJoint& setDamping(double damping);

		[[nodiscard]]
		double getDamping() const;

		P2DistanceJoint& setLinearStiffness(double frequencyHz, double dampingRatio);

		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2DistanceJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2DistanceJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, double length, EnableCollision enableCollision);
	};
}
