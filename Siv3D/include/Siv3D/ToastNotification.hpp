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
	using ToastNotificationID = int64;

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows
	{
		namespace ToastNotification
		{
			/// @brief トースト通知が可能な OS であるかを返します。
			/// @return トースト通知が可能な場合 true, それ以外の場合は false
			[[nodiscard]]
			bool IsAvailable();

			ToastNotificationID Show(const ToastNotificationItem& item);

			[[nodiscard]]
			ToastNotificationState GetState(ToastNotificationID id);

			[[nodiscard]]
			Optional<size_t> GetAction(ToastNotificationID id);

			void Hide(ToastNotificationID id);

			void Clear();
		}
	}

# endif
}
