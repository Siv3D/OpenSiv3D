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
	/// @brief ファイルの操作
	enum class FileAction: uint8
	{
		/// @brief 不明な操作
		Unknown,

		/// @brief ファイルが新規追加された
		Added,

		/// @brief ファイルが削除された
		Removed,

		/// @brief ファイルの内容が更新された
		Modified,
	};
}
