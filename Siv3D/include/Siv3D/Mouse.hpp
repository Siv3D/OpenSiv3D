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
# include "Array.hpp"
# include "InputGroups.hpp"

namespace s3d
{
	namespace Mouse
	{
		/// @brief 現在のフレームで何らかの入力操作があるマウスのボタンの一覧を取得します。
		/// @return 現在のフレームで何らかの入力操作があるマウスのボタンの一覧
		[[nodiscard]]
		const Array<Input>& GetAllInputs() noexcept;

		/// @brief マウスホイールのスクロール量を返します。
		/// @return マウスホイールのスクロール量
		[[nodiscard]]
		double Wheel() noexcept;

		/// @brief マウスの水平ホイールのスクロール量を返します。
		/// @return マウスの水平ホイールのスクロール量
		[[nodiscard]]
		double WheelH() noexcept;
	}

	/// @brief マウス左ボタン
	inline constexpr Input MouseL{ InputDeviceType::Mouse, 0 };

	/// @brief マウス右ボタン
	inline constexpr Input MouseR{ InputDeviceType::Mouse, 1 };

	/// @brief マウス中央ボタン
	inline constexpr Input MouseM{ InputDeviceType::Mouse, 2 };

	/// @brief マウス X1 ボタン
	inline constexpr Input MouseX1{ InputDeviceType::Mouse, 3 };

	/// @brief マウス X2 ボタン
	inline constexpr Input MouseX2{ InputDeviceType::Mouse, 4 };

	/// @brief マウス X3 ボタン
	inline constexpr Input MouseX3{ InputDeviceType::Mouse, 5 };

	/// @brief マウス X4 ボタン
	inline constexpr Input MouseX4{ InputDeviceType::Mouse, 6 };

	/// @brief マウス X5 ボタン
	inline constexpr Input MouseX5{ InputDeviceType::Mouse, 7 };
}
