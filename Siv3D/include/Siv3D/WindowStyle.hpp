//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	/// @brief ウィンドウスタイル
	enum class WindowStyle
	{
		/// @brief サイズ変更できない枠付きのウィンドウ
		Fixed,

		/// @brief サイズ変更できる枠付きのウィンドウ
		Sizable,

		/// @brief 枠の無いウィンドウ
		Frameless,
	};
}
