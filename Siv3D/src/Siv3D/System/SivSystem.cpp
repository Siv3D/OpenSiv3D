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

# include <Siv3D/System.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3DEngine.hpp>
# include "ISystem.hpp"

namespace s3d
{
	namespace System
	{
		bool Update()
		{
			return Siv3DEngine::Get<ISiv3DSystem>()->update();
		}

		void Exit()
		{
			Siv3DEngine::Get<ISiv3DSystem>()->reportUserActions(UserAction::ExitFlag);
		}

		void SetTerminationTriggers(const uint32 userActionFlags)
		{
			Siv3DEngine::Get<ISiv3DSystem>()->setTerminationTriggers(userActionFlags);
		}

		uint32 GetTerminationTriggers()
		{
			return Siv3DEngine::Get<ISiv3DSystem>()->getTerminationTriggers();
		}

		uint32 GetUserActions()
		{
			return Siv3DEngine::Get<ISiv3DSystem>()->getUserActions();
		}

		void Sleep(const Duration& duration)
		{
			Sleep(static_cast<int32>(duration.count() * 1000));
		}
	}
}
