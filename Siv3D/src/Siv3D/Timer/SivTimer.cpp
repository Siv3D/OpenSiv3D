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

# include <Siv3D/Timer.hpp>

namespace s3d
{
	Timer::Timer(const double timeSec, const bool startImmediately)
		: m_initialTimeMicrosec(static_cast<int64>(timeSec * 1'000'000))
	{
		set(SecondsF(timeSec));

		if (startImmediately)
		{
			start();
		}
	}

	Timer::Timer(const Duration& time, const bool startImmediately)
		: m_initialTimeMicrosec(static_cast<int64>(time.count() * 1'000'000))
	{
		set(time);

		if (startImmediately)
		{
			start();
		}
	}

	void Timer::start()
	{
		if (!m_pausing)
		{
			return;
		}

		m_isStarted = true;

		m_pausing = false;

		m_startTimeMicrosec = Time::GetMicrosec();
	}

	int64 Timer::us() const
	{
		const int64 t = Time::GetMicrosec();

		if (!m_isStarted)
		{
			return 0;
		}

		if (m_pausing)
		{
			return Max<int64>(m_accumulationMicrosec, 0);
		}

		return Max<int64>(m_accumulationMicrosec - (t - m_startTimeMicrosec), 0);
	}

	void Timer::restart()
	{
		set(MicrosecondsF(m_initialTimeMicrosec));

		start();
	}

	void Timer::restart(const Duration& time)
	{
		set(time);

		start();
	}

	String Timer::format(const StringView format) const
	{
		return Stopwatch(remaining(), false).format(format);
	}

	bool operator <(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remaining() < time;
	}

	bool operator <=(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remaining() <= time;
	}

	bool operator >(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remaining() > time;
	}

	bool operator >=(const Timer& timer, const MicrosecondsF& time)
	{
		return timer.remaining() >= time;
	}


	bool operator <(const MicrosecondsF& time, const Timer& timer)
	{
		return time < timer.remaining();
	}

	bool operator <=(const MicrosecondsF& time, const Timer& timer)
	{
		return time <= timer.remaining();
	}

	bool operator >(const MicrosecondsF& time, const Timer& timer)
	{
		return time > timer.remaining();
	}

	bool operator >=(const MicrosecondsF& time, const Timer& timer)
	{
		return time >= timer.remaining();
	}

	void Formatter(FormatData& formatData, const Timer& value)
	{
		formatData.string.append(value.format());
	}
}
