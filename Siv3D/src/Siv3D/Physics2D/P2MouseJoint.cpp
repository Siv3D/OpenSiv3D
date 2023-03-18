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
# include <Siv3D/Physics2D/P2MouseJoint.hpp>
# include "P2Common.hpp"
# include "P2MouseJointDetail.hpp"

namespace s3d
{
	P2MouseJoint::P2MouseJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& body, const Vec2& worldTargetPos)
		: pImpl(std::make_shared<detail::P2MouseJointDetail>(world, body, worldTargetPos)) {}

	void P2MouseJoint::release()
	{
		pImpl.reset();
	}

	Vec2 P2MouseJoint::getAnchorPos() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetAnchorB());
	}

	Vec2 P2MouseJoint::getReactionForce(const double timeStep) const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetReactionForce(static_cast<float>(1.0 / timeStep)));
	}

	double P2MouseJoint::getReactionTorque(const double timeStep) const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetReactionTorque(static_cast<float>(1.0 / timeStep));
	}

	P2MouseJoint& P2MouseJoint::setTargetPos(const Vec2& pos)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetTarget(detail::ToB2Vec2(pos));
		return *this;
	}

	Vec2 P2MouseJoint::getTargetPos() const
	{
		if (not pImpl)
		{
			return{ 0.0, 0.0 };
		}

		return detail::ToVec2(pImpl->getJoint().GetTarget());
	}

	P2MouseJoint& P2MouseJoint::setMaxForce(const double force)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetMaxForce(static_cast<float>(force));
		return *this;
	}

	double P2MouseJoint::getMaxForce() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetMaxForce();
	}

	P2MouseJoint& P2MouseJoint::setStiffness(const double stiffness)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetStiffness(static_cast<float>(stiffness));
		return *this;
	}

	double P2MouseJoint::getStiffness() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetStiffness();
	}

	P2MouseJoint& P2MouseJoint::setDamping(const double damping)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->getJoint().SetDamping(static_cast<float>(damping));
		return *this;
	}

	double P2MouseJoint::getDamping() const
	{
		if (not pImpl)
		{
			return 0.0;
		}

		return pImpl->getJoint().GetDamping();
	}

	P2MouseJoint& P2MouseJoint::setLinearStiffness(const double frequencyHz, const double dampingRatio)
	{
		if (not pImpl)
		{
			return *this;
		}

		pImpl->setLinearStiffness(frequencyHz, dampingRatio);
		return *this;
	}

	void P2MouseJoint::draw(const ColorF& color) const
	{
		if (not pImpl)
		{
			return;
		}

		const Vec2 anchorPos = detail::ToVec2(pImpl->getJoint().GetAnchorB());
		const Vec2 targetPos = detail::ToVec2(pImpl->getJoint().GetTarget());
		const double scale = (1.0 / Graphics2D::GetMaxScaling());
		const double r = (detail::P2AnchorR * scale);
		Circle{ anchorPos, r }.draw(color);
		Circle{ targetPos, r }.draw(color);
		Line{ anchorPos, targetPos }.draw(detail::P2LineThickness * scale, color);
	}
}
