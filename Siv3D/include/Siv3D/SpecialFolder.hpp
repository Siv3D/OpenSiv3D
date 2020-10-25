//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	/// @brief 特殊フォルダ
	enum class SpecialFolder
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
