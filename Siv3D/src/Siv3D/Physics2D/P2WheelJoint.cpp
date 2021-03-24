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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Physics2D/P2WheelJoint.hpp>
# include "P2Common.hpp"
# include "P2WheelJointDetail.hpp"

namespace s3d
{
	P2WheelJoint::P2WheelJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchor, const Vec2& axis)
		: pImpl{ std::make_shared<detail::P2WheelJointDetail>(world, bodyA, bodyB, anchor, axis) } {}
}
