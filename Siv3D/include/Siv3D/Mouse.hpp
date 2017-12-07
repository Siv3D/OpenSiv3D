//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Key.hpp"

namespace s3d
{
	/// <summary>
	/// マウス左ボタン
	/// </summary>
	constexpr Key MouseL{ InputDevice::Mouse, 0 };

	/// <summary>
	/// マウス右ボタン
	/// </summary>
	constexpr Key MouseR{ InputDevice::Mouse, 1 };

	/// <summary>
	/// マウス中央ボタン
	/// </summary>
	constexpr Key MouseM{ InputDevice::Mouse, 2 };

	/// <summary>
	/// マウス X1 ボタン
	/// </summary>
	constexpr Key MouseX1{ InputDevice::Mouse, 3 };

	/// <summary>
	/// マウス X2 ボタン
	/// </summary>
	constexpr Key MouseX2{ InputDevice::Mouse, 4 };

	/// <summary>
	/// マウス X3 ボタン
	/// </summary>
	constexpr Key MouseX3{ InputDevice::Mouse, 5 };

	/// <summary>
	/// マウス X4 ボタン
	/// </summary>
	constexpr Key MouseX4{ InputDevice::Mouse, 6 };

	/// <summary>
	/// マウス X5 ボタン
	/// </summary>
	constexpr Key MouseX5{ InputDevice::Mouse, 7 };
	
	namespace Mouse
	{
		/// <summary>
		/// マウスホイールのスクロール量を返します。
		/// </summary>
		/// <returns>
		/// マウスホイールのスクロール量
		/// </returns>
		double Wheel();
		
		/// <summary>
		/// マウスの水平ホイールのスクロール量を返します。
		/// </summary>
		/// <returns>
		/// マウスの水平ホイールのスクロール量
		/// </returns>
		double WheelH();
	}
}
