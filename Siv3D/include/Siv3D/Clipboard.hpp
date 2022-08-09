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
# include "String.hpp"
# include "Array.hpp"
# include "Image.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	/// @brief クリップボードに関する機能を提供します。
	namespace Clipboard
	{
		/// @brief クリップボードの内容がユーザによって変更されたかを返します。
		/// @return クリップボードの内容がユーザによって変更された場合 true, それ以外の場合は false
		[[nodiscard]]
		bool HasChanged();

		/// @brief クリップボードにあるテキストを取得します。
		/// @param text テキストの格納先
		/// @return テキストの取得に成功した場合 true, それ以外の場合は false
		bool GetText(String& text);

		/// @brief クリップボードにある画像を取得します。
		/// @param image 画像の格納先
		/// @return 画像の取得に成功した場合 true, それ以外の場合は false
		bool GetImage(Image& image);

		/// @brief クリップボードにあるファイルパスを取得します。
		/// @param paths ファイルパスの格納先
		/// @return ァイルパスの取得に成功した場合 true, それ以外の場合は false
		bool GetFilePaths(Array<FilePath>& paths);

		/// @brief クリップボードにテキストを設定します。
		/// @param text テキスト
		void SetText(const String& text);

		/// @brief クリップボードに画像を設定します。
		/// @param image 画像
		void SetImage(const Image& image);

		/// @brief クリップボードの内容を消去します。
		void Clear();
	}

# if SIV3D_PLATFORM(WEB)
	namespace Platform::Web::Clipboard 
	{
		AsyncTask<String> GetText();
	}
# endif
}
