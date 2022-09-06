//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Timer.hpp>
# include <Siv3D/ISteadyClock.hpp>
# include <Siv3D/FormatData.hpp>

namespace s3d
{
	Timer::Timer(const Duration& duration, const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: m_durationMicrosec{ static_cast<int64>(duration.count() * 1'000'000) }
		, m_remainingMicrosec{ m_durationMicrosec }
		, m_pSteadyClock{ pSteadyClock }
	{
		if (startImmediately)
		{
			start();
		}
	}

	bool Timer::isStarted() const noexcept
	{
		return m_isStarted;
	}

	bool Timer::isPaused() const noexcept
	{
		return (m_isStarted && m_pausing);
	}

	bool Timer::isRunning() const noexcept
	{
		return (m_isStarted && not m_pausing);
	}

	bool Timer::reachedZero() const
	{
		return (us() == 0);
	}

	void Timer::start()
	{
		if (m_isStarted && (not m_pausing))
		{
			return;
		}

		m_isStarted = true;

		m_pausing = false;

		m_startTimeMicrosec = ISteadyClock::GetMicrosec(m_pSteadyClock);
	}

	void Timer::pause()
	{
		m_remainingMicrosec = us();

		m_pausing = true;
	}

	void Timer::resume()
	{
		if (not isPaused())
		{
			return;
		}

		start();
	}

	void Timer::reset() noexcept
	{
		m_remainingMicrosec = m_durationMicrosec;

		m_isStarted = false;

		m_pausing = false;
	}

	void Timer::restart()
	{
		setRemaining(MicrosecondsF(m_durationMicrosec));

		start();
	}

	void Timer::restart(const Duration& duration)
	{
		reset();

		set(duration);

		start();
	}

	void Timer::set(const Duration& duration)
	{
		m_durationMicrosec = static_cast<int64>(duration.count() * 1'000'000);

		m_remainingMicrosec = m_durationMicrosec;

		m_startTimeMicrosec = ISteadyClock::GetMicrosec(m_pSteadyClock);
	}

	void Timer::setRemaining(const Duration& remaining)
	{
		m_remainingMicrosec = static_cast<int64>(remaining.count() * (1000LL * 1000LL));

		m_startTimeMicrosec = ISteadyClock::GetMicrosec(m_pSteadyClock);
	}

	int32 Timer::d() const
	{
		return static_cast<int32>(d64());
	}

	int64 Timer::d64() const
	{
		return (us() / (1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	double Timer::dF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	int32 Timer::h() const
	{
		return static_cast<int32>(h64());
	}

	int64 Timer::h64() const
	{
		return (us() / (1000LL * 1000LL * 60LL * 60LL));
	}

	double Timer::hF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL));
	}

	int32 Timer::min() const
	{
		return static_cast<int32>(min64());
	}

	int64 Timer::min64() const
	{
		return (us() / (1000LL * 1000LL * 60LL));
	}

	double Timer::minF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL));
	}

	int32 Timer::s() const
	{
		return static_cast<int32>(s64());
	}

	int64 Timer::s64() const
	{
		return (us() / (1000LL * 1000LL));
	}

	double Timer::sF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL));
	}

	int32 Timer::ms() const
	{
		return static_cast<int32>(ms64());
	}

	int64 Timer::ms64() const
	{
		return (us() / (1000LL));
	}

	double Timer::msF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL));
	}

	int64 Timer::us() const
	{
		const int64 t = ISteadyClock::GetMicrosec(m_pSteadyClock);

		if (not m_isStarted)
		{
			return m_durationMicrosec;
		}

		if (m_pausing)
		{
			return Max<int64>(m_remainingMicrosec, 0);
		}

		return Max<int64>(m_remainingMicrosec - (t - m_startTimeMicrosec), 0);
	}

	int64 Timer::us64() const
	{
		return us();
	}

	double Timer::usF() const
	{
		return static_cast<double>(us());
	}

	Duration Timer::duration() const
	{
		return SecondsF{ m_durationMicrosec / static_cast<double>(1000LL * 1000LL) };
	}

	Duration Timer::remaining() const
	{
		return SecondsF{ sF() };
	}

	double Timer::progress1_0() const
	{
		if (m_durationMicrosec == 0)
		{
			return 0.0;
		}
		else
		{
			return (static_cast<double>(us()) / m_durationMicrosec);
		}
	}

	double Timer::progress0_1() const
	{
		return (1.0 - progress1_0());
	}

	String Timer::format(const StringView format) const
	{
		return FormatTime(remaining(), format);
	}

	void Formatter(FormatData& formatData, const Timer& value)
	{
		formatData.string.append(value.format());
	}
}
