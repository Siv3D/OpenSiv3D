//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Optional.hpp"
# include "AsyncTask.hpp"
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

			/// @brief トースト通知を発行します。
			/// @param item 発行するトースト通知
			/// @return 発行したトースト通知の ID
			ToastNotificationID Show(const ToastNotificationItem& item);

			/// @brief トースト通知の状態を取得します。
			/// @param id トースト通知の ID
			/// @return トースト通知の状態
			[[nodiscard]]
			ToastNotificationState GetState(ToastNotificationID id);

			/// @brief トースト通知の結果を取得します。
			/// @param id トースト通知の ID
			/// @return ユーザが選んだ選択のインデックス。選択されていない場合は none
			[[nodiscard]]
			Optional<size_t> GetAction(ToastNotificationID id);

			/// @brief 指定したトースト通知を非表示にします。
			/// @param id トースト通知の ID
			void Hide(ToastNotificationID id);

			/// @brief すべてのトースト通知を削除します。
			void Clear();
		}
	}

# elif SIV3D_PLATFORM(WEB)

	namespace Platform::Web
	{
		namespace Notification
		{
			/// @brief トースト通知が可能な OS であるかを返します。
			/// @return トースト通知が可能な場合 true, それ以外の場合は false
			[[nodiscard]]
			bool IsAvailable();

			AsyncTask<bool> RequestPermission();

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
