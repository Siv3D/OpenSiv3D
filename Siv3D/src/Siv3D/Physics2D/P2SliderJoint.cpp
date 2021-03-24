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
# include <Siv3D/Physics2D/P2SliderJoint.hpp>
# include "P2Common.hpp"
# include "P2SliderJointDetail.hpp"

namespace s3d
{
	P2SliderJoint::P2SliderJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const P2Body& bodyB, const Vec2& anchorPos, const Vec2& normalizedAxis)
		: pImpl{ std::make_shared<detail::P2SliderJointDetail>(world, bodyA, bodyB, anchorPos, normalizedAxis) } {}
}
