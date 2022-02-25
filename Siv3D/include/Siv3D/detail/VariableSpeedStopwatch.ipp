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
	inline VariableSpeedStopwatch::VariableSpeedStopwatch(const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: VariableSpeedStopwatch{ 1.0, startImmediately, pSteadyClock } {}

	inline VariableSpeedStopwatch::VariableSpeedStopwatch(const double speed, const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: m_speed{ speed }
		, m_pSteadyClock{ pSteadyClock }
	{
		if (startImmediately)
		{
			start();
		}
	}

	inline VariableSpeedStopwatch::VariableSpeedStopwatch(const Duration& startTime, const double speed, const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: m_speed{ speed }
		, m_pSteadyClock{ pSteadyClock }
	{
		set(startTime);

		if (startImmediately)
		{
			start();
		}
	}

	inline bool VariableSpeedStopwatch::isStarted() const noexcept
	{
		return m_isStarted;
	}

	inline bool VariableSpeedStopwatch::isPaused() const noexcept
	{
		return (m_isStarted && m_pausing);
	}

	inline bool VariableSpeedStopwatch::isRunning() const noexcept
	{
		return (m_isStarted && not m_pausing);
	}

	inline void VariableSpeedStopwatch::start()
	{
		if (not m_pausing)
		{
			return;
		}

		m_isStarted = true;

		m_pausing = false;

		m_lastTimeNanosec = ISteadyClock::GetNanosec(m_pSteadyClock);
	}

	inline void VariableSpeedStopwatch::pause()
	{
		m_accumulationNanosec = ns();

		m_pausing = true;
	}

	inline void VariableSpeedStopwatch::resume()
	{
		if (not isPaused())
		{
			return;
		}

		start();
	}

	inline void VariableSpeedStopwatch::reset() noexcept
	{
		m_accumulationNanosec = 0;

		m_isStarted = false;

		m_pausing = true;
	}

	inline void VariableSpeedStopwatch::restart()
	{
		reset();

		start();
	}

	inline void VariableSpeedStopwatch::set(const Duration& time)
	{
		m_isStarted = true;

		m_accumulationNanosec = static_cast<int64>(time.count() * (1000LL * 1000LL * 1000LL));

		m_lastTimeNanosec = ISteadyClock::GetNanosec(m_pSteadyClock);
	}

	inline void VariableSpeedStopwatch::setSpeed(const double speed)
	{
		assert(0.0 <= speed);

		if (speed == m_speed)
		{
			return;
		}

		m_accumulationNanosec = ns();

		m_speed = speed;
	}

	inline double VariableSpeedStopwatch::getSpeed() const noexcept
	{
		return m_speed;
	}

	inline int32 VariableSpeedStopwatch::d() const
	{
		return static_cast<int32>(d64());
	}

	inline int64 VariableSpeedStopwatch::d64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	inline double VariableSpeedStopwatch::dF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	inline int32 VariableSpeedStopwatch::h() const
	{
		return static_cast<int32>(h64());
	}

	inline int64 VariableSpeedStopwatch::h64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL * 60LL * 60LL));
	}

	inline double VariableSpeedStopwatch::hF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL * 60LL));
	}

	inline int32 VariableSpeedStopwatch::min() const
	{
		return static_cast<int32>(min64());
	}

	inline int64 VariableSpeedStopwatch::min64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL * 60LL));
	}

	inline double VariableSpeedStopwatch::minF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL));
	}

	inline int32 VariableSpeedStopwatch::s() const
	{
		return static_cast<int32>(s64());
	}

	inline int64 VariableSpeedStopwatch::s64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL));
	}

	inline double VariableSpeedStopwatch::sF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL));
	}

	inline int32 VariableSpeedStopwatch::ms() const
	{
		return static_cast<int32>(ms64());
	}

	inline int64 VariableSpeedStopwatch::ms64() const
	{
		return (ns() / (1000LL * 1000LL));
	}

	inline double VariableSpeedStopwatch::msF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL));
	}

	inline int64 VariableSpeedStopwatch::us() const
	{
		return us64();
	}

	inline int64 VariableSpeedStopwatch::us64() const
	{
		return (ns() / (1000LL));
	}

	inline double VariableSpeedStopwatch::usF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL));
	}

	inline Duration VariableSpeedStopwatch::elapsed() const
	{
		return SecondsF{ sF() };
	}

	inline String VariableSpeedStopwatch::format(const StringView format) const
	{
		return FormatTime(elapsed(), format);
	}

	inline int64 VariableSpeedStopwatch::ns() const
	{
		const int64 t = ISteadyClock::GetNanosec(m_pSteadyClock);

		if (not m_isStarted)
		{
			return 0;
		}

		if (m_pausing)
		{
			return m_accumulationNanosec;
		}

		const int64 delta = static_cast<int64>((t - m_lastTimeNanosec) * m_speed);

		m_accumulationNanosec += delta;

		m_lastTimeNanosec = t;

		return m_accumulationNanosec;
	}
}
