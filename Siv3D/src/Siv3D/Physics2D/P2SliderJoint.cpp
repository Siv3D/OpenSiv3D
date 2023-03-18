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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Physics2D/P2SliderJoint.hpp>
# include "P2Common.hpp"
# include "P2SliderJointDetail.hpp"

namespace s3d
{
	P2SliderJoint::P2SliderJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, const EnableCollision enableCollision)
		: pImpl{ std::make_shared<detail::P2SliderJointDetail>(world, bodyA, bodyB, worldAnchorPos, normalizedAxis, enableCollision) } {}

	void P2SliderJoint::release()
	{
		pImpl.reset();
	}

	Vec2 P2SliderJoint::getAnchorPosA() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	Vec2 P2SliderJoint::getAnchorPosB() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	double P2SliderJoint::getJointTranslation() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointTranslation();
	}

	double P2SliderJoint::getJointSpeed() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointSpeed();
	}

	P2SliderJoint& P2SliderJoint::setLimitEnabled(const bool enabled)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableLimit(enabled);
		return *this;
	}

	bool P2SliderJoint::getLimitEnabled() const
	{
		if (not pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsLimitEnabled();
	}

	P2SliderJoint& P2SliderJoint::setLimits(const double lower, const double upper)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetLimits(static_cast<float>(lower), static_cast<float>(upper));
		return *this;
	}

	std::pair<double, double> P2SliderJoint::getLimits() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return{ pImpl->getJoint().GetLowerLimit(), pImpl->getJoint().GetLowerLimit() };
	}

	P2SliderJoint& P2SliderJoint::setMotorEnabled(const bool enabled)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableMotor(enabled);
		return *this;
	}

	bool P2SliderJoint::getMotorEnabled() const
	{
		if (not pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsMotorEnabled();
	}

	P2SliderJoint& P2SliderJoint::setMotorSpeed(const double speed)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMotorSpeed(static_cast<float>(speed));
		return *this;
	}

	double P2SliderJoint::getMotorSpeed() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorSpeed();
	}

	P2SliderJoint& P2SliderJoint::setMaxMotorForce(const double force)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxMotorForce(static_cast<float>(force));
		return *this;
	}

	double P2SliderJoint::getMaxMotorForce() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxMotorForce();
	}

	double P2SliderJoint::getCurrentMotorForce(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorForce(static_cast<float>(1.0 / timeStep));
	}

	Vec2 P2SliderJoint::getReactionForce(const double timeStep) const
	{
		if (not pImpl)
		{
			return Vec2::Zero();
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float>(1.0 / timeStep)));
	}

	double P2SliderJoint::getReactionTorque(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float>(1.0 / timeStep));
	}

	void P2SliderJoint::draw(const ColorF& color) const
	{
		if (not pImpl)
		{
			return;
		}

		const Vec2 anchorPosA = detail::ToVec2(pImpl->getJoint().GetAnchorA());
		const Vec2 anchorPosB = detail::ToVec2(pImpl->getJoint().GetAnchorB());

		const double scale = (1.0 / Graphics2D::GetMaxScaling());
		const double r = (detail::P2AnchorR * scale);
		Circle{ anchorPosA, r }.draw(color);
		Circle{ anchorPosB, r }.draw(color);
		Line{ anchorPosA, anchorPosB }.draw((detail::P2LineThickness * scale), color);
	}
}
