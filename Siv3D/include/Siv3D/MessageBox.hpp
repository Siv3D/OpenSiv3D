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
# include "StringView.hpp"
# include "MessageBoxResult.hpp"
# include "MessageBoxStyle.hpp"

namespace s3d
{
	namespace System
	{
		/// @brief 「OK」ボタンを持つメッセージボックスを表示する。
		/// @param text 本文
		/// @param style スタイル
		/// @remark この関数はユーザがボタンを押すかメッセージボックスを閉じるまで制御を返しません。
		/// @return `MessageBoxResult::OK`
		MessageBoxResult MessageBoxOK(StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		/// @brief 「OK」ボタンを持つメッセージボックスを表示する。
		/// @param title メッセージボックスのタイトル
		/// @param text 本文
		/// @param style スタイル
		/// @remark この関数はユーザがボタンを押すかメッセージボックスを閉じるまで制御を返しません。
		/// @return `MessageBoxResult::OK`
		MessageBoxResult MessageBoxOK(StringView title, StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		/// @brief 「OK」「キャンセル」ボタンを持つメッセージボックスを表示する。
		/// @param text 本文
		/// @param style スタイル
		/// @remark この関数はユーザがボタンを押すかメッセージボックスを閉じるまで制御を返しません。
		/// @return `MessageBoxResult::OK` または `MessageBoxResult::Cancel`
		[[nodiscard]]
		MessageBoxResult MessageBoxOKCancel(StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		/// @brief 「OK」「キャンセル」ボタンを持つメッセージボックスを表示する。
		/// @param title メッセージボックスのタイトル
		/// @param text 本文
		/// @param style スタイル
		/// @remark この関数はユーザがボタンを押すかメッセージボックスを閉じるまで制御を返しません。
		/// @return `MessageBoxResult::OK` または `MessageBoxResult::Cancel`
		[[nodiscard]]
		MessageBoxResult MessageBoxOKCancel(StringView title, StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		/// @brief 「はい」「いいえ」ボタンを持つメッセージボックスを表示する。
		/// @param text 本文
		/// @param style スタイル
		/// @remark この関数はユーザがボタンを押すまで制御を返しません。
		/// @return `MessageBoxResult::Yes` または `MessageBoxResult::No`
		[[nodiscard]]
		MessageBoxResult MessageBoxYesNo(StringView text, MessageBoxStyle style = MessageBoxStyle::Default);

		/// @brief 「はい」「いいえ」ボタンを持つメッセージボックスを表示する。
		/// @param title メッセージボックスのタイトル
		/// @param text 本文
		/// @param style スタイル
		/// @remark この関数はユーザがボタンを押すまで制御を返しません。
		/// @return `MessageBoxResult::Yes` または `MessageBoxResult::No`
		[[nodiscard]]
		MessageBoxResult MessageBoxYesNo(StringView title, StringView text, MessageBoxStyle style = MessageBoxStyle::Default);
	}
}
