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

# pragma once
# include "../Common.hpp"
# include "../2DShapesFwd.hpp"
# include "../ColorHSV.hpp"
# include "P2Fwd.hpp"

namespace s3d
{
	class P2WheelJoint
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2WheelJoint() = default;

		[[nodiscard]]
		Vec2 getAnchorPosA() const;

		[[nodiscard]]
		Vec2 getAnchorPosB() const;

		[[nodiscard]]
		Vec2 getReactionForce(double inv_dt) const;

		[[nodiscard]]
		double getReactionTorque(double inv_dt) const;

		[[nodiscard]]
		double getJointTranslation() const;

		[[nodiscard]]
		double getJointLinearSpeed() const;

		[[nodiscard]]
		double getJointAngle() const;

		[[nodiscard]]
		double getJointAngularSpeed() const;

		P2WheelJoint& setMotorEnabled(bool enabled);

		[[nodiscard]]
		bool getMotorEnabled() const;

		P2WheelJoint& setMotorSpeed(double speed);

		[[nodiscard]]
		double getMotorSpeed() const;

		P2WheelJoint& setMaxMotorTorque(double torque);

		[[nodiscard]]
		double getMaxMotorTorque() const;

		[[nodiscard]]
		double getMotorTorque(double inv_dt) const;

		P2WheelJoint& setSpringFrequencyHz(double hz);

		[[nodiscard]]
		double getSpringFrequencyHz() const;

		P2WheelJoint& setSpringDampingRatio(double ratio);

		[[nodiscard]]
		double getSpringDampingRatio() const;

		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2WheelJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2WheelJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchor, const Vec2& axis);
	};
}
