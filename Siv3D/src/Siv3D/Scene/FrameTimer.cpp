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

# include <Siv3D/Time.hpp>
# include "FrameTimer.hpp"

namespace s3d
{
	void FrameTimer::update()
	{
		const uint64 currentNanoSec = Time::GetNanosec();

		const double deltaTimeSec = m_previousFrameTimeNanosec ?
			((currentNanoSec - m_previousFrameTimeNanosec) / 1'000'000'000.0) : 0.0;

		m_deltaTimeSec = Min(deltaTimeSec, m_maxDeltaTimeSec);

		m_timeSec += m_deltaTimeSec;

		m_previousFrameTimeNanosec = currentNanoSec;
	}

	double FrameTimer::getTimeSec() const noexcept
	{
		return m_timeSec;
	}

	double FrameTimer::getDeltaTimeSec() const noexcept
	{
		return m_deltaTimeSec;
	}

	double FrameTimer::getMaxDeltaTimeSec() const noexcept
	{
		return m_maxDeltaTimeSec;
	}

	void FrameTimer::setMaxDeltaTimeSec(double timeSec) noexcept
	{
		m_deltaTimeSec = Max(timeSec, 0.0);
	}
}
