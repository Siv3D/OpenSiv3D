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

# include "CEffect.hpp"

namespace s3d
{
	CEffect::CEffect()
	{

	}

	CEffect::~CEffect()
	{
		m_effects.destroy();
	}

	bool CEffect::init()
	{
		const auto nullEffect = std::make_shared<EffectData>(EffectData::Null{});

		if (!nullEffect->isInitialized())
		{
			return false;
		}

		m_effects.setNullData(nullEffect);

		return true;
	}

	Effect::IDType CEffect::create()
	{
		const auto effet = std::make_shared<EffectData>(EffectData::Null{});

		if (!effet->isInitialized())
		{
			return Effect::NullHandleID;
		}

		return m_effects.add(effet);
	}

	void CEffect::release(const Effect::IDType handleID)
	{
		m_effects.erase(handleID);
	}

	void CEffect::add(const Effect::IDType handleID, std::unique_ptr<IEffect>&& effect)
	{
		if (!effect)
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

	void CEffect::update(const Effect::IDType handleID)
	{
		m_effects[handleID]->update();
	}

	void CEffect::clear(const Effect::IDType handleID)
	{
		m_effects[handleID]->clear();
	}
}
