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

namespace s3d
{
	/// @brief シーンの自動リサイズモード
	enum class ResizeMode : uint8
	{
		/// @brief シーンのサイズをウィンドウの実サイズに合わせる
		Actual,

		/// @brief シーンのサイズをウィンドウの仮想サイズに合わせる（デフォルト）
		Virtual,

		/// @brief シーンのサイズは変更しない
		Keep,
	};
}
