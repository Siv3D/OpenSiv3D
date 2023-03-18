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

# include <Siv3D/SimpleAnimation.hpp>
# include <Siv3D/Math.hpp>

namespace s3d
{
	SimpleAnimation::SimpleAnimation(ISteadyClock* pSteadyClock)
		: m_stopwatch{ StartImmediately::No, pSteadyClock } {}

	SimpleAnimation& SimpleAnimation::set(const StringView name, const KeyFrame& a, const KeyFrame& b, double func(double))
	{
		if ((b.time <= a.time)
			|| (func == nullptr))
		{
			return *this;
		}

		m_animationDurationSec = Max(m_animationDurationSec, b.time.count());

		m_animations[name].push_back({ a, b, func });

		m_animations[name].sort_by([](const Animation& a, const Animation& b) { return (a.a.time < b.a.time); });

		return *this;
	}

	SimpleAnimation& SimpleAnimation::setLoop(const SecondsF& loopEnd)
	{
		m_loopTiming.first = 0.0;
		m_loopTiming.second = loopEnd.count();
		return *this;
	}

	SimpleAnimation& SimpleAnimation::setLoop(const SecondsF& loopBegin, const SecondsF& loopEnd)
	{
		m_loopTiming.first = loopBegin.count();
		m_loopTiming.second = loopEnd.count();
		return *this;
	}

	double SimpleAnimation::operator [](const StringView name) const
	{
		auto it = m_animations.find(name);

		if (it == m_animations.end())
		{
			return 0.0;
		}

		return GetValue(it->second, posSec());
	}

	void SimpleAnimation::start()
	{
		m_stopwatch.start();
	}

	void SimpleAnimation::pause()
	{
		m_stopwatch.pause();
	}

	void SimpleAnimation::resume()
	{
		m_stopwatch.resume();
	}

	void SimpleAnimation::restart()
	{
		m_stopwatch.restart();
	}

	double SimpleAnimation::posSec() const
	{
		const double t = m_stopwatch.sF();

		if (m_loopTiming.second == 0.0)
		{
			return t;
		}

		if (t <= m_loopTiming.second)
		{
			return t;
		}
		else
		{
			const double loopLength = (m_loopTiming.second - m_loopTiming.first);

			const double ext = (t - m_loopTiming.second);

			return (m_loopTiming.first + Math::Fmod(ext, loopLength));
		}
	}

	double SimpleAnimation::lengthSec() const noexcept
	{
		return m_animationDurationSec;
	}

	bool SimpleAnimation::isDone() const
	{
		if (m_loopTiming.second != 0.0)
		{
			return false;
		}

		return (m_animationDurationSec <= m_stopwatch.sF());
	}

	size_t SimpleAnimation::loopCount() const
	{
		if (m_loopTiming.second == 0.0)
		{
			return 0;
		}

		const double t = m_stopwatch.sF();

		if (t <= m_loopTiming.second)
		{
			return 0;
		}
		else
		{
			const double loopLength = (m_loopTiming.second - m_loopTiming.first);

			const double ext = (t - m_loopTiming.second);

			return static_cast<size_t>(1 + (ext / loopLength));
		}
	}

	double SimpleAnimation::GetValue(const Array<Animation>& animations, const double timeSec)
	{
		if (timeSec < animations.front().a.time.count())
		{
			return animations.front().a.value;
		}

		if (animations.back().b.time.count() <= timeSec)
		{
			return animations.back().b.value;
		}

		for (size_t i = 0; i < animations.size(); ++i)
		{
			const auto& animation = animations[i];
			const double tA = animation.a.time.count();
			const double tB = animation.b.time.count();

			if (timeSec < tA)
			{
				return animations[i - 1].b.value;
			}

			if (InRange(timeSec, tA, tB))
			{
				const double duration = (tB - tA);
				const double f = ((timeSec - tA) / duration);
				return Math::Lerp(animation.a.value, animation.b.value, animation.func(f));
			}
		}

		return animations.back().b.value;
	}
}
