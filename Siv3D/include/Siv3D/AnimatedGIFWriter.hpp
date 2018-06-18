//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Duration.hpp"

namespace s3d
{
	class AnimatedGIFWriter
	{
	private:

		class AnimatedGIFWriterDetail;

		std::shared_ptr<AnimatedGIFWriterDetail> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		AnimatedGIFWriter();

		AnimatedGIFWriter(const FilePath& path, int32 width, int32 height, bool dither = false, bool hasAlpha = false);

		AnimatedGIFWriter(const FilePath& path, const Size& size, bool dither = false, bool hasAlpha = false);

		/// <summary>
		/// アニメーション GIF の作成を終了し、保存します。
		/// </summary>
		~AnimatedGIFWriter();

		bool open(const FilePath& path, int32 width, int32 height, bool dither = false, bool hasAlpha = false);

		bool open(const FilePath& path, const Size& size, bool dither = false, bool hasAlpha = false);

		/// <summary>
		/// アニメーション GIF の作成を終了し、保存します。
		/// </summary>
		/// <remarks>
		/// 新しいアニメーション GIF を作成するには、再度 open() する必要があります。
		/// </remarks>
		/// <returns>
		/// アニメーション GIF の保存に成功したら true, 失敗したら false
		/// </returns>
		bool close();

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool isOpened() const noexcept;

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] explicit operator bool() const noexcept;

		/// <summary>
		/// フレームを書き出します。
		/// </summary>
		/// <param name="image">
		/// 書き出すフレームの画像
		/// </param>
		/// <param name="delay">
		/// アニメーションの間隔
		/// </param>
		/// <remarks>
		/// image は動画と同じサイズでなければいけません。
		/// </remarks>
		/// <returns>
		/// フレームの書き出しに成功したら true, 失敗したら false
		/// </returns>
		[[nodiscard]] bool writeFrame(const Image& image, const Duration& delay = SecondsF(0.1));

		[[nodiscard]] size_t frameCount() const noexcept;

		[[nodiscard]] Size imageSize() const noexcept;
	};
}
