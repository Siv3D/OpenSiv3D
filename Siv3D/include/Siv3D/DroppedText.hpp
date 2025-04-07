﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief ドロップされたテキストの情報
	struct DroppedText
	{
		/// @brief テキスト
		String text;

		/// @brief ドロップされた位置（クライアント座標）
		Point pos;

		/// @brief ドロップされた時刻（ミリ秒）
		/// @remark `Time::GetMillisec()` で取得する時刻と比較できます。
		uint64 timeMillisec;
	};
}
