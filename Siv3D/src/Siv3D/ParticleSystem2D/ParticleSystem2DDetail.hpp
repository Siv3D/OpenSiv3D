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

# pragma once
# include <Siv3D/ParticleSystem2D.hpp>
# include <Siv3D/Particle2D.hpp>

namespace s3d
{
	class ParticleSystem2D::ParticleSystem2DDetail
	{
	public:

		ParticleSystem2DDetail();

		ParticleSystem2DDetail(const Vec2& position, const Vec2& force);

		ParticleSystem2DDetail(const Vec2& position, const Vec2& force, std::unique_ptr<IEmitter2D>&& emitter,
			const ParticleSystem2DParameters& parameters, const Texture& texture);

		~ParticleSystem2DDetail();

		void setPosition(const Vec2& position) noexcept;

		void setForce(const Vec2& force) noexcept;

		void setEmitter(std::unique_ptr<IEmitter2D>&& emitter);

		void setParameters(const ParticleSystem2DParameters& parameters);

		void setTexture(const Texture& texture) noexcept;

		size_t num_particles() const noexcept;

		void prewarm();

		void update(double deltaTime);

		void draw() const;

		void drawDebug() const;

	private:

		Array<Particle2D> m_particles;
		double m_remainingTime = 0.0;

		Vec2 m_position = Vec2(0, 0);
		Vec2 m_force = Vec2(0, 0);
		ParticleSystem2DParameters m_parameters;

		std::unique_ptr<IEmitter2D> m_emitter;
		Texture m_particleTexture;

		void updateCurrentparticles(float deltaTime);

		void addParticles(const ParticleSystem2DParameters& params);

		void drawParticle() const;

		void drawTexturedParticle() const;

		void drawDebugParticle() const;
	};
}
