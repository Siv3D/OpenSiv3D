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
	class P2SliderJoint
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2SliderJoint() = default;

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
		double getJointSpeed() const;

		P2SliderJoint& setLimitEnabled(bool enabled);

		[[nodiscard]]
		bool getLimitEnabled() const;

		P2SliderJoint& setLimits(double lower, double upper);

		[[nodiscard]]
		std::pair<double, double> getLimits() const;

		P2SliderJoint& setMotorEnabled(bool enabled);

		[[nodiscard]]
		bool getMotorEnabled() const;

		P2SliderJoint& setMotorSpeed(double speed);

		[[nodiscard]]
		double getMotorSpeed() const;

		P2SliderJoint& setMaxMotorForce(double force);

		[[nodiscard]]
		double getMaxMotorForce() const;

		[[nodiscard]]
		double getMotorForce(double inv_dt) const;

		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2SliderJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2SliderJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis);
	};
}
