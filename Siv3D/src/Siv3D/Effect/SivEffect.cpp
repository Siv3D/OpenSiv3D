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
# include <Siv3D/Effect/IEffect.hpp>
# include <Siv3D/Troubleshooting/Troubleshooting.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		static void CheckEngine()
		{
			if (not Siv3DEngine::isActive())
			{
				Troubleshooting::Show(Troubleshooting::Error::AssetInitializationBeforeEngineStartup, U"Effect");
				std::exit(EXIT_FAILURE);
			}
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Effect>>::AssetIDWrapper()
	{
		detail::CheckEngine();
	}

	template <>
	AssetIDWrapper<AssetHandle<Effect>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Effect))
		{
			p->release(m_id);
		}
	}

	Effect::Effect(const double maxLifeTimeSec)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Effect)->create(maxLifeTimeSec))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Effect::Effect(const Duration& maxLifeTimeSec)
		: Effect{ maxLifeTimeSec.count() } {}

	Effect::~Effect()
	{

	}

	Effect::operator bool() const
	{
		return hasEffects();
	}

	bool Effect::isEmpty() const
	{
		return (not hasEffects());
	}

	const Effect& Effect::add(std::unique_ptr<IEffect>&& effect) const
	{
		SIV3D_ENGINE(Effect)->add(m_handle->id(), std::move(effect));

		return *this;
	}

	bool Effect::hasEffects() const
	{
		return (0 < num_effects());
	}

	size_t Effect::num_effects() const
	{
		return SIV3D_ENGINE(Effect)->num_effects(m_handle->id());
	}

	void Effect::pause() const
	{
		SIV3D_ENGINE(Effect)->pause(m_handle->id());
	}

	bool Effect::isPaused() const
	{
		return SIV3D_ENGINE(Effect)->isPaused(m_handle->id());
	}

	void Effect::resume() const
	{
		SIV3D_ENGINE(Effect)->resume(m_handle->id());
	}

	const Effect& Effect::setSpeed(const double speed) const
	{
		SIV3D_ENGINE(Effect)->setSpeed(m_handle->id(), speed);

		return *this;
	}

	double Effect::getSpeed() const
	{
		return SIV3D_ENGINE(Effect)->getSpeed(m_handle->id());
	}

	const Effect& Effect::setMaxLifeTime(const double maxLifeTimeSec)
	{
		SIV3D_ENGINE(Effect)->setMaxLifeTime(m_handle->id(), maxLifeTimeSec);

		return *this;
	}

	void Effect::setMaxLifeTime(const Duration& maxLifeTimeSec)
	{
		SIV3D_ENGINE(Effect)->setMaxLifeTime(m_handle->id(), maxLifeTimeSec.count());
	}

	double Effect::getMaxLifeTime() const
	{
		return SIV3D_ENGINE(Effect)->getMaxLifeTime(m_handle->id());
	}

	void Effect::update() const
	{
		SIV3D_ENGINE(Effect)->updateEffect(m_handle->id());
	}

	void Effect::clear() const
	{
		SIV3D_ENGINE(Effect)->clear(m_handle->id());
	}

	void Effect::swap(Effect& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
