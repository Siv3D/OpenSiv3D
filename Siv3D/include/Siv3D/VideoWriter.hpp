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
# include "StringView.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 動画ファイルの書き出し
	class VideoWriter
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		VideoWriter();

		SIV3D_NODISCARD_CXX20
		explicit VideoWriter(FilePathView path, const Size& size, double fps);

		bool open(FilePathView path, const Size& size, double fps);

		/// @brief 動画ファイルをクローズします。
		void close();

		/// @brief ファイルがオープンしているかを返します。
		/// @return ファイルがオープンしている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const noexcept;

		/// @brief ファイルがオープンしているかを返します。
		/// @remark `isOpen()` と同じです。
		/// @return ファイルがオープンしている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 動画ファイルにフレームを書き出します。
		/// @param image 書き出すフレーム
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool writeFrame(const Image& image);

		/// @brief 動画の解像度を返します。
		/// @return 動画の解像度
		[[nodiscard]]
		Size getSize() const noexcept;

		/// @brief 動画の FPS を返します。
		/// @return 動画の FPS
		[[nodiscard]]
		double getFPS() const noexcept;

		/// @brief 動画ファイルのフルパスを返します。
		/// @return 動画ファイルのフルパス
		[[nodiscard]]
		const FilePath& path() const noexcept;

	private:

		class VideoWriterDetail;

		std::shared_ptr<VideoWriterDetail> pImpl;
	};
}
