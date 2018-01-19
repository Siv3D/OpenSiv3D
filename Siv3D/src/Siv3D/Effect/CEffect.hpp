//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IEffect.hpp"
# include "../AssetHandleManager/AssetHandleManager.hpp"
# include "EffectData.hpp"

namespace s3d
{
	class CEffect : public ISiv3DEffect
	{
	private:

		AssetHandleManager<EffectID, EffectData> m_effects{ U"Effect" };

	public:

		CEffect();

		~CEffect() override;

		bool init() override;

		EffectID create() override;

		void release(EffectID handleID) override;

		void add(EffectID handleID, std::unique_ptr<IEffect>&& effect) override;

		size_t num_effects(EffectID handleID) override;

		void pause(EffectID handleID) override;

		bool isPaused(EffectID handleID) override;

		void resume(EffectID handleID) override;

		void setSpeed(EffectID handleID, double speed) override;

		double getSpeed(EffectID handleID) override;

		void update(EffectID handleID) override;

		void clear(EffectID handleID) override;
	};
}
