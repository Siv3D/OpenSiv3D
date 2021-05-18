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
# include "StringView.hpp"
# include "MessageBoxResult.hpp"
# include "MessageBoxStyle.hpp"

namespace s3d
{
	namespace System
	{
		/// @brief 「OK」というボタンを持つメッセージボックスを表示する。
		/// @param text 本文
		/// @param style スタイル
		/// @return ユーザのアクション
		MessageBoxResult MessageBoxOK(StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		/// @brief 「OK」というボタンを持つメッセージボックスを表示する。
		/// @param title メッセージボックスのタイトル
		/// @param text 本文
		/// @param style スタイル
		/// @return ユーザのアクション
		MessageBoxResult MessageBoxOK(StringView title, StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		[[nodiscard]]
		MessageBoxResult MessageBoxOKCancel(StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		[[nodiscard]]
		MessageBoxResult MessageBoxOKCancel(StringView title, StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		[[nodiscard]]
		MessageBoxResult MessageBoxYesNo(StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		[[nodiscard]]
		MessageBoxResult MessageBoxYesNo(StringView title, StringView text, MessageBoxStyle style = MessageBoxStyle::Default);
	}
}
