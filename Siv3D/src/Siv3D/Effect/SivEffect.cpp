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

# include <Siv3DEngine.hpp>
# include <AssetHandleManager/AssetReport.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include "IEffect.hpp"

namespace s3d
{
	template <>
	AssetHandle<Effect::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Effect` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Effect::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Effect` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Effect::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::Get<ISiv3DEffect>())
		{
			p->release(m_id);
		}
	}

	Effect::Effect()
		: m_handle(std::make_shared<EffectHandle>(Siv3DEngine::Get<ISiv3DEffect>()->create()))
	{
		ReportAssetCreation();
	}

	Effect::~Effect()
	{

	}

	void Effect::release()
	{
		m_handle = std::make_shared<EffectHandle>();
	}

	EffectID Effect::id() const
	{
		return m_handle->id();
	}

	bool Effect::operator ==(const Effect& effect) const
	{
		return m_handle->id() == effect.m_handle->id();
	}

	bool Effect::operator !=(const Effect& effect) const
	{
		return m_handle->id() != effect.m_handle->id();
	}

	Effect::operator bool() const
	{
		return hasEffects();
	}

	bool Effect::isEmpty() const
	{
		return !hasEffects();
	}

	bool Effect::hasEffects() const
	{
		return num_effects() > 0;
	}

	size_t Effect::num_effects() const
	{
		return Siv3DEngine::Get<ISiv3DEffect>()->num_effects(m_handle->id());
	}

	void Effect::add(std::unique_ptr<IEffect>&& effect) const
	{
		Siv3DEngine::Get<ISiv3DEffect>()->add(m_handle->id(), std::move(effect));
	}

	void Effect::add(std::function<bool(double)> f) const
	{
		struct AnonymousEffect : IEffect
		{
			std::function<bool(double)> function;

			explicit AnonymousEffect(std::function<bool(double)> _function)
				: function(_function) {}

			bool update(double timeSec) override
			{
				return function(timeSec);
			}
		};

		add(std::make_unique<AnonymousEffect>(f));
	}

	void Effect::pause() const
	{
		Siv3DEngine::Get<ISiv3DEffect>()->pause(m_handle->id());
	}

	bool Effect::isPaused() const
	{
		return Siv3DEngine::Get<ISiv3DEffect>()->isPaused(m_handle->id());
	}

	void Effect::resume() const
	{
		Siv3DEngine::Get<ISiv3DEffect>()->resume(m_handle->id());
	}

	void Effect::setSpeed(const double speed) const
	{
		Siv3DEngine::Get<ISiv3DEffect>()->setSpeed(m_handle->id(), speed);
	}

	double Effect::getSpeed() const
	{
		return Siv3DEngine::Get<ISiv3DEffect>()->getSpeed(m_handle->id());
	}

	void Effect::update() const
	{
		Siv3DEngine::Get<ISiv3DEffect>()->updateEffect(m_handle->id());
	}

	void Effect::clear() const
	{
		Siv3DEngine::Get<ISiv3DEffect>()->clear(m_handle->id());
	}
}
