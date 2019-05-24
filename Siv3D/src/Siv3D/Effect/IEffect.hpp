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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Effect.hpp>

namespace s3d
{
	class ISiv3DEffect
	{
	public:

		static ISiv3DEffect* Create();

		virtual ~ISiv3DEffect() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual EffectID create() = 0;

		virtual void release(EffectID handleID) = 0;

		virtual void add(EffectID handleID, std::unique_ptr<IEffect>&& effect) = 0;

		virtual size_t num_effects(EffectID handleID) = 0;

		virtual void pause(EffectID handleID) = 0;

		virtual bool isPaused(EffectID handleID) = 0;

		virtual void resume(EffectID handleID) = 0;

		virtual void setSpeed(EffectID handleID, double speed) = 0;

		virtual double getSpeed(EffectID handleID) = 0;

		virtual void updateEffect(EffectID handleID) = 0;

		virtual void clear(EffectID handleID) = 0;
	};
}
