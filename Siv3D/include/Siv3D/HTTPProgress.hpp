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
# include "HTTPAsyncStatus.hpp"
# include "Optional.hpp"

namespace s3d
{
	/// @brief HTTP 通信の進捗
	struct HTTPProgress
	{
		/// @brief 進行状況
		HTTPAsyncStatus status = HTTPAsyncStatus::None_;

		/// @brief ダウンロードしたサイズ（バイト）
		int64 downloaded_bytes = 0;

		/// @brief アップロードしたサイズ（バイト）
		int64 uploaded_bytes = 0;

		/// @brief ダウンロードするファイルの合計サイズ（バイト）。不明な場合 none
		Optional<int64> download_total_bytes;

		/// @brief アップロードするファイルの合計サイズ（バイト）。不明な場合 none
		Optional<int64> upload_total_bytes;
	};
}