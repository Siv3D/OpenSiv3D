//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/StringView.hpp>

namespace s3d
{
	// エンジン未初期化でも使えるメッセージボックス
	namespace FreestandingMessageBox
	{
		/// @brief メッセージボックスを表示します。
		/// @param text メッセージボックスに表示するテキスト
		void ShowInfo(StringView text);

		/// @brief エラーメッセージボックスを表示します。
		/// @param text メッセージボックスに表示するテキスト
		void ShowError(StringView text);
	}
}
