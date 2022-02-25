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
	/// @brief 特殊フォルダ
	/// @remark `FileSystem::GetFolderPath()` で使用します。
	enum class SpecialFolder : uint8
	{
		/// @brief デスクトップ
		Desktop,

		/// @brief ドキュメント
		Documents,

		/// @brief ローカル・アプリケーション・データ（キャッシュ）
		LocalAppData,

		/// @brief ピクチャー
		Pictures,

		/// @brief ミュージック
		Music,

		/// @brief ビデオ
		Videos,

		/// @brief キャッシュ
		Caches = LocalAppData,

		/// @brief ムービー（ビデオ）
		Movies = Videos,

		/// @brief システムフォント
		SystemFonts,

		/// @brief ローカルフォント
		LocalFonts,

		/// @brief ユーザーフォント
		UserFonts,

		/// @brief ユーザープロファイル
		UserProfile,

		/// @brief アプリケーション
		ProgramFiles,
	};
}
