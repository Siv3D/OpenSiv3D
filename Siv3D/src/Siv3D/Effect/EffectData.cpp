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

namespace s3d
{
	EffectData::EffectData(Null)
	{
		m_initialized = true;
	}

	void EffectData::add(std::unique_ptr<IEffect>&& effect)
	{
		if (m_paused)
		{
			return;
		}

		m_effects.emplace_back(std::move(effect), 0);
	}

	size_t EffectData::num_effects() const
	{
		return m_effects.size();
	}

	void EffectData::pause()
	{
		m_paused = true;
	}

	void EffectData::resume()
	{
		m_paused = false;
	}

	void EffectData::setSpeed(const double speed)
	{
		m_speed = speed;
	}

	void EffectData::setCurrectDeltaTimeUs(const uint64 currentDeltaUs)
	{
		const int64 deltaUs = m_paused ? 0 : static_cast<int64>(currentDeltaUs * m_speed);

		m_lastDeltaSec = deltaUs / 1'000'000.0;
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
			else if (timeSec > MaxEffectLengthSec
				|| (it->first->update(timeSec) == false))
			{
				it = m_effects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void EffectData::clear()
	{
		m_effects.clear();
	}
}
