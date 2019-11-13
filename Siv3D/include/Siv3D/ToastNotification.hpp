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
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	struct ToastNotificationProperty
	{
		String title;

		String message;

		FilePath imagePath;

		Array<String> actions;
	};

	enum class ToastNotificationState
	{
		None,
		
		Shown,
		
		Activated,
		
		UserCanceled,
		
		ApplicationHidden,
		
		TimedOut,
		
		Error,
	};

	using NotificationID = int64;

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows
	{
		namespace ToastNotification
		{
			[[nodiscard]] bool IsAvailable();

			NotificationID Show(const ToastNotificationProperty& prop);

			[[nodiscard]] ToastNotificationState GetState(NotificationID id);

			[[nodiscard]] Optional<size_t> GetAction(NotificationID id);

			void Hide(NotificationID id);

			void Clear();
		}
	}

# endif
}
