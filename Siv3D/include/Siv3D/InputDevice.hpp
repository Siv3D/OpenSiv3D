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
	/// @brief 入力デバイスの種類
	enum class InputDeviceType : uint8
	{
		/// @brief 未定義
		Undefined,

		/// @brief キーボード
		Keyboard,

		/// @brief マウス
		Mouse,

		/// @brief ゲームパッド
		Gamepad,

		/// @brief XInput 対応ゲームコントローラー
		XInput,
	};
}
