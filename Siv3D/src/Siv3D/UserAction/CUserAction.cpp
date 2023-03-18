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

# include <Siv3D/EngineLog.hpp>
# include "CUserAction.hpp"

namespace s3d
{
	void CUserAction::setTerminationTriggers(const uint32 userActionFlags) noexcept
	{
		m_terminationTriggers = userActionFlags;
	}

	uint32 CUserAction::getTerminationTriggers() noexcept
	{
		return m_terminationTriggers;
	}

	uint32 CUserAction::getPreviousUserActions() noexcept
	{
		return m_previousUserActions;
	}

	void CUserAction::reportUserActions(const uint32 userActions) noexcept
	{
		m_currentUserActions |= userActions;
	}

	bool CUserAction::terminationTriggered() noexcept
	{
		m_previousUserActions = m_currentUserActions.exchange(UserAction::NoAction);

		if (const uint32 triggerdActions = (m_previousUserActions & (UserAction::SystemExitCalled | m_terminationTriggers)))
		{
			logTermination(triggerdActions);

			return true;
		}
		else
		{
			return false;
		}
	}

	void CUserAction::logTermination(const uint32 triggerdActions)
	{
		if (triggerdActions & UserAction::CloseButtonClicked)
		{
			LOG_INFO(U"🚪 System::Update(): `UserAction::CloseButtonClicked` has occurred");
		}
		else if (triggerdActions & UserAction::EscapeKeyDown)
		{
			LOG_INFO(U"🚪 System::Update(): `UserAction::EscapeKeyDown` has occurred");
		}
		else if (triggerdActions & UserAction::WindowDeactivated)
		{
			LOG_INFO(U"🚪 System::Update(): `UserAction::WindowDeactivated` has occurred");
		}
		else if (triggerdActions & UserAction::AnyKeyDown)
		{
			LOG_INFO(U"🚪 System::Update(): `UserAction::AnyKeyDown` has occurred");
		}
		else if (triggerdActions & UserAction::MouseButtonDown)
		{
			LOG_INFO(U"🚪 System::Update(): `UserAction::MouseButtonDown` has occurred");
		}
		else if (triggerdActions & UserAction::SystemExitCalled)
		{
			LOG_INFO(U"🚪 System::Update(): System::Exit() has called");
		}
	}
}
