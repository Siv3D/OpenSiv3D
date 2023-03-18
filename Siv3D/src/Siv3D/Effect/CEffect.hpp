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
# include <Siv3D/Common.hpp>
# include <Siv3D/Effect.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "IEffect.hpp"
# include "EffectData.hpp"

namespace s3d
{
	class CEffect final : public ISiv3DEffect
	{
	private:

		AssetHandleManager<Effect::IDType, EffectData> m_effects{ U"Effect" };

		uint64 m_previousTimeUs = 0;

	public:

		CEffect();

		~CEffect();

		void init() override;

		void update() override;

		Effect::IDType create(double maxLifeTimeSec) override;

		void release(Effect::IDType handleID) override;

		void add(Effect::IDType handleID, std::unique_ptr<IEffect>&& effect) override;

		size_t num_effects(Effect::IDType handleID) override;

		void pause(Effect::IDType handleID) override;

		bool isPaused(Effect::IDType handleID) override;

		void resume(Effect::IDType handleID) override;

		void setSpeed(Effect::IDType handleID, double speed) override;

		double getSpeed(Effect::IDType handleID) override;

		void setMaxLifeTime(Effect::IDType handleID, double maxLifeTimeSec) override;

		double getMaxLifeTime(Effect::IDType handleID) override;

		void updateEffect(Effect::IDType handleID) override;

		void clear(Effect::IDType handleID) override;
	};
}
