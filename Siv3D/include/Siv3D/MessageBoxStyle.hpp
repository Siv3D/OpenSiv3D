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
	/// @brief メッセージボックスのスタイル
	enum class MessageBoxStyle : uint8
	{
		/// @brief 通常のスタイル
		Default,

		/// @brief 情報を伝えるスタイル
		Info,

		/// @brief 警告を伝えるスタイル
		Warning,

		/// @brief 深刻なエラーを伝えるスタイル
		Error,

		/// @brief クエスチョンマークのスタイル
		Question,
	};
}
