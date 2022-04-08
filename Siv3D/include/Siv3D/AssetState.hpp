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
	/// @brief アセットのロード状況
	enum class AssetState : uint8
	{
		/// @brief ロードを開始していない
		Uninitialized,

		/// @brief 非同期ロード中
		AsyncLoading,

		/// @brief ロード済み
		Loaded,

		/// @brief ロードに失敗
		Failed,
	};
}
