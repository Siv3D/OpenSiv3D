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

# pragma once

namespace s3d
{
	inline Stopwatch::Stopwatch(const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: m_pSteadyClock{ pSteadyClock }
	{
		if (startImmediately)
		{
			start();
		}
	}

	inline Stopwatch::Stopwatch(const Duration& startTime, const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: m_pSteadyClock{ pSteadyClock }
	{
		set(startTime);

		if (startImmediately)
		{
			start();
		}
	}

	inline bool Stopwatch::isStarted() const noexcept
	{
		return m_isStarted;
	}

	inline bool Stopwatch::isPaused() const noexcept
	{
		return (m_isStarted && m_pausing);
	}

	inline bool Stopwatch::isRunning() const noexcept
	{
		return (m_isStarted && not m_pausing);
	}

	inline void Stopwatch::start()
	{
		if (not m_pausing)
		{
			return;
		}

		m_isStarted = true;

		m_pausing = false;

		m_startTimeMicrosec = ISteadyClock::GetMicrosec(m_pSteadyClock);
	}

	inline void Stopwatch::pause()
	{
		m_accumulationMicrosec = us();

		m_pausing = true;
	}

	inline void Stopwatch::resume()
	{
		if (not isPaused())
		{
			return;
		}

		start();
	}

	inline void Stopwatch::reset() noexcept
	{
		m_accumulationMicrosec = 0;

		m_isStarted = false;

		m_pausing = true;
	}

	inline void Stopwatch::restart()
	{
		reset();

		start();
	}

	inline void Stopwatch::set(const Duration& time)
	{
		m_isStarted = true;

		m_accumulationMicrosec = static_cast<int64>(time.count() * (1000LL * 1000LL));

		m_startTimeMicrosec = ISteadyClock::GetMicrosec(m_pSteadyClock);
	}

	inline int32 Stopwatch::d() const
	{
		return static_cast<int32>(d64());
	}

	inline int64 Stopwatch::d64() const
	{
		return (us() / (1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	inline double Stopwatch::dF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	inline int32 Stopwatch::h() const
	{
		return static_cast<int32>(h64());
	}

	inline int64 Stopwatch::h64() const
	{
		return (us() / (1000LL * 1000LL * 60LL * 60LL));
	}

	inline double Stopwatch::hF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL));
	}

	inline int32 Stopwatch::min() const
	{
		return static_cast<int32>(min64());
	}

	inline int64 Stopwatch::min64() const
	{
		return (us() / (1000LL * 1000LL * 60LL));
	}

	inline double Stopwatch::minF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL));
	}

	inline int32 Stopwatch::s() const
	{
		return static_cast<int32>(s64());
	}

	inline int64 Stopwatch::s64() const
	{
		return (us() / (1000LL * 1000LL));
	}

	inline double Stopwatch::sF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL));
	}

	inline int32 Stopwatch::ms() const
	{
		return static_cast<int32>(ms64());
	}

	inline int64 Stopwatch::ms64() const
	{
		return (us() / (1000LL));
	}

	inline double Stopwatch::msF() const
	{
		return static_cast<double>(us() / static_cast<double>(1000LL));
	}

	inline int64 Stopwatch::us() const
	{
		const int64 t = ISteadyClock::GetMicrosec(m_pSteadyClock);

		if (not m_isStarted)
		{
			return 0;
		}

		if (m_pausing)
		{
			return m_accumulationMicrosec;
		}

		return m_accumulationMicrosec + (t - m_startTimeMicrosec);
	}

	inline int64 Stopwatch::us64() const
	{
		return us();
	}

	inline double Stopwatch::usF() const
	{
		return static_cast<double>(us());
	}

	inline Duration Stopwatch::elapsed() const
	{
		return SecondsF{ sF() };
	}

	inline String Stopwatch::format(const StringView format) const
	{
		return FormatTime(elapsed(), format);
	}
}
