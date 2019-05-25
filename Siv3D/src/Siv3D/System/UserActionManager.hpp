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
# include <atomic>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	class UserActionManager
	{
	private:

		std::atomic<uint32> m_currentUserActions = { 0 };

		uint32 m_previousUserActions = 0;

		uint32 m_terminationTriggers = UserAction::Default;

	public:

		void setTerminationTriggers(const uint32 userActions)
		{
			m_terminationTriggers = userActions;
		}

		[[nodiscard]] uint32 getTerminationTriggers() const
		{
			return m_terminationTriggers;
		}

		[[nodiscard]] uint32 getPreviousUserActions() const
		{
			return m_previousUserActions;
		}

		[[nodiscard]] uint32 checkTermination()
		{
			m_previousUserActions = m_currentUserActions.exchange(0u);

			return m_previousUserActions & (UserAction::ExitFlag | m_terminationTriggers);
		}

		void logExitEvent(const uint32 exitEvent)
		{
			if (exitEvent & UserAction::CloseButtonClicked)
			{
				LOG_INFO(U"🚪 System::Update(): `UserAction::CloseButtonClicked` has occurred");
			}
			else if (exitEvent & UserAction::EscapeKeyDown)
			{
				LOG_INFO(U"🚪 System::Update(): `UserAction::EscapeKeyDown` has occurred");
			}
			else if (exitEvent & UserAction::WindowDeactivated)
			{
				LOG_INFO(U"🚪 System::Update(): `UserAction::WindowDeactivated` has occurred");
			}
			else if (exitEvent & UserAction::AnyKeyDown)
			{
				LOG_INFO(U"🚪 System::Update(): `UserAction::AnyKeyDown` has occurred");
			}
			else if (exitEvent & UserAction::MouseButtonDown)
			{
				LOG_INFO(U"🚪 System::Update(): `UserAction::MouseButtonDown` has occurred");
			}
			else if (exitEvent & UserAction::ExitFlag)
			{
				LOG_INFO(U"🚪 System::Update(): System::Exit() has been called");
			}
		}

		void reportUserActions(const uint32 userActions)
		{
			m_currentUserActions |= userActions;
		}
	};
}
