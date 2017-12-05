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
}
