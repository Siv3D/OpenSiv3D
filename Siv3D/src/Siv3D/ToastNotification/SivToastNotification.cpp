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

# include <Siv3D/ToastNotification.hpp>
# include "../Siv3DEngine.hpp"
# include "IToastNotification.hpp"

# if SIV3D_PLATFORM(LINUX)
# include "ToastNotification/CToastNotification.hpp"
# endif

namespace s3d
{
# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows
	{
		namespace ToastNotification
		{
			bool IsAvailable()
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->isAvailable();
			}

			NotificationID Show(const ToastNotificationProperty& prop)
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->show(prop);
			}

			ToastNotificationState GetState(const NotificationID id)
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->getState(id);
			}

			Optional<size_t> GetAction(const NotificationID id)
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->getAction(id);
			}

			void Hide(const NotificationID id)
			{
				Siv3DEngine::Get<ISiv3DToastNotification>()->hide(id);
			}

			void Clear()
			{
				Siv3DEngine::Get<ISiv3DToastNotification>()->clear();
			}
		}
	}

# elif SIV3D_PLATFORM(LINUX)

	namespace Platform::Linux
	{
		namespace ToastNotification
		{
			bool IsAvailable()
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->isAvailable();
			}

			NotificationID Show(const ToastNotificationProperty& prop)
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->show(prop);
			}

			ToastNotificationState GetState(const NotificationID id)
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->getState(id);
			}

			Optional<size_t> GetAction(const NotificationID id)
			{
				return Siv3DEngine::Get<ISiv3DToastNotification>()->getAction(id);
			}

			void Hide(const NotificationID id)
			{
				Siv3DEngine::Get<ISiv3DToastNotification>()->hide(id);
			}

			void Clear()
			{
				Siv3DEngine::Get<ISiv3DToastNotification>()->clear();
			}

			bool SupportsActions()
			{
				CToastNotification* const pToastNotification = dynamic_cast<CToastNotification* const>(Siv3DEngine::Get<ISiv3DToastNotification>());
				return pToastNotification->supportsActions();
			}
		}
	};

# endif
}
