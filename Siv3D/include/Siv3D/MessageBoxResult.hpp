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
	/// @brief メッセージボックスの結果
	enum class MessageBoxResult : uint8
	{
		/// @brief [OK] が押された
		OK,

		/// @brief [キャンセル] が押されたか、メッセージボックスが閉じられた
		Cancel,

		/// @brief [はい] が押された
		Yes,

		/// @brief [いいえ] が押された
		No,
	};
}
