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

# include <Siv3D/Particle2D.hpp>

namespace s3d
{
	Particle2D::Particle2D(const Emission2D& emission, const Float4& _startColor,
		const float _startSize, const float _rotation, const float _startAngularVelocity,
		const float _startLifeTime, const float _remainingLifeTime) noexcept
		: position{ emission.position }
		, velocity{ emission.velocity }
		, startColor{ _startColor }
		, startSize{ _startSize }
		, rotation{ _rotation }
		, startAngularVelocity{ _startAngularVelocity }
		, startLifeTime{ _startLifeTime }
		, remainingLifeTime{ _remainingLifeTime } {}

	void Particle2D::update(const float deltaTime, const Float2& deltaVelocity) noexcept
	{
		remainingLifeTime -= deltaTime;
		velocity += deltaVelocity;
		position += (velocity * deltaTime);
		rotation += (startAngularVelocity * deltaTime);
	}

	void Particle2D::advance(const float deltaTime, const Float2& deltaVelocity) noexcept
	{
		velocity += deltaVelocity;
		position += (velocity * deltaTime);
		rotation += (startAngularVelocity * deltaTime);
	}

	bool Particle2D::isDead() const noexcept
	{
		return (remainingLifeTime < 0.0);
	}
}
