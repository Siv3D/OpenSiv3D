//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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

		virtual bool init() = 0;

		virtual Effect::IDType create() = 0;

		virtual void release(Effect::IDType handleID) = 0;

		virtual void add(Effect::IDType handleID, std::unique_ptr<IEffect>&& effect) = 0;

		virtual size_t num_effects(Effect::IDType handleID) = 0;

		virtual void pause(Effect::IDType handleID) = 0;

		virtual bool isPaused(Effect::IDType handleID) = 0;

		virtual void resume(Effect::IDType handleID) = 0;

		virtual void setSpeed(Effect::IDType handleID, double speed) = 0;

		virtual double getSpeed(Effect::IDType handleID) = 0;

		virtual void update(Effect::IDType handleID) = 0;

		virtual void clear(Effect::IDType handleID) = 0;
	};
}
