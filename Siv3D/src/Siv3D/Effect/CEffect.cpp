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

# include <Siv3D/Effect.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CEffect.hpp"

namespace s3d
{
	CEffect::CEffect()
	{
		// do nothing
	}

	CEffect::~CEffect()
	{
		LOG_SCOPED_TRACE(U"CEffect::~CEffect()");

		m_effects.destroy();
	}

	void CEffect::init()
	{
		LOG_SCOPED_TRACE(U"CEffect::init()");

		// null Effect を管理に登録
		{
			// null Effect を作成
			auto nullEffect = std::make_unique<EffectData>(EffectData::Null{});

			if (not nullEffect->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null Effect initialization failed");
			}

			// 管理に登録
			m_effects.setNullData(std::move(nullEffect));
		}
	}

	void CEffect::update()
	{
		if (m_previousTimeUs == 0) // first frame
		{
			m_previousTimeUs = Time::GetMicrosec();
		}
		else
		{
			const uint64 currentTimeUs = Time::GetMicrosec();
			const uint64 currentDeltaTimeUS = (currentTimeUs - m_previousTimeUs);
			m_previousTimeUs = currentTimeUs;

			for (auto& data : m_effects)
			{
				data.second->setCurrectDeltaTimeUs(currentDeltaTimeUS);
			}
		}
	}

	Effect::IDType CEffect::create(double maxLifeTimeSec)
	{
		// Effect を作成
		auto effect = std::make_unique<EffectData>(EffectData::Null{}, maxLifeTimeSec);

		if (not effect->isInitialized()) // もし作成に失敗していたら
		{
			return Effect::IDType::NullAsset();
		}

		// Effect を管理に登録
		return m_effects.add(std::move(effect));
	}

	void CEffect::release(const Effect::IDType handleID)
	{
		m_effects.erase(handleID);
	}

	void CEffect::add(const Effect::IDType handleID, std::unique_ptr<IEffect>&& effect)
	{
		if (not effect)
		{
			return;
		}

		m_effects[handleID]->add(std::move(effect));
	}

	size_t CEffect::num_effects(const Effect::IDType handleID)
	{
		return m_effects[handleID]->num_effects();
	}

	void CEffect::pause(const Effect::IDType handleID)
	{
		m_effects[handleID]->pause();
	}

	bool CEffect::isPaused(const Effect::IDType handleID)
	{
		return m_effects[handleID]->isPaused();
	}

	void CEffect::resume(const Effect::IDType handleID)
	{
		m_effects[handleID]->resume();
	}

	void CEffect::setSpeed(const Effect::IDType handleID, const double speed)
	{
		m_effects[handleID]->setSpeed(speed);
	}

	double CEffect::getSpeed(const Effect::IDType handleID)
	{
		return m_effects[handleID]->getSpeed();
	}

	void CEffect::setMaxLifeTime(const Effect::IDType handleID, const double maxLifeTimeSec)
	{
		m_effects[handleID]->setMaxLifeTime(maxLifeTimeSec);
	}

	double CEffect::getMaxLifeTime(const Effect::IDType handleID)
	{
		return m_effects[handleID]->getMaxLifeTime();
	}

	void CEffect::updateEffect(const Effect::IDType handleID)
	{
		m_effects[handleID]->update();
	}

	void CEffect::clear(const Effect::IDType handleID)
	{
		m_effects[handleID]->clear();
	}
}
