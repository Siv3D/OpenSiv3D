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
	class P2PivotJoint
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2PivotJoint() = default;

		void release();

		[[nodiscard]]
		Vec2 getAnchorPos() const;

		[[nodiscard]]
		double getJointAngle() const;

		[[nodiscard]]
		double getJointAngleSpeed() const;

		P2PivotJoint& setLimitsEnabled(bool enabled);

		[[nodiscard]]
		bool getLimitsEnabled() const;

		P2PivotJoint& setLimits(double lower, double upper);

		[[nodiscard]]
		std::pair<double, double> getLimits() const;

		P2PivotJoint& setMotorEnabled(bool enabled);

		[[nodiscard]]
		bool getMotorEnabled() const;

		P2PivotJoint& setMotorSpeed(double speed);

		[[nodiscard]]
		double getMotorSpeed() const;

		P2PivotJoint& setMaxMotorTorque(double torque);

		[[nodiscard]]
		double getMaxMotorTorque() const;

		[[nodiscard]]
		Vec2 getReactionForce(double timeStep) const;

		[[nodiscard]]
		double getReactionTorque(double timeStep) const;

		[[nodiscard]]
		double getMotorTorque(double timeStep) const;

		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2PivotJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2PivotJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, EnableCollision enableCollision);
	};
}
