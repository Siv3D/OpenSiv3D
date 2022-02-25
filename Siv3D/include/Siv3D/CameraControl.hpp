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
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>

namespace s3d
{
	/// @brief カメラの操作方法
	enum class CameraControl : uint8
	{
		/// @brief 手動操作無し
		None_		= 0,

		/// @brief WASD キーによる上下左右移動
		WASDKeys	= 0b0001,

		/// @brief ↑↓ キーによるズーム倍率変更
		UpDownKeys	= 0b0010,

		/// @brief 右クリック・ドラッグによる移動
		RightClick	= 0b0100,

		/// @brief マウスホイールによるズーム倍率変更
		Wheel		= 0b1000,

		/// @brief WASD↑↓ キーによる上下左右移動とズーム倍率変更
		Keyboard	= (WASDKeys | UpDownKeys),

		/// @brief 右クリック・ドラッグによる移動とマウスホイールによるズーム倍率変更
		Mouse		= (RightClick | Wheel),

		/// @brief キーボードとマウスによる移動、ズーム倍率変更
		Default		= (Keyboard | Mouse),
	};
	DEFINE_BITMASK_OPERATORS(CameraControl);
}
