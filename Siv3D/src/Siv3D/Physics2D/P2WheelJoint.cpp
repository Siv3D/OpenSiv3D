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
# include <Siv3D/Physics2D/P2WheelJoint.hpp>
# include "P2Common.hpp"
# include "P2WheelJointDetail.hpp"

namespace s3d
{
	P2WheelJoint::P2WheelJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const Vec2& normalizedAxis, const EnableCollision enableCollision)
		: pImpl{ std::make_shared<detail::P2WheelJointDetail>(world, bodyA, bodyB, worldAnchorPos, normalizedAxis, enableCollision) } {}

	void P2WheelJoint::release()
	{
		pImpl.reset();
	}

	Vec2 P2WheelJoint::getAnchorPosA() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	Vec2 P2WheelJoint::getAnchorPosB() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	Vec2 P2WheelJoint::getReactionForce(const double timeStep) const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float>(1.0 / timeStep)));
	}

	double P2WheelJoint::getReactionTorque(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float>(1.0 / timeStep));
	}

	double P2WheelJoint::getJointTranslation() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointTranslation();
	}

	double P2WheelJoint::getJointLinearSpeed() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointLinearSpeed();
	}

	double P2WheelJoint::getJointAngle() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointAngle();
	}

	double P2WheelJoint::getJointAngularSpeed() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointAngularSpeed();
	}

	P2WheelJoint& P2WheelJoint::setLimitsEnabled(const bool enabled)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableLimit(enabled);
		return *this;
	}

	bool P2WheelJoint::getLimitsEnabled() const
	{
		if (not pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsLimitEnabled();
	}

	P2WheelJoint& P2WheelJoint::setLimits(const double lower, const double upper)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetLimits(static_cast<float>(lower), static_cast<float>(upper));
		return *this;
	}

	std::pair<double, double> P2WheelJoint::getLimits() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return{ pImpl->getJoint().GetLowerLimit(), pImpl->getJoint().GetLowerLimit() };
	}

	P2WheelJoint& P2WheelJoint::setMotorEnabled(const bool enabled)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableMotor(enabled);
		return *this;
	}

	bool P2WheelJoint::getMotorEnabled() const
	{
		if (not pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsMotorEnabled();
	}

	P2WheelJoint& P2WheelJoint::setMotorSpeed(const double speed)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMotorSpeed(static_cast<float>(speed));
		return *this;
	}

	double P2WheelJoint::getMotorSpeed() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorSpeed();
	}

	P2WheelJoint& P2WheelJoint::setMaxMotorTorque(const double torque)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxMotorTorque(static_cast<float>(torque));
		return *this;
	}

	double P2WheelJoint::getMaxMotorTorque() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxMotorTorque();
	}

	double P2WheelJoint::getMotorTorque(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorTorque(static_cast<float>(1.0 / timeStep));
	}

	P2WheelJoint& P2WheelJoint::setStiffness(const double stiffness)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetStiffness(static_cast<float>(stiffness));
		return *this;
	}

	double P2WheelJoint::getStiffness() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetStiffness();
	}

	P2WheelJoint& P2WheelJoint::setDamping(const double damping)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetDamping(static_cast<float>(damping));
		return *this;
	}

	double P2WheelJoint::getDamping() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetDamping();
	}

	P2WheelJoint& P2WheelJoint::setLinearStiffness(const double frequencyHz, const double dampingRatio)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->setLinearStiffness(frequencyHz, dampingRatio);
		return *this;
	}

	void P2WheelJoint::draw(const ColorF& color) const
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
		Line{ anchorPosA, anchorPosB }.draw(detail::P2LineThickness * scale, color);
	}
}
