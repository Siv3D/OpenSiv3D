//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct Particle2D
	{
		Float2 position;
		Float2 velocity;
		Float4 startColor;
		float startSize;
		float rotation;
		float startAngularVelocity;
		float startLifeTime;
		float remainingLifeTime;

		Particle2D() = default;

		Particle2D(const Emission2D& emission, const Float4& _startColor,
			float _startSize, float _rotation, float _startAngularVelocity,
			float _startLifeTime, float _remainingLifeTime) noexcept;

		void update(const float deltaTime, const Float2& deltaVelocity) noexcept;

		void advance(const float deltaTime, const Float2& deltaVelocity) noexcept;

		bool isDead() const noexcept;
	};
}
