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

# include "../Siv3DEngine.hpp"
# include "IEffect.hpp"
# include "../Profiler/IProfiler.hpp"

namespace s3d
{
	template <>
	AssetHandle<Effect::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetEffect())
		{
			p->release(m_id);
		}
	}

	Effect::Effect()
		: m_handle(std::make_shared<EffectHandle>(Siv3DEngine::GetEffect()->create()))
	{
		ASSET_CREATION();
	}

	Effect::~Effect()
	{

	}

	void Effect::release()
	{
		m_handle = std::make_shared<EffectHandle>();
	}

	Effect::IDType Effect::id() const
	{
		return m_handle->getID();
	}

	bool Effect::operator ==(const Effect& effect) const
	{
		return m_handle->getID() == effect.m_handle->getID();
	}

	bool Effect::operator !=(const Effect& effect) const
	{
		return m_handle->getID() != effect.m_handle->getID();
	}

	size_t Effect::num_effects() const
	{
		return Siv3DEngine::GetEffect()->num_effects(m_handle->getID());
	}

	void Effect::add(std::unique_ptr<IEffect>&& effect) const
	{
		Siv3DEngine::GetEffect()->add(m_handle->getID(), std::move(effect));
	}

	void Effect::pause() const
	{
		Siv3DEngine::GetEffect()->pause(m_handle->getID());
	}

	bool Effect::isPaused() const
	{
		return Siv3DEngine::GetEffect()->isPaused(m_handle->getID());
	}

	void Effect::resume() const
	{
		Siv3DEngine::GetEffect()->resume(m_handle->getID());
	}

	void Effect::setSpeed(const double speed) const
	{
		Siv3DEngine::GetEffect()->setSpeed(m_handle->getID(), speed);
	}

	double Effect::getSpeed() const
	{
		return Siv3DEngine::GetEffect()->getSpeed(m_handle->getID());
	}

	void Effect::update() const
	{
		Siv3DEngine::GetEffect()->update(m_handle->getID());
	}

	void Effect::clear() const
	{
		Siv3DEngine::GetEffect()->clear(m_handle->getID());
	}
}
