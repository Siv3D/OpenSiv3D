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
	/// @brief オーディオのループ位置指定
	struct AudioLoopTiming
	{
		/// @brief ループ始点サンプル位置
		uint64 beginPos = 0;

		/// @brief ループ終点サンプル位置。0 の場合はループ無し
		uint64 endPos = 0;
	};
}
