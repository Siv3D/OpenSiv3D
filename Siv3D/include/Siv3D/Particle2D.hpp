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
# include "Emission2D.hpp"

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

		SIV3D_NODISCARD_CXX20
		Particle2D() = default;

		SIV3D_NODISCARD_CXX20
		Particle2D(const Emission2D& emission, const Float4& _startColor,
			float _startSize, float _rotation, float _startAngularVelocity,
			float _startLifeTime, float _remainingLifeTime) noexcept;

		void update(float deltaTime, const Float2& deltaVelocity) noexcept;

		void advance(float deltaTime, const Float2& deltaVelocity) noexcept;

		[[nodiscard]]
		bool isDead() const noexcept;
	};
}
