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
# include "DragItemType.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief ドラッグの状態
	struct DragStatus
	{
		/// @brief ドラッグしているアイテムの種類
		DragItemType itemType;

		/// @brief ドラッグ中のカーソルの位置（クライアント座標）
		Point cursorPos;
	};
}
