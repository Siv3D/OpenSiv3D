//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Duration.hpp"

namespace s3d
{
	class AnimatedGIFWriter
	{
	public:

		AnimatedGIFWriter();

		AnimatedGIFWriter(FilePathView path, int32 width, int32 height, bool dither = false, bool hasAlpha = false);

		AnimatedGIFWriter(FilePathView path, Size size, bool dither = false, bool hasAlpha = false);

		~AnimatedGIFWriter();

		bool open(FilePathView path, int32 width, int32 height, bool dither = false, bool hasAlpha = false);

		bool open(FilePathView path, const Size& size, bool dither = false, bool hasAlpha = false);

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

		[[nodiscard]]
		size_t frameCount() const noexcept;

		[[nodiscard]]
		Size imageSize() const noexcept;

	private:

		class AnimatedGIFWriterDetail;

		std::shared_ptr<AnimatedGIFWriterDetail> pImpl;
	};
}
