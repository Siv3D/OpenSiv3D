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

# include <Siv3D/ScopedRenderStates2D.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "ParticleSystem2DDetail.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static float DefaultSizeOverLifeTimeFunc(float startSize, float startLifeTime, float remainingLifeTime)
		{
			return startSize * (remainingLifeTime / startLifeTime);
		};

		[[nodiscard]]
		static Float4 DefaultColorOverLifeTimeFunc(const Float4& startColor, float, float)
		{
			return startColor;
		};
	}

	ParticleSystem2D::ParticleSystem2DDetail::ParticleSystem2DDetail() {}

	ParticleSystem2D::ParticleSystem2DDetail::ParticleSystem2DDetail(const Vec2& position, const Vec2& force)
		: m_position{ position }
		, m_force{ force } {}

	ParticleSystem2D::ParticleSystem2DDetail::ParticleSystem2DDetail(const Vec2& position, const Vec2& force, std::unique_ptr<IEmitter2D>&& emitter,
		const ParticleSystem2DParameters& parameters, const Texture& texture)
		: m_position{ position }
		, m_force{ force }
		, m_parameters{ parameters }
		, m_emitter{ std::move(emitter) }
		, m_particleTexture{ texture } {}

	ParticleSystem2D::ParticleSystem2DDetail::~ParticleSystem2DDetail() {}

	void ParticleSystem2D::ParticleSystem2DDetail::setPosition(const Vec2& position) noexcept
	{
		m_position = position;
	}

	void ParticleSystem2D::ParticleSystem2DDetail::setForce(const Vec2& force) noexcept
	{
		m_force = force;
	}

	void ParticleSystem2D::ParticleSystem2DDetail::setEmitter(std::unique_ptr<IEmitter2D>&& emitter)
	{
		m_emitter = std::move(emitter);
	}

	void ParticleSystem2D::ParticleSystem2DDetail::setParameters(const ParticleSystem2DParameters& parameters)
	{
		m_parameters = parameters;
	}

	void ParticleSystem2D::ParticleSystem2DDetail::setTexture(const Texture& texture) noexcept
	{
		m_particleTexture = texture;
	}

	size_t ParticleSystem2D::ParticleSystem2DDetail::num_particles() const noexcept
	{
		return m_particles.size();
	}

	void ParticleSystem2D::ParticleSystem2DDetail::prewarm()
	{
		if (not m_emitter)
		{
			return;
		}

		if (m_parameters.rate == 0.0)
		{
			return;
		}

		m_remainingTime = m_parameters.startLifeTime;

		addParticles(m_parameters);
	}

	void ParticleSystem2D::ParticleSystem2DDetail::update(const double deltaTime)
	{
		updateCurrentparticles(static_cast<float>(deltaTime));

		m_remainingTime += deltaTime;

		if (not m_emitter)
		{
			m_remainingTime = 0.0;
			return;
		}

		if (m_parameters.rate == 0.0)
		{
			m_remainingTime = 0.0;
			return;
		}

		addParticles(m_parameters);
	}

	void ParticleSystem2D::ParticleSystem2DDetail::draw() const
	{
		ScopedRenderStates2D blend{ m_parameters.blendState };

		if (m_particleTexture)
		{
			drawTexturedParticle();
		}
		else
		{
			drawParticle();
		}
	}

	void ParticleSystem2D::ParticleSystem2DDetail::drawDebug() const
	{
		ScopedRenderStates2D blend{ m_parameters.blendState };

		if (m_emitter)
		{
			m_emitter->drawDebug(m_position);
		}

		drawDebugParticle();
	}

	void ParticleSystem2D::ParticleSystem2DDetail::updateCurrentparticles(float deltaTime)
	{
		const Float2 deltaVelocity = (m_force * deltaTime);

		for (auto& particle : m_particles)
		{
			particle.update(deltaTime, deltaVelocity);
		}

		m_particles.remove_if([](const Particle2D& p) { return p.isDead(); });
	}

	void ParticleSystem2D::ParticleSystem2DDetail::addParticles(const ParticleSystem2DParameters& params)
	{
		const double timePerParticle = (1.0 / params.rate);

		while (m_remainingTime > timePerParticle)
		{
			m_remainingTime -= timePerParticle;
			const double remainigLifeTime = (params.startLifeTime - m_remainingTime);

			if (remainigLifeTime <= 0.0)
			{
				continue;
			}

			const double startRotationDeg = params.startRotationDeg + Random(-params.randomStartRotationDeg * 0.5, params.randomStartRotationDeg * 0.5);
			const double angularVelocityDeg = params.startAngularVelocityDeg + Random(-params.randomStartAngularVelocityDeg * 0.5, params.randomStartAngularVelocityDeg * 0.5);

			Particle2D particle(
				m_emitter->emit(m_position, params.startSpeed),
				params.startColor.toFloat4(),
				static_cast<float>(params.startSize),
				static_cast<float>(Math::ToRadians(startRotationDeg)),
				static_cast<float>(Math::ToRadians(angularVelocityDeg)),
				static_cast<float>(params.startLifeTime),
				static_cast<float>(remainigLifeTime)
			);

			const float perParticledeltaTime = (particle.startLifeTime - particle.remainingLifeTime);
			particle.advance(perParticledeltaTime, m_force * perParticledeltaTime);
			m_particles << particle;
		}

		if (const size_t maxParticles = static_cast<size_t>(params.maxParticles); m_particles.size() > maxParticles)
		{
			m_particles.erase(m_particles.begin(), m_particles.begin() + (m_particles.size() - maxParticles));
		}
	}

	void ParticleSystem2D::ParticleSystem2DDetail::drawParticle() const
	{
		const ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc =
			m_parameters.sizeOverLifeTimeFunc ? m_parameters.sizeOverLifeTimeFunc : detail::DefaultSizeOverLifeTimeFunc;
		const ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc =
			m_parameters.colorOverLifeTimeFunc ? m_parameters.colorOverLifeTimeFunc : detail::DefaultColorOverLifeTimeFunc;

		for (const auto& particle : m_particles)
		{
			const float size = sizeOverLifeTimeFunc(particle.startSize, particle.startLifeTime, particle.remainingLifeTime);
			const Float4 color = colorOverLifeTimeFunc(particle.startColor, particle.startLifeTime, particle.remainingLifeTime);

			RectF{ Arg::center = particle.position, size }
				.rotated(particle.rotation)
				.draw(ColorF{ color });
		}
	}

	void ParticleSystem2D::ParticleSystem2DDetail::drawTexturedParticle() const
	{
		const ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc =
			m_parameters.sizeOverLifeTimeFunc ? m_parameters.sizeOverLifeTimeFunc : detail::DefaultSizeOverLifeTimeFunc;
		const ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc =
			m_parameters.colorOverLifeTimeFunc ? m_parameters.colorOverLifeTimeFunc : detail::DefaultColorOverLifeTimeFunc;

		SIV3D_ENGINE(Renderer2D)->addTexturedParticles(m_particleTexture, m_particles, sizeOverLifeTimeFunc, colorOverLifeTimeFunc);
	}

	void ParticleSystem2D::ParticleSystem2DDetail::drawDebugParticle() const
	{
		const ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc =
			m_parameters.sizeOverLifeTimeFunc ? m_parameters.sizeOverLifeTimeFunc : detail::DefaultSizeOverLifeTimeFunc;
		const ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc =
			m_parameters.colorOverLifeTimeFunc ? m_parameters.colorOverLifeTimeFunc : detail::DefaultColorOverLifeTimeFunc;

		for (const auto& particle : m_particles)
		{
			const float size = sizeOverLifeTimeFunc(particle.startSize, particle.startLifeTime, particle.remainingLifeTime);
			const Float4 color = colorOverLifeTimeFunc(particle.startColor, particle.startLifeTime, particle.remainingLifeTime);

			RectF{ Arg::center = particle.position, size }
				.rotated(particle.rotation)
				.drawFrame(1, ColorF{ color });
		}
	}
}
