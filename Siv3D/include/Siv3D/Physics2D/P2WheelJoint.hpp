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
	class P2WheelJoint
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2WheelJoint() = default;

		void release();

		[[nodiscard]]
		Vec2 getAnchorPosA() const;

		[[nodiscard]]
		Vec2 getAnchorPosB() const;

		[[nodiscard]]
		Vec2 getReactionForce(double timeStep) const;

		[[nodiscard]]
		double getReactionTorque(double timeStep) const;

		[[nodiscard]]
		double getJointTranslation() const;

		[[nodiscard]]
		double getJointLinearSpeed() const;

		[[nodiscard]]
		double getJointAngle() const;

		[[nodiscard]]
		double getJointAngularSpeed() const;

		P2WheelJoint& setLimitsEnabled(bool enabled);

		bool getLimitsEnabled() const;

		P2WheelJoint& setLimits(double lower, double upper);

		[[nodiscard]]
		std::pair<double, double> getLimits() const;

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
		double getMotorTorque(double timeStep) const;

		P2WheelJoint& setStiffness(double stiffness);

		[[nodiscard]]
		double getStiffness() const;

		P2WheelJoint& setDamping(double damping);

		[[nodiscard]]
		double getDamping() const;

		P2WheelJoint& setLinearStiffness(double frequencyHz, double dampingRatio);

		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2WheelJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2WheelJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& axis, EnableCollision enableCollision);
	};
}
