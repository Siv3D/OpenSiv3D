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

namespace s3d
{
	/// @brief シーンサイズの設定
	enum class ResizeMode
	{
		/// @brief ウィンドウの実サイズに合わせる
		Actual,

		/// @brief ウィンドウの仮想サイズに合わせる
		Virtual,

		/// @brief シーンのサイズは変更しない
		Keep,
	};
}
