//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	namespace ScreenCapture
	{
		void SaveCurrentFrame();

		void SaveCurrentFrame(const FilePath& path);

		/// <summary>
		/// 現在のフレームのスクリーンショットをメモリ上に保存します。
		/// </summary>
		/// <remarks>
		/// 撮影されたスクリーンショットは次のフレームで ScreenCapture::GetFrame() を通して取得できます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void RequestCurrentFrame();

		/// <summary>
		/// 新しいスクリーンショットがあるかを返します。
		/// </summary>
		/// <remarks>
		/// 直前のフレームで ScreenCapture::Request() を呼び、
		/// 現在のフレームで ScreenCapture::GetFrmae() を呼んでいないときに true を返します。
		/// </remarks>
		/// <returns>
		/// 新しいスクリーンショットがある場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool HasNewFrame();

		/// <summary>
		/// メモリ上に保存されたスクリーンショットを取得します。
		/// </summary>
		/// <remarks>
		/// 以前のフレームで Graphics::ReceiveScreenCapture()　が呼ばれていないといけません。
		/// </remarks>
		/// <returns>
		/// 保存されているスクリーンショット。スクリーンショットが保存されていない場合は空の画像
		/// </returns>
		[[nodiscard]] const Image& GetFrame();

		/// <summary>
		/// スクリーンショットを取得します。
		/// </summary>
		/// <param name="image">
		/// スクリーンショットのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetFrame(Image& image);

		/// <summary>
		/// スクリーンショットを取得します。
		/// </summary>
		/// <param name="texture">
		/// スクリーンショットのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetFrame(DynamicTexture& texture);
	}
}
