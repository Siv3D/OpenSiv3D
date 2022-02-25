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
	/// @brief 電源の接続状態
	enum class ACLineStatus : uint8
	{
		/// @brief 不明
		Unknown,

		/// @brief 電源に接続されていない
		Offline,

		/// @brief 電源に接続されている
		Online,
	};
}
