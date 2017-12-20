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
# include <Siv3D/Time.hpp>

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

		if (m_previousTimeUs == 0)
		{
			m_previousTimeUs = Time::GetMicrosec();
		}
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

		m_previousTimeUs = Time::GetMicrosec();
	}

	void EffectData::setSpeed(const double speed)
	{
		m_speed = speed;
	}

	void EffectData::update()
	{
		const uint64 currentTimeUs = Time::GetMicrosec();

		const int64 deltaUs = m_paused ? 0 : static_cast<int64>((currentTimeUs - m_previousTimeUs) * m_speed);

		const double deltaSec = deltaUs / 1'000'000.0;

		m_previousTimeUs = currentTimeUs;

		for (auto it = m_effects.begin(); it != m_effects.end();)
		{
			const double timeSec = it->second += deltaSec;

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
