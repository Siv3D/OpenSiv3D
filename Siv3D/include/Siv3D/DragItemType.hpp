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
	/// @brief ドラッグするアイテムの種類
	enum class DragItemType : uint8
	{
		/// @brief ファイルパス
		FilePaths,

		/// @brief テキスト
		Text
	};
}
