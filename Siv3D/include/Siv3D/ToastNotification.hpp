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

# pragma once
# include "Common.hpp"
# include "Optional.hpp"
# include "ToastNotificationItem.hpp"
# include "ToastNotificationState.hpp"

namespace s3d
{
	using NotificationID = int64;

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows
	{
		namespace ToastNotification
		{
			[[nodiscard]]
			bool IsAvailable();

			NotificationID Show(const ToastNotificationItem& item);

			[[nodiscard]]
			ToastNotificationState GetState(NotificationID id);

			[[nodiscard]]
			Optional<size_t> GetAction(NotificationID id);

			void Hide(NotificationID id);

			void Clear();
		}
	}

# endif
}
