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
# include <Siv3D/Physics2D/P2PivotJoint.hpp>
# include "P2Common.hpp"
# include "P2PivotJointDetail.hpp"

namespace s3d
{
	P2PivotJoint::P2PivotJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& worldAnchorPos, const EnableCollision enableCollision)
		: pImpl(std::make_shared<detail::P2PivotJointDetail>(world, bodyA, bodyB, worldAnchorPos, enableCollision)) {}

	void P2PivotJoint::release()
	{
		pImpl.reset();
	}

	Vec2 P2PivotJoint::getAnchorPos() const
	{
		if (not pImpl)
		{
			return{ 0, 0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	double P2PivotJoint::getJointAngle() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointAngle();
	}

	double P2PivotJoint::getJointAngleSpeed() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetJointSpeed();
	}

	P2PivotJoint& P2PivotJoint::setLimitsEnabled(const bool enabled)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableLimit(enabled);
		return *this;
	}

	bool P2PivotJoint::getLimitsEnabled() const
	{
		if (not pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsLimitEnabled();
	}

	P2PivotJoint& P2PivotJoint::setLimits(const double lower, const double upper)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetLimits(static_cast<float>(lower), static_cast<float>(upper));
		return *this;
	}

	std::pair<double, double> P2PivotJoint::getLimits() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return{ pImpl->getJoint().GetLowerLimit(), pImpl->getJoint().GetLowerLimit() };
	}

	P2PivotJoint& P2PivotJoint::setMotorEnabled(const bool enabled)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().EnableMotor(enabled);
		return *this;
	}

	bool P2PivotJoint::getMotorEnabled() const
	{
		if (not pImpl)
		{
			return false;
		}

		return pImpl->getJoint().IsMotorEnabled();
	}

	P2PivotJoint& P2PivotJoint::setMotorSpeed(const double speed)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMotorSpeed(static_cast<float>(speed));
		return *this;
	}

	double P2PivotJoint::getMotorSpeed() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorSpeed();
	}

	P2PivotJoint& P2PivotJoint::setMaxMotorTorque(const double torque)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxMotorTorque(static_cast<float>(torque));
		return *this;
	}

	double P2PivotJoint::getMaxMotorTorque() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxMotorTorque();
	}

	Vec2 P2PivotJoint::getReactionForce(const double timeStep) const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float>(1.0 / timeStep)));
	}

	double P2PivotJoint::getReactionTorque(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float>(1.0 / timeStep));
	}

	double P2PivotJoint::getMotorTorque(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMotorTorque(static_cast<float>(1.0 / timeStep));
	}

	void P2PivotJoint::draw(const ColorF& color) const
	{
		if (not pImpl)
		{
			return;
		}

		const Vec2 anchorPos = detail::ToVec2(pImpl->getJoint().GetAnchorA());
		Circle{ anchorPos, detail::AdjustThickness(detail::P2AnchorR) }.draw(color);
	}
}
