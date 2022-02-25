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
# include "IEmitter2D.hpp"
# include "ParticleSystem2DParameters.hpp"
# include "Scene.hpp"
# include "Texture.hpp"

namespace s3d
{
	class ParticleSystem2D
	{
	public:

		SIV3D_NODISCARD_CXX20
		ParticleSystem2D();

		SIV3D_NODISCARD_CXX20
		explicit ParticleSystem2D(const Vec2& position, const Vec2& force = Vec2{ 0, 0 });

		SIV3D_NODISCARD_CXX20
		ParticleSystem2D(const Vec2& position, const Vec2& force, std::unique_ptr<IEmitter2D>&& emitter,
			const ParticleSystem2DParameters& parameters, const Texture& texture);

		template <class Emitter, std::enable_if_t<std::is_base_of_v<IEmitter2D, Emitter>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		ParticleSystem2D(const Vec2& position, const Vec2& force, const Emitter& emitter,
			const ParticleSystem2DParameters& parameters, const Texture& texture);

		~ParticleSystem2D();

		void setPosition(const Vec2& position) noexcept;

		void setForce(const Vec2& force) noexcept;

		void setEmitter(std::unique_ptr<IEmitter2D>&& emitter);

		template <class Emitter, std::enable_if_t<std::is_base_of_v<IEmitter2D, Emitter>>* = nullptr>
		void setEmitter(const Emitter& emitter);

		void setParameters(const ParticleSystem2DParameters& parameters);

		void setTexture(const Texture& texture) noexcept;

		[[nodiscard]]
		size_t num_particles() const noexcept;

		void prewarm();

		void update(double deltaTime = Scene::DeltaTime());

		void draw() const;

		void drawDebug() const;

	private:

		class ParticleSystem2DDetail;

		std::shared_ptr<ParticleSystem2DDetail> pImpl;
	};
}

# include "detail/ParticleSystem2D.ipp"
