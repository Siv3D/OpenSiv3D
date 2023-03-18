//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	/// @brief 画像アドレスモード
	enum class ImageAddressMode : uint8
	{
		/// @brief 繰り返し
		Repeat,

		/// @brief ミラーで繰り返し
		Mirror,

		/// @brief 繰り返しなし
		Clamp,

		/// @brief 繰り返しなしで範囲外は黒
		BorderBlack,

		/// @brief 繰り返しなしで範囲外は白
		BorderWhite,
	};
}
