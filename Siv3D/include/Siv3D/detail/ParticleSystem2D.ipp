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

namespace s3d
{
	template <class Emitter, std::enable_if_t<std::is_base_of_v<IEmitter2D, Emitter>>*>
	inline ParticleSystem2D::ParticleSystem2D(const Vec2& position, const Vec2& force, const Emitter& emitter,
		const ParticleSystem2DParameters& parameters, const Texture& texture)
			: ParticleSystem2D{ position, force, std::make_unique<Emitter>(emitter), parameters, texture } {}

	template <class Emitter, std::enable_if_t<std::is_base_of_v<IEmitter2D, Emitter>>*>
	inline void ParticleSystem2D::setEmitter(const Emitter& emitter)
	{
		setEmitter(std::make_unique<Emitter>(emitter));
	}
}
