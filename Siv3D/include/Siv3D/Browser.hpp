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
# include "InputGroup.hpp"
# include "HashTable.hpp"

namespace s3d
{ 
# if SIV3D_PLATFORM(WEB)

	namespace Platform::Web
	{
		enum class KeyModifier 
		{
			_None,
			Control,
			Shift,
			ControlShift
		};

		struct BrowserKeyboardShorcut
		{ 
			Input key;
			KeyModifier modifier;
		};

		/// @brief ブラウザ上の仮想ファイルをローカルにダウンロードします。
		/// @param filePath ブラウザ上の仮想ファイルへのパス
		void DownloadFile(FilePathView filePath);

		/// @brief 仮想ファイルシステムに `path` と同名のファイルが無い場合、カレントディレクトリ基準で `path` を
		///        HTTP リクエスト経由でダウンロードし仮想ファイルシステムに追加します。これにより、当該ファイルに
		///        Siv3D の API でアクセスできるようになります。この関数を呼び出す関数は、ビルドオプションで
		///        `ASYNCIFY_ADD` への登録が必要です。その関数を呼ぶ関数も再帰的に登録が必要です。
		/// @param filePath ブラウザ上の仮想ファイルへのパス
		void FetchFile(FilePathView filePath);
	}

	namespace Platform::Web::System
	{
		/// @brief 現在のページのクエリ文字列を取得します
		/// @return 現在のページのクエリ文字列
		[[nodiscard]]
		HashTable<String, String> GetURLParameters();

		/// @brief ブラウザ側が用意しているキーボードショートカットを可能な限り無効化します
		/// @param allowList 許可するキーボードショートカットのリスト
		/// @remarks タブを閉じるなど、一部のキーボードショートカットはブラウザの制約により無効化することができません
		void DisbaleBrowserKeyboardShortcuts(const Array<BrowserKeyboardShorcut>& allowList = {});
	}

# endif
}
