//-----------------------------------------------
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

namespace s3d
{
	/// @brief ダウンロードの進行状況
	enum class HTTPAsyncStatus : uint8
	{
		/// @brief ダウンロードするものが無い
		None_,

		/// @brief ダウンロード中
		Downloading,

		/// @brief ダウンロード失敗
		Failed,

		/// @brief ダウンロードがキャンセルされた
		Canceled,

		/// @brief ダウンロード完了
		Succeeded,
	};
}