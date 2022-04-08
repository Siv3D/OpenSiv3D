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

namespace s3d
{
	/// @brief トースト通知の状態
	enum class ToastNotificationState : uint8
	{
		/// @brief 無効
		None_,
		
		/// @brief 表示されている
		Shown,

		/// @brief ユーザによってアクティベートされた
		Activated,

		/// @brief ユーザによってキャンセルされた
		UserCanceled,

		/// @brief アプリケーションによって非表示にされた
		ApplicationHidden,

		/// @brief タイムアウトした
		TimedOut,

		/// @brief エラーが発生した
		Error,
	};
}
