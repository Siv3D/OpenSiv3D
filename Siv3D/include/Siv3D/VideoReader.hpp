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
	/// @brief 動画ファイルの読み込み
	/// @remark バックグラウンドで次のフレームを先読みしているため、`setCurrentFrameIndex()` を使わず順番にフレームを読み込むのが効率的です。
	class VideoReader
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		VideoReader();

		/// @brief 動画ファイルをオープンします。
		/// @param path 動画ファイルのパス
		/// @remark プラットフォームによって対応している動画ファイル形式が異なります。
		SIV3D_NODISCARD_CXX20
		explicit VideoReader(FilePathView path);

		/// @brief 動画ファイルをオープンします。
		/// @param path 動画ファイルのパス
		/// @remark すでに動画ファイルをオープンしている場合、それが先にクローズされます。
		/// @return 対応している動画ファイル形式で、ファイルのオープンに成功した場合 true, それ以外の場合は false
		bool open(FilePathView path);

		/// @brief 動画ファイルをクローズします。
		void close();

		/// @brief ファイルがオープンしているかを返します。
		/// @remark この関数が true を返せば動画ファイルを読み込めます。
		/// @return ファイルがオープンしている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const noexcept;

		/// @brief ファイルがオープンしているかを返します。
		/// @remark この関数が true を返せば動画ファイルを読み込めます。
		/// @remark `isOpen()` と同じです。
		/// @return ファイルがオープンしている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 動画ファイルから 1 フレーム読み込み、読み込み位置を 1 フレーム進めます。
		/// @param image 読み込んだ画像の格納先
		/// @remark image は動画の解像度に合わせてリサイズされます。image があらかじめ動画と同じ解像度になっているとリサイズが不要です。
		/// @remark したがって、動画の一連のフレームを読み込むときには、同じ Image オブジェクトを使い回すのが効率的です。
		/// @return 新しいフレームの読み込みに成功した場合 true, それ以外の場合は false
		bool readFrame(Image& image);

		/// @brief 動画の解像度を返します。
		/// @return 動画の解像度
		[[nodiscard]]
		Size getSize() const noexcept;

		/// @brief 動画の FPS を返します。
		/// @return 動画の FPS
		[[nodiscard]] 
		double getFPS() const noexcept;

		/// @brief 動画の長さ（秒）を返します。
		/// @return 動画の長さ（秒）
		[[nodiscard]]
		double getLengthSec() const;

		/// @brief 次に読み込むフレームのインデックスを変更します。
		/// @param index 変更後のインデックス
		void setCurrentFrameIndex(size_t index);

		/// @brief 次に読み込むフレームのインデックスを返します。
		/// @return 次に読み込むフレームのインデックス
		[[nodiscard]] 
		size_t getCurrentFrameIndex() const noexcept;

		/// @brief 次に読み込むフレームの再生位置（秒）を返します。
		/// @return 次に読み込むフレームの再生位置（秒）
		[[nodiscard]]
		double getPosSec() const;

		/// @brief 動画のフレーム数を返します。
		/// @return 動画のフレーム数
		[[nodiscard]]
		size_t getFrameCount() const noexcept;

		/// @brief 動画の 1 フレームあたりの時間（秒）を返します。
		/// @remark `(1.0 / getFPS())` です。
		/// @return 動画の 1 フレームあたりの時間（秒）
		[[nodiscard]] 
		double getFrameDeltaSec() const noexcept;

		/// @brief 動画の再生位置を [0.0, 1.0] で返します。
		/// @remark `((double)getCurrentFrameIndex() / getFrameCount())` です。
		/// @return 動画の再生位置 [0.0, 1.0]
		[[nodiscard]]
		double getProgress() const noexcept;

		/// @brief 動画のフレームが終端に到達したかを返します。
		/// @return 動画のフレームが終端に到達した場合 true, それ以外の場合は false
		[[nodiscard]]
		bool reachedEnd() const noexcept;

		/// @brief 動画ファイルのフルパスを返します。
		/// @return 動画ファイルのフルパス
		[[nodiscard]]
		const FilePath& path() const noexcept;

	private:

		class VideoReaderDetail;

		std::shared_ptr<VideoReaderDetail> pImpl;
	};
}
