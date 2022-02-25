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
	/// @brief フォントのスタイル
	enum class FontStyle : uint8
	{
		/// @brief デフォルト
		Default = 0x0,

		/// @brief ボールド
		Bold = 0x01,

		/// @brief イタリック
		Italic = 0x02,

		/// @brief ボールド + イタリック
		BoldItalic = Bold | Italic,

		/// @brief ビットマップ
		Bitmap = 0x04,

		/// @brief ボールド + ビットマップ
		BoldBitmap = Bold | Bitmap,

		/// @brief イタリック + ビットマップ
		ItalicBitmap = Italic | Bitmap,

		/// @brief ボールド + イタリック + ビットマップ
		BoldItalicBitmap = Bold | Italic | Bitmap,
	};
	DEFINE_BITMASK_OPERATORS(FontStyle);
}
