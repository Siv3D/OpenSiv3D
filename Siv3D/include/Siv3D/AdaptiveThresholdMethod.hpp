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
	/// @brief 適応的閾値処理において閾値を計算する方法
	/// @remark `Image::adaptiveThreshold()` などで使います。
	enum class AdaptiveThresholdMethod : uint32
	{
		/// @brief 周辺の値 - 定数 C
		Mean,

		/// @brief 周辺のガウス分布による重みづけの合計 - 定数 C
		Gaussian,
	};
}
