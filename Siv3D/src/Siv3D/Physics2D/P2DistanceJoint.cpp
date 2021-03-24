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
# include <Siv3D/Physics2D/P2DistanceJoint.hpp>
# include "P2Common.hpp"
# include "P2DistanceJointDetail.hpp"

namespace s3d
{
	P2DistanceJoint::P2DistanceJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, const double length)
		: pImpl{ std::make_shared<detail::P2DistanceJointDetail>(world, bodyA, anchorPosA, bodyB, anchorPosB, length) } {}
}
