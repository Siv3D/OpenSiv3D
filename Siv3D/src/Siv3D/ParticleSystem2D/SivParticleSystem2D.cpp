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

# include <Siv3D/ParticleSystem2D.hpp>
# include <Siv3D/ParticleSystem2D/ParticleSystem2DDetail.hpp>

namespace s3d
{
	ParticleSystem2D::ParticleSystem2D()
		: pImpl{ std::make_shared<ParticleSystem2DDetail>() } {}

	ParticleSystem2D::ParticleSystem2D(const Vec2& position, const Vec2& force)
		: pImpl{ std::make_shared<ParticleSystem2DDetail>(position, force) } {}

	ParticleSystem2D::ParticleSystem2D(const Vec2& position, const Vec2& force, std::unique_ptr<IEmitter2D>&& emitter,
		const ParticleSystem2DParameters& parameters, const Texture& texture)
		: pImpl{ std::make_shared<ParticleSystem2DDetail>(position, force, std::move(emitter), parameters, texture) } {}

	ParticleSystem2D::~ParticleSystem2D() {}

	void ParticleSystem2D::setPosition(const Vec2& position) noexcept
	{
		pImpl->setPosition(position);
	}

	void ParticleSystem2D::setForce(const Vec2& force) noexcept
	{
		pImpl->setForce(force);
	}

	void ParticleSystem2D::setEmitter(std::unique_ptr<IEmitter2D>&& emitter)
	{
		pImpl->setEmitter(std::move(emitter));
	}

	void ParticleSystem2D::setParameters(const ParticleSystem2DParameters& parameters)
	{
		pImpl->setParameters(parameters);
	}

	void ParticleSystem2D::setTexture(const Texture& texture) noexcept
	{
		pImpl->setTexture(texture);
	}

	size_t ParticleSystem2D::num_particles() const noexcept
	{
		return pImpl->num_particles();
	}

	void ParticleSystem2D::prewarm()
	{
		pImpl->prewarm();
	}

	void ParticleSystem2D::update(const double deltaTime)
	{
		pImpl->update(deltaTime);
	}

	void ParticleSystem2D::draw() const
	{
		pImpl->draw();
	}

	void ParticleSystem2D::drawDebug() const
	{
		pImpl->drawDebug();
	}
}
