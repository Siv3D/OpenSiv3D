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

# pragma once
# include <atomic>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace WindowEvent
	{
		static constexpr uint32 ExitFlag = 0x10000000;
	}

	class ExitEventManager
	{
	private:

		std::atomic<uint32> m_event = { 0 };

		uint32 m_previousEvent = 0;

		uint32 m_exitEvent = WindowEvent::Default;

	public:

		uint32 checkExitEvent()
		{
			m_previousEvent = m_event.exchange(0);

			return m_previousEvent & (WindowEvent::ExitFlag | m_exitEvent);
		}

		void reportEvent(const uint32 windowEventFlag)
		{
			m_event |= windowEventFlag;
		}

		void setExitEvent(const uint32 windowEventFlag)
		{
			m_exitEvent = windowEventFlag;
		}

		uint32 getPreviousEvent() const
		{
			return m_previousEvent;
		}
	};

	class FrameCounter
	{
	private:

		uint64 m_systemFrameCount = 0;

		int32 m_userFrameCount = 0;

	public:

		void operator ++() noexcept
		{
			++m_systemFrameCount;

			++m_userFrameCount;
		}

		uint64 getSystemFrameCount() const noexcept
		{
			return m_systemFrameCount;
		}

		int32 getUserFrameCount() const noexcept
		{
			return m_userFrameCount;
		}

		void setUserFrameCount(const int32 count) noexcept
		{
			m_userFrameCount = count;
		}
	};

	class FrameDelta
	{
	private:

		double m_currentDeltaTimeSec = 0.0;

		uint64 m_previousFrameTimeNanosec = 0;

	public:

		void update()
		{
			const uint64 currentNanoSec = Time::GetNanosec();
			
			m_currentDeltaTimeSec = m_previousFrameTimeNanosec ?
				(currentNanoSec - m_previousFrameTimeNanosec) / 1'000'000'000.0 : 0.0;
			
			m_previousFrameTimeNanosec = currentNanoSec;
		}

		double getDeltaTimeSec() const noexcept
		{
			return m_currentDeltaTimeSec;
		}
	};
}
