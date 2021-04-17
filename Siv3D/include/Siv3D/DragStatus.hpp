//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
	struct DragStatus
	{
		/// @brief ドラッグしているアイテムの種類
		DragItemType itemType;

		/// @brief ドラッグ中のカーソルの位置（クライアント座標）
		Point cursorPos;
	};
}
