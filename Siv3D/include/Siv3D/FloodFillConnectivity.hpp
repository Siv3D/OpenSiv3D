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
	/// @brief 塗りつぶしの連結性
	enum class FloodFillConnectivity : uint32
	{
		/// @brief 上下左右 4 ピクセル
		Value4 = 4,

		/// @brief 周囲 8 ピクセル
		Value8 = 8,
	};
}
