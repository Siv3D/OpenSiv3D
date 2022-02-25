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
	/// @brief バッテリーの残量
	enum class BatteryStatus : uint8
	{
		/// @brief 不明
		Unknown,

		/// @brief 高
		High,

		/// @brief 中
		Middle,

		/// @brief 低
		Low,

		/// @brief 残りわずか
		Critical,

		/// @brief バッテリー非搭載
		NoBattery,
	};
}
