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
# include <memory>
# include "Common.hpp"
# include "Duration.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief GIF アニメーションのファイル書き出し
	class AnimatedGIFWriter
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		AnimatedGIFWriter();

		/// @brief GIF アニメーションを書き出すファイルをオープンします。
		/// @param path 書き出し先のファイルパス
		/// @param width GIF 画像の幅（ピクセル）
		/// @param height GIF 画像の高さ（ピクセル）
		/// @param dither ディザリングを適用するか
		/// @param hasAlpha 背景透過があるか
		SIV3D_NODISCARD_CXX20
		AnimatedGIFWriter(FilePathView path, int32 width, int32 height, Dither dither = Dither::No, HasAlpha hasAlpha = HasAlpha::No);

		/// @brief GIF アニメーションを書き出すファイルをオープンします。
		/// @param path 書き出し先のファイルパス
		/// @param size GIF 画像の幅と高さ（ピクセル）
		/// @param dither ディザリングを適用するか
		/// @param hasAlpha 背景透過があるか
		SIV3D_NODISCARD_CXX20
		AnimatedGIFWriter(FilePathView path, Size size, Dither dither = Dither::No, HasAlpha hasAlpha = HasAlpha::No);

		/// @brief デストラクタ
		~AnimatedGIFWriter();

		/// @brief GIF アニメーションを書き出すファイルをオープンします。
		/// @param path 書き出し先のファイルパス
		/// @param width GIF 画像の幅（ピクセル）
		/// @param height GIF 画像の高さ（ピクセル）
		/// @param dither ディザリングを適用するか
		/// @param hasAlpha 背景透過があるか
		/// @return オープンに成功した場合 true, それ以外の場合は false
		bool open(FilePathView path, int32 width, int32 height, Dither dither = Dither::No, HasAlpha hasAlpha = HasAlpha::No);

		/// @brief GIF アニメーションを書き出すファイルをオープンします。
		/// @param path 書き出し先のファイルパス
		/// @param size GIF 画像の幅と高さ（ピクセル）
		/// @param dither ディザリングを適用するか
		/// @param hasAlpha 背景透過があるか
		/// @return オープンに成功した場合 true, それ以外の場合は false
		bool open(FilePathView path, const Size& size, Dither dither = Dither::No, HasAlpha hasAlpha = HasAlpha::No);

		/// @brief アニメーション GIF の作成を終了し、保存します。
		/// @remark 新しいアニメーション GIF を作成するには、再度 open() する必要があります。
		/// @return アニメーション GIF の保存に成功したら true, 失敗したら false
		bool close();

		/// @brief 書き出し用ファイルがオープンされているかを返します。
		/// @return ファイルがオープンされている場合 true, それ以外の場合は false	
		[[nodiscard]]
		bool isOpen() const noexcept;

		/// @brief 書き出し用ファイルがオープンされているかを返します。
		/// @return ファイルがオープンされている場合 true, それ以外の場合は false	
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief フレームを書き出します。
		/// @param image 書き出すフレームの画像
		/// @param delay アニメーションの間隔
		/// @remark 画像は出力する動画の解像度と同じサイズでなければいけません。
		/// @return フレームの書き出しに成功したら true, 失敗したら false
		bool writeFrame(const Image& image, const Duration& delay = SecondsF{ 0.1 });

		/// @brief 書き出したフレームの合計数を返します。
		/// @return 書き出したフレームの合計数
		[[nodiscard]]
		size_t frameCount() const noexcept;

		/// @brief GIF 画像の幅と高さ（ピクセル）を返します。
		/// @return GIF 画像の幅と高さ（ピクセル）
		[[nodiscard]]
		Size imageSize() const noexcept;

	private:

		class AnimatedGIFWriterDetail;

		std::shared_ptr<AnimatedGIFWriterDetail> pImpl;
	};
}
