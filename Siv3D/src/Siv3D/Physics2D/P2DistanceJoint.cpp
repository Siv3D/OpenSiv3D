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
# include <Siv3D/Physics2D/P2DistanceJoint.hpp>
# include "P2Common.hpp"
# include "P2DistanceJointDetail.hpp"

namespace s3d
{
	P2DistanceJoint::P2DistanceJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const Vec2& worldAnchorPosA, const P2Body& bodyB, const Vec2& worldAnchorPosB, const double length, const EnableCollision enableCollision)
		: pImpl{ std::make_shared<detail::P2DistanceJointDetail>(world, bodyA, worldAnchorPosA, bodyB, worldAnchorPosB, length, enableCollision) } {}

	void P2DistanceJoint::release()
	{
		pImpl.reset();
	}

	Vec2 P2DistanceJoint::getAnchorPosA() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorA());
	}

	Vec2 P2DistanceJoint::getAnchorPosB() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	Vec2 P2DistanceJoint::getReactionForce(const double timeStep) const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float>(1.0 / timeStep)));
	}

	double P2DistanceJoint::getReactionTorque(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float>(1.0 / timeStep));
	}

	P2DistanceJoint& P2DistanceJoint::setRestLength(const double length)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetLength(static_cast<float>(length));
		return *this;
	}

	double P2DistanceJoint::getRestLength() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetLength();
	}

	P2DistanceJoint& P2DistanceJoint::setMinLength(const double length)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMinLength(static_cast<float>(length));
		return *this;
	}

	double P2DistanceJoint::getMinLength() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMinLength();
	}

	P2DistanceJoint& P2DistanceJoint::setMaxLength(const double length)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxLength(static_cast<float>(length));
		return *this;
	}

	double P2DistanceJoint::getMaxLength() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxLength();
	}

	double P2DistanceJoint::getCurrentLength() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetCurrentLength();
	}

	P2DistanceJoint& P2DistanceJoint::setStiffness(const double stiffness)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetStiffness(static_cast<float>(stiffness));
		return *this;
	}

	double P2DistanceJoint::getStiffness() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetStiffness();
	}

	P2DistanceJoint& P2DistanceJoint::setDamping(const double damping)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetDamping(static_cast<float>(damping));
		return *this;
	}

	double P2DistanceJoint::getDamping() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetDamping();
	}

	P2DistanceJoint& P2DistanceJoint::setLinearStiffness(const double frequencyHz, const double dampingRatio)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->setLinearStiffness(frequencyHz, dampingRatio);
		return *this;
	}

	void P2DistanceJoint::draw(const ColorF& color) const
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
