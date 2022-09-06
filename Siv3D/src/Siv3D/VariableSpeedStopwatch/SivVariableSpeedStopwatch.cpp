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

# include <Siv3D/VariableSpeedStopwatch.hpp>
# include <Siv3D/ISteadyClock.hpp>
# include <Siv3D/FormatData.hpp>

namespace s3d
{
	VariableSpeedStopwatch::VariableSpeedStopwatch(const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: VariableSpeedStopwatch{ 1.0, startImmediately, pSteadyClock } {}

	VariableSpeedStopwatch::VariableSpeedStopwatch(const double speed, const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: m_speed{ speed }
		, m_pSteadyClock{ pSteadyClock }
	{
		if (startImmediately)
		{
			start();
		}
	}

	VariableSpeedStopwatch::VariableSpeedStopwatch(const Duration& startTime, const double speed, const StartImmediately startImmediately, ISteadyClock* pSteadyClock)
		: m_speed{ speed }
		, m_pSteadyClock{ pSteadyClock }
	{
		set(startTime);

		if (startImmediately)
		{
			start();
		}
	}

	bool VariableSpeedStopwatch::isStarted() const noexcept
	{
		return m_isStarted;
	}

	bool VariableSpeedStopwatch::isPaused() const noexcept
	{
		return (m_isStarted && m_pausing);
	}

	bool VariableSpeedStopwatch::isRunning() const noexcept
	{
		return (m_isStarted && not m_pausing);
	}

	void VariableSpeedStopwatch::start()
	{
		if (not m_pausing)
		{
			return;
		}

		m_isStarted = true;

		m_pausing = false;

		m_lastTimeNanosec = ISteadyClock::GetNanosec(m_pSteadyClock);
	}

	void VariableSpeedStopwatch::pause()
	{
		m_accumulationNanosec = ns();

		m_pausing = true;
	}

	void VariableSpeedStopwatch::resume()
	{
		if (not isPaused())
		{
			return;
		}

		start();
	}

	void VariableSpeedStopwatch::reset() noexcept
	{
		m_accumulationNanosec = 0;

		m_isStarted = false;

		m_pausing = true;
	}

	void VariableSpeedStopwatch::restart()
	{
		reset();

		start();
	}

	void VariableSpeedStopwatch::set(const Duration& time)
	{
		m_isStarted = true;

		m_accumulationNanosec = static_cast<int64>(time.count() * (1000LL * 1000LL * 1000LL));

		m_lastTimeNanosec = ISteadyClock::GetNanosec(m_pSteadyClock);
	}

	void VariableSpeedStopwatch::setSpeed(const double speed)
	{
		assert(0.0 <= speed);

		if (speed == m_speed)
		{
			return;
		}

		m_accumulationNanosec = ns();

		m_speed = speed;
	}

	double VariableSpeedStopwatch::getSpeed() const noexcept
	{
		return m_speed;
	}

	int32 VariableSpeedStopwatch::d() const
	{
		return static_cast<int32>(d64());
	}

	int64 VariableSpeedStopwatch::d64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	double VariableSpeedStopwatch::dF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL * 60LL * 24LL));
	}

	int32 VariableSpeedStopwatch::h() const
	{
		return static_cast<int32>(h64());
	}

	int64 VariableSpeedStopwatch::h64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL * 60LL * 60LL));
	}

	double VariableSpeedStopwatch::hF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL * 60LL));
	}

	int32 VariableSpeedStopwatch::min() const
	{
		return static_cast<int32>(min64());
	}

	int64 VariableSpeedStopwatch::min64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL * 60LL));
	}

	double VariableSpeedStopwatch::minF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL * 60LL));
	}

	int32 VariableSpeedStopwatch::s() const
	{
		return static_cast<int32>(s64());
	}

	int64 VariableSpeedStopwatch::s64() const
	{
		return (ns() / (1000LL * 1000LL * 1000LL));
	}

	double VariableSpeedStopwatch::sF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL * 1000LL));
	}

	int32 VariableSpeedStopwatch::ms() const
	{
		return static_cast<int32>(ms64());
	}

	int64 VariableSpeedStopwatch::ms64() const
	{
		return (ns() / (1000LL * 1000LL));
	}

	double VariableSpeedStopwatch::msF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL * 1000LL));
	}

	int64 VariableSpeedStopwatch::us() const
	{
		return us64();
	}

	int64 VariableSpeedStopwatch::us64() const
	{
		return (ns() / (1000LL));
	}

	double VariableSpeedStopwatch::usF() const
	{
		return static_cast<double>(ns() / static_cast<double>(1000LL));
	}

	Duration VariableSpeedStopwatch::elapsed() const
	{
		return SecondsF{ sF() };
	}

	String VariableSpeedStopwatch::format(const StringView format) const
	{
		return FormatTime(elapsed(), format);
	}

	int64 VariableSpeedStopwatch::ns() const
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

	void Formatter(FormatData& formatData, const VariableSpeedStopwatch& value)
	{
		formatData.string.append(value.format());
	}
}
