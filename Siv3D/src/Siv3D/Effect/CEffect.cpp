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

# include "CEffect.hpp"
# include <Siv3D/Time.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CEffect::CEffect()
	{

	}

	CEffect::~CEffect()
	{
		LOG_TRACE(U"CEffect::~CEffect()");

		m_effects.destroy();
	}

	void CEffect::init()
	{
		LOG_TRACE(U"CEffect::init()");

		auto nullEffect = std::make_unique<EffectData>(EffectData::Null{});

		if (!nullEffect->isInitialized())
		{
			throw EngineError(U"Null Effect initialization failed");
		}

		m_effects.setNullData(std::move(nullEffect));

		LOG_INFO(U"ℹ️ CEffect initialized");
	}

	void CEffect::update()
	{
		if (m_previousTimeUs == 0)
		{
			m_previousTimeUs = Time::GetMicrosec();
		}
		else
		{
			const uint64 currentTimeUs = Time::GetMicrosec();

			const uint64 currentDeltaTimeUS = currentTimeUs - m_previousTimeUs;

			m_previousTimeUs = currentTimeUs;

			for (auto& data : m_effects)
			{
				data.second->setCurrectDeltaTimeUs(currentDeltaTimeUS);
			}
		}
	}

	EffectID CEffect::create()
	{
		auto effet = std::make_unique<EffectData>(EffectData::Null{});

		if (!effet->isInitialized())
		{
			return EffectID::NullAsset();
		}

		return m_effects.add(std::move(effet));
	}

	void CEffect::release(const EffectID handleID)
	{
		m_effects.erase(handleID);
	}

	void CEffect::add(const EffectID handleID, std::unique_ptr<IEffect>&& effect)
	{
		if (!effect)
		{
			return;
		}

		m_effects[handleID]->add(std::move(effect));
	}

	size_t CEffect::num_effects(const EffectID handleID)
	{
		return m_effects[handleID]->num_effects();
	}

	void CEffect::pause(const EffectID handleID)
	{
		m_effects[handleID]->pause();
	}

	bool CEffect::isPaused(const EffectID handleID)
	{
		return m_effects[handleID]->isPaused();
	}

	void CEffect::resume(const EffectID handleID)
	{
		m_effects[handleID]->resume();
	}

	void CEffect::setSpeed(const EffectID handleID, const double speed)
	{
		m_effects[handleID]->setSpeed(speed);
	}

	double CEffect::getSpeed(const EffectID handleID)
	{
		return m_effects[handleID]->getSpeed();
	}

	void CEffect::updateEffect(const EffectID handleID)
	{
		m_effects[handleID]->update();
	}

	void CEffect::clear(const EffectID handleID)
	{
		m_effects[handleID]->clear();
	}
}
