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
# include "IEffect.hpp"
# include <AssetHandleManager/AssetHandleManager.hpp>
# include "EffectData.hpp"

namespace s3d
{
	class CEffect : public ISiv3DEffect
	{
	private:

		AssetHandleManager<EffectID, EffectData> m_effects{ U"Effect" };

		uint64 m_previousTimeUs = 0;

	public:

		CEffect();

		~CEffect() override;

		void init() override;

		void update() override;

		EffectID create() override;

		void release(EffectID handleID) override;

		void add(EffectID handleID, std::unique_ptr<IEffect>&& effect) override;

		size_t num_effects(EffectID handleID) override;

		void pause(EffectID handleID) override;

		bool isPaused(EffectID handleID) override;

		void resume(EffectID handleID) override;

		void setSpeed(EffectID handleID, double speed) override;

		double getSpeed(EffectID handleID) override;

		void updateEffect(EffectID handleID) override;

		void clear(EffectID handleID) override;
	};
}
