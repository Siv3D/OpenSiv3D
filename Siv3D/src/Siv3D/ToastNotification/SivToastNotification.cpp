//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ToastNotification.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/ToastNotification/IToastNotification.hpp>

namespace s3d
{
# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows
	{
		namespace ToastNotification
		{
			bool IsAvailable()
			{
				return SIV3D_ENGINE(ToastNotification)->isAvailable();
			}

			NotificationID Show(const ToastNotificationItem& item)
			{
				return SIV3D_ENGINE(ToastNotification)->show(item);
			}

			ToastNotificationState GetState(const NotificationID id)
			{
				return SIV3D_ENGINE(ToastNotification)->getState(id);
			}

			Optional<size_t> GetAction(const NotificationID id)
			{
				return SIV3D_ENGINE(ToastNotification)->getAction(id);
			}

			void Hide(const NotificationID id)
			{
				SIV3D_ENGINE(ToastNotification)->hide(id);
			}

			void Clear()
			{
				SIV3D_ENGINE(ToastNotification)->clear();
			}
		}
	}

# endif
}
