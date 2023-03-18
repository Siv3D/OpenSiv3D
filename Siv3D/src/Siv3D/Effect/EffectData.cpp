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

# include "EffectData.hpp"

namespace s3d
{
	EffectData::EffectData(Null, const double maxLifeTimeSec)
		: m_maxLifeTimeSec{ maxLifeTimeSec }
		, m_initialized{ true } {}

	bool EffectData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	void EffectData::add(std::unique_ptr<IEffect>&& effect)
	{
		if (m_paused)
		{
			return;
		}

		m_effects.emplace_back(std::move(effect), 0);
	}

	size_t EffectData::num_effects() const noexcept
	{
		return m_effects.size();
	}

	void EffectData::pause() noexcept
	{
		m_paused = true;
	}

	bool EffectData::isPaused() const noexcept
	{
		return m_paused;
	}

	void EffectData::resume() noexcept
	{
		m_paused = false;
	}

	void EffectData::setSpeed(const double speed) noexcept
	{
		m_speed = speed;
	}

	double EffectData::getSpeed() const noexcept
	{
		return m_speed;
	}

	void EffectData::setMaxLifeTime(const double maxLifeTimeSec) noexcept
	{
		m_maxLifeTimeSec = maxLifeTimeSec;
	}

	double EffectData::getMaxLifeTime() const noexcept
	{
		return m_maxLifeTimeSec;
	}

	void EffectData::setCurrectDeltaTimeUs(const uint64 currentDeltaUs) noexcept
	{
		const int64 deltaUs = (m_paused ? 0 : static_cast<int64>(currentDeltaUs * m_speed));

		m_lastDeltaSec = (deltaUs / 1'000'000.0);
	}

	void EffectData::update()
	{
		for (auto& effect : m_effects)
		{
			effect.second += m_lastDeltaSec;
		}

		m_lastDeltaSec = 0.0;

		for (auto it = m_effects.begin(); it != m_effects.end();)
		{
			const double timeSec = it->second;

			if (timeSec < 0.0)
			{
				++it;
				continue;
			}

			if (m_maxLifeTimeSec < timeSec)
			{
				it = m_effects.erase(it);
				continue;
			}
		
			if (it->first->update(timeSec) == false)
			{
				if (m_effects.empty()) // effect is cleared.
				{
					break;
				}

				it = m_effects.erase(it);
				continue;
			}
			
			++it;
		}
	}

	void EffectData::clear()
	{
		m_effects.clear();
	}
}
