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
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief トースト通知の設定
	struct ToastNotificationItem
	{
		/// @brief 通知のタイトル
		String title;

		/// @brief 通知するメッセージ
		String message;

		/// @brief 表示する画像のファイルパス
		FilePath imagePath;

		/// @brief ユーザの選択肢
		Array<String> actions;

		/// @brief 効果音を利用できる場合, 効果音を再生するか
		/// @remark Windows 版でのみ有効です
		bool audio = true;
	};
}
