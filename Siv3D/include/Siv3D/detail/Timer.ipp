//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Timer::Timer(const Duration& startRemaining, const bool startImmediately, ISteadyClock* pSteadyClock)
		: m_initialTimeMicrosec(static_cast<int64>(startRemaining.count() * 1'000'000))
		, m_pSteadyClock(pSteadyClock)
	{
		setRemaining(startRemaining);

		if (startImmediately)
		{
			start();
		}
	}

	inline bool Timer::isStarted() const
	{
		return m_isStarted;
	}

	inline bool Timer::isPaused() const
	{
		return (m_isStarted && m_pausing);
	}

	inline bool Timer::isRunning() const
	{
		return (m_isStarted && not m_pausing);
	}

	inline bool Timer::reachedZero() const
	{
		return (us() == 0);
	}

	inline void Timer::start()
	{
		if (not m_pausing)
		{
			return;
		}

		m_isStarted = true;

		m_pausing = false;

		m_startTimeMicrosec = ISteadyClock::GetMicrosec(m_pSteadyClock);
	}

	inline void Timer::pause()
	{
		m_remainingMicrosec = us();

		m_pausing = true;
	}

	inline void Timer::resume()
	{
		if (not isPaused())
		{
			return;
		}

		start();
	}

	inline void Timer::restart()
	{
		setRemaining(MicrosecondsF(m_initialTimeMicrosec));

		start();
	}

	inline void Timer::restart(const Duration& startRemaining)
	{
		setRemaining(startRemaining);

		start();
	}

	inline void Timer::setRemaining(const Duration& remaining)
	{
		m_isStarted = true;

		m_remainingMicrosec = static_cast<int64>(remaining.count() * (1000LL * 1000LL));

		m_startTimeMicrosec = ISteadyClock::GetMicrosec(m_pSteadyClock);
	}

	inline int32 Timer::d() const
	{
		return static_cast<int32>(d64());
	}

	inline int64 Timer::d64() const
	{
		return (us() / (1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	inline double Timer::dF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	inline int32 Timer::h() const
	{
		return static_cast<int32>(h64());
	}

	inline int64 Timer::h64() const
	{
		return (us() / (1000LL * 1000LL * 60LL * 60LL));
	}

	inline double Timer::hF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL));
	}

	inline int32 Timer::min() const
	{
		return static_cast<int32>(min64());
	}

	inline int64 Timer::min64() const
	{
		return (us() / (1000LL * 1000LL * 60LL));
	}

	inline double Timer::minF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL));
	}

	inline int32 Timer::s() const
	{
		return static_cast<int32>(s64());
	}

	inline int64 Timer::s64() const
	{
		return (us() / (1000LL * 1000LL));
	}

	inline double Timer::sF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL));
	}

	inline int32 Timer::ms() const
	{
		return static_cast<int32>(ms64());
	}

	inline int64 Timer::ms64() const
	{
		return (us() / (1000LL));
	}

	inline double Timer::msF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL));
	}

	inline int64 Timer::us() const
	{
		const int64 t = ISteadyClock::GetMicrosec(m_pSteadyClock);

		if (not m_isStarted)
		{
			return 0;
		}

		if (m_pausing)
		{
			return Max<int64>(m_remainingMicrosec, 0);
		}

		return Max<int64>(m_remainingMicrosec - (t - m_startTimeMicrosec), 0);
	}

	inline int64 Timer::us64() const
	{
		return us();
	}

	inline double Timer::usF() const
	{
		return static_cast<double>(us());
	}

	inline Duration Timer::duration() const
	{
		return SecondsF{ m_initialTimeMicrosec / static_cast<double>(1000LL * 1000LL) };
	}

	inline Duration Timer::remaining() const
	{
		return SecondsF{ sF() };
	}

	inline double Timer::progress1_0() const
	{
		return (static_cast<double>(us()) / m_initialTimeMicrosec);
	}

	inline double Timer::progress0_1() const
	{
		return (1.0 - progress1_0());
	}

	inline String Timer::format(const StringView format) const
	{
		return FormatTime(remaining(), format);
	}
}
