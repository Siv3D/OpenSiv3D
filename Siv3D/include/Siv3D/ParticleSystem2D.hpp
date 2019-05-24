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
# include <functional>
# include "Fwd.hpp"
# include "Color.hpp"
# include "BlendState.hpp"
# include "Emitter2D.hpp"
# include "Scene.hpp"

namespace s3d
{
	struct ParticleSystem2DParameters
	{
		using SizeOverLifeTimeFunc = std::function<float(float startSize, float startLifeTime, float remainingLifeTime)>;
		using ColorOverLifeTimeFunc = std::function<Float4(const Float4& startColor, float startLifeTime, float remainingLifeTime)>;

		double rate				= 50;
		double maxParticles		= 1000;
		double startLifeTime	= 1.0;
		double startSpeed		= 100.0;
		ColorF startColor		= ColorF(1.0);
		double startSize		= 10.0;
		double startRotationDeg			= 0.0;
		double startAngularVelocityDeg	= 0.0;
		bool randomStartRotation		= true;
		bool randomAngularVelocity		= true;
		BlendState blendState			= BlendState::Additive;

		SizeOverLifeTimeFunc sizeOverLifeTimeFunc;
		ColorOverLifeTimeFunc colorOverLifeTimeFunc;
	};

	class ParticleSystem2D
	{
	private:

		class ParticleSystem2DDetail;

		std::shared_ptr<ParticleSystem2DDetail> pImpl;

	public:

		ParticleSystem2D();

		~ParticleSystem2D();

		explicit ParticleSystem2D(const Vec2& position, const Vec2& force = Vec2(0, 0));

		ParticleSystem2D(const Vec2& position, const Vec2& force, std::unique_ptr<IEmitter2D>&& emitter,
			const ParticleSystem2DParameters& parameters, const Texture& texture);

		template <class Emitter, std::enable_if_t<std::is_base_of_v<IEmitter2D, Emitter>>* = nullptr>
		ParticleSystem2D(const Vec2& position, const Vec2& force, const Emitter& emitter,
			const ParticleSystem2DParameters& parameters, const Texture& texture)
			: ParticleSystem2D(position, force, std::make_unique<Emitter>(emitter), parameters, texture) {}

		void setPosition(const Vec2& position) noexcept;

		void setForce(const Vec2& force) noexcept;

		void setEmitter(std::unique_ptr<IEmitter2D>&& emitter);

		template <class Emitter, std::enable_if_t<std::is_base_of_v<IEmitter2D, Emitter>>* = nullptr>
		void setEmitter(const Emitter& emitter)
		{
			setEmitter(std::make_unique<Emitter>(emitter));
		}

		void setParameters(const ParticleSystem2DParameters& parameters);

		void setTexture(const Texture& texture) noexcept;

		size_t num_particles() const noexcept;

		void prewarm();

		void update(double deltaTime = Scene::DeltaTime());

		void draw() const;

		void drawDebug() const;
	};
}
