//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "BlendState.hpp"

namespace s3d
{
	struct ParticleSystem2DParameters
	{
		using SizeOverLifeTimeFunc = std::function<float(float startSize, float startLifeTime, float remainingLifeTime)>;
		using ColorOverLifeTimeFunc = std::function<Float4(const Float4& startColor, float startLifeTime, float remainingLifeTime)>;

		double rate = 50;

		double maxParticles = 1000;

		double startLifeTime = 1.0;

		double startSpeed = 100.0;

		ColorF startColor = ColorF{ 1.0 };

		double startSize = 10.0;

		double startRotationDeg = 0.0;

		double randomStartRotationDeg = 0.0;

		double startAngularVelocityDeg = 0.0;

		double randomStartAngularVelocityDeg = 0.0;

		BlendState blendState = BlendState::Additive;

		SizeOverLifeTimeFunc sizeOverLifeTimeFunc;

		ColorOverLifeTimeFunc colorOverLifeTimeFunc;
	};
}

