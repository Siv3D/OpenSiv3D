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
# include "IEffect.hpp"
# include "../AssetHandleManager/AssetHandleManager.hpp"
# include "EffectData.hpp"

namespace s3d
{
	class CEffect : public ISiv3DEffect
	{
	private:

		AssetHandleManager<Effect::IDType, std::shared_ptr<EffectData>> m_effects{ S3DSTR("Effect") };

	public:

		CEffect();

		~CEffect() override;

		bool init() override;

		Effect::IDType create() override;

		void release(Effect::IDType handleID) override;

		void add(Effect::IDType handleID, std::unique_ptr<IEffect>&& effect) override;

		size_t num_effects(Effect::IDType handleID) override;

		void pause(Effect::IDType handleID) override;

		bool isPaused(Effect::IDType handleID) override;

		void resume(Effect::IDType handleID) override;

		void setSpeed(Effect::IDType handleID, double speed) override;

		double getSpeed(Effect::IDType handleID) override;

		void update(Effect::IDType handleID) override;

		void clear(Effect::IDType handleID) override;
	};
}
