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
	/// @brief マウスカーソルの形状
	enum class CursorStyle : uint8
	{
		/// @brief 矢印
		Arrow,

		/// @brief I 形
		IBeam,

		/// @brief 十字型
		Cross,

		/// @brief 手のアイコン
		Hand,

		/// @brief 禁止のアイコン
		NotAllowed,

		/// @brief 上下のリサイズ
		ResizeUpDown,

		/// @brief 左右のリサイズ
		ResizeLeftRight,

		/// @brief 左上-右下のリサイズ
		ResizeNWSE,

		/// @brief 右上-左下のリサイズ
		ResizeNESW,

		/// @brief 上下左右方向のリサイズ
		ResizeAll,

		/// @brief 非表示
		Hidden,

		/// @brief デフォルト（矢印）
		Default = Arrow,
	};
}
