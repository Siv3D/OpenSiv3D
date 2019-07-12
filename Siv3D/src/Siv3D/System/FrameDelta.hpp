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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/Scene.hpp>

namespace s3d
{
	static_assert(Scene::DefaultMaxDeltaTime > 0.0);

	class FrameDelta
	{
	private:

		double m_timeSec = 0.0;

		double m_deltaTimeSec = 0.0;

		double m_maxDeltaTimeSec = Scene::DefaultMaxDeltaTime;

		uint64 m_previousFrameTimeNanosec = 0;

	public:

		void update()
		{
			const uint64 currentNanoSec = Time::GetNanosec();

			const double deltaTimeSec = m_previousFrameTimeNanosec ?
				(currentNanoSec - m_previousFrameTimeNanosec) / 1'000'000'000.0 : 0.0;

			m_deltaTimeSec = std::min(deltaTimeSec, m_maxDeltaTimeSec);

			m_timeSec += m_deltaTimeSec;

			m_previousFrameTimeNanosec = currentNanoSec;
		}

		double getTimeSec() const noexcept
		{
			return m_timeSec;
		}

		double getDeltaTimeSec() const noexcept
		{
			return m_deltaTimeSec;
		}

		double getMaxDeltaTimeSec() const noexcept
		{
			return m_maxDeltaTimeSec;
		}

		void setMaxDeltaTimeSec(double timeSec) noexcept
		{
			m_deltaTimeSec = std::max(timeSec, 0.0);
		}
	};
}
