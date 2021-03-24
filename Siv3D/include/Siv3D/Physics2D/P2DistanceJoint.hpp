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
	class P2DistanceJoint
	{
	public:

		SIV3D_NODISCARD_CXX20
		P2DistanceJoint() = default;

		[[nodiscard]]
		Vec2 getAnchorPosA() const;

		[[nodiscard]]
		Vec2 getAnchorPosB() const;

		[[nodiscard]]
		Vec2 getReactionForce(double inv_dt) const;

		[[nodiscard]]
		double getReactionTorque(double inv_dt) const;

		P2DistanceJoint& setLength(double length);

		[[nodiscard]]
		double getLength() const;

		P2DistanceJoint& setFrequencyHz(double hz);

		[[nodiscard]]
		double getFrequencyHz() const;

		P2DistanceJoint& setDampingRatio(double ratio);

		[[nodiscard]]
		double getDampingRatio() const;

		void draw(const ColorF& color = Palette::White) const;

	private:

		std::shared_ptr<detail::P2DistanceJointDetail> pImpl;

		friend class detail::P2WorldDetail;

		SIV3D_NODISCARD_CXX20
		P2DistanceJoint(const std::shared_ptr<detail::P2WorldDetail>& world, const P2Body& bodyA, const Vec2& anchorPosA, const P2Body& bodyB, const Vec2& anchorPosB, double length);
	};
}
