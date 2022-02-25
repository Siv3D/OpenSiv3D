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
# include "Array.hpp"
# include "String.hpp"
# include "DateTime.hpp"
# include "InputGroups.hpp"

namespace s3d
{
	class Image;
	class DynamicTexture;

	/// @brief スクリーンショットに関連する機能
	/// @remark これらの関数を呼ぶ以外にも、OS 固有のスクリーンショットのキーボード操作でスクリーンショットを自動保存します。
	namespace ScreenCapture
	{
		/// @brief 現在設定されている、スクリーンショットの保存先のディレクトリを取得します。
		/// @return スクリーンショットの保存先のディレクトリ
		[[nodiscard]]
		FilePath GetScreenshotDirectory();

		/// @brief スクリーンショットの保存先のディレクトリを変更します。
		/// @param path 新しい保存先のディレクトリ
		void SetScreenshotDirectory(FilePath&& path);

		/// @brief 現在のフレームを次の `System::Update()` でスクリーンショットとして保存します。
		/// @param path 保存するスクリーンショットのファイル名
		void SaveCurrentFrame(FilePath&& path = (DateTime::Now().format(U"yyyyMMdd-HHmmss-SSS") + U".png"));

		/// @brief 現在のフレームのスクリーンショットを、次の `System::Update()` でメモリ上に保存します。
		/// @remark 保存されたスクリーンショットは、`ScreenCapture::GetFrame()` を通して取得できます。
		void RequestCurrentFrame();

		/// @brief メモリ上に新しいスクリーンショットが保存されているかを返します。
		/// @remark 直前のフレームで `ScreenCapture::Request()` を呼んだ場合のみ true を返します。
		/// @return メモリ上に新しいスクリーンショットが保存されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool HasNewFrame();

		/// @brief メモリ上に保存されているスクリーンショットを取得します。
		/// @return メモリ上に新しいスクリーンショットが保存されている場合その画像、それ以外の場合は空の画像
		[[nodiscard]]
		const Image& GetFrame();

		/// @brief メモリ上に保存されているスクリーンショットを取得します。
		/// @param image 取得した画像のコピー先
		/// @return メモリ上に新しいスクリーンショットが保存されていて、その取得に成功した場合 true, それ以外の場合は false
		bool GetFrame(Image& image);

		/// @brief メモリ上に保存されているスクリーンショットを DynamicTexture に書き込みます。
		/// @param texture スクリーンショットの書き込み先
		/// @remark DynamicTexture はスクリーンショットと同じ解像度か、空でなければこの関数は失敗します。
		/// @return メモリ上に新しいスクリーンショットが保存されていて、そのスクリーンショットの書き込みに成功した場合 true, それ以外の場合は false
		bool GetFrame(DynamicTexture& texture);

		/// @brief スクリーンショットのショートカットキーを設定します。
		/// @remark デフォルトでは `{ KeyPrintScreen, KeyF12 }` です。
		/// @param screenshotShortcutKeys スクリーンショットのショートカットキー
		void SetShortcutKeys(const Array<InputGroup>& screenshotShortcutKeys);
	}
}
