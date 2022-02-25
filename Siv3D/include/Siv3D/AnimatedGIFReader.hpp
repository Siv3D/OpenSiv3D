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
# include "Array.hpp"
# include "IReader.hpp"
# include "Image.hpp"

namespace s3d
{
	/// @brief GIF アニメーションの読み込み
	class AnimatedGIFReader
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		AnimatedGIFReader();

		/// @brief GIF アニメーションファイルを読み込みます。
		/// @param path 画像ファイルのパス
		SIV3D_NODISCARD_CXX20
		explicit AnimatedGIFReader(FilePathView path);

		/// @brief GIF アニメーションデータを読み込みます。
		/// @param reader 画像データの IReader インタフェース
		SIV3D_NODISCARD_CXX20
		explicit AnimatedGIFReader(IReader&& reader);

		/// @brief デストラクタ
		~AnimatedGIFReader();

		/// @brief GIF アニメーションファイルを読み込みます。
		/// @param path 画像ファイルのパス
		/// @remark 以前に読み込んだGIF アニメーションデータは破棄されます。
		/// @return ファイルの読み込みに成功した場合 true, それ以外の場合は false
		bool open(FilePathView path);

		/// @brief GIF アニメーションデータを読み込みます。
		/// @param reader 画像データの IReader インタフェース
		/// @remark 以前に読み込んだGIF アニメーションデータは破棄されます。
		/// @return データの読み込みに成功した場合 true, それ以外の場合は false
		bool open(IReader&& reader);

		/// @brief 読み込んだ GIF アニメーションデータを破棄します。
		void close();

		/// @brief GIF アニメーションデータが読み込まれているかを返します。
		/// @return GIF アニメーションデータが読み込まれている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const noexcept;

		/// @brief GIF アニメーションデータが読み込まれているかを返します。
		/// @remark `isOpen()` と同じです。
		/// @return GIF アニメーションデータが読み込まれている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief GIF アニメーションデータをデコードして、結果を配列に格納します。
		/// @param images 結果のフレーム (Image) を格納する配列
		/// @param delaysMillisec フレーム時間（ミリ秒）を格納する配列
		/// @return デコードに成功した場合 true, それ以外の場合は false
		bool read(Array<Image>& images, Array<int32>& delaysMillisec) const;

		/// @brief GIF アニメーションデータをデコードして、結果を配列に格納します。
		/// @param images 結果のフレーム (Image) を格納する配列
		/// @param delaysMillisec フレーム時間（ミリ秒）を格納する配列
		/// @param durationMillisec フレームの合計時間（ミリ秒）を格納する配列
		/// @remark durationMillisec は `delaysMillisec.sum()` と同じです。
		/// @return デコードに成功した場合 true, それ以外の場合は false
		bool read(Array<Image>& images, Array<int32>& delaysMillisec, int32& durationMillisec) const;

		/// @brief 時間を GIF アニメーションのフレームインデックスに変換します。
		/// @param timeMillisec 時間（ミリ秒）
		/// @param delaysMillisec GIF アニメーションのフレーム時間（ミリ秒）を格納した配列
		/// @return 時間に対応する GIF アニメーションのフレーム位置
		[[nodiscard]]
		static size_t MillisecToIndex(int64 timeMillisec, const Array<int32>& delaysMillisec) noexcept;

		/// @brief 時間を GIF アニメーションのフレームインデックスに変換します。
		/// @param timeMillisec 時間（ミリ秒）
		/// @param delaysMillisec GIF アニメーションのフレーム時間（ミリ秒）を格納した配列
		/// @param durationMillisec フレームの合計時間（ミリ秒）
		/// @return 時間に対応する GIF アニメーションのフレームインデックス
		[[nodiscard]]
		static size_t MillisecToIndex(int64 timeMillisec, const Array<int32>& delaysMillisec, int32 durationMillisec) noexcept;

		/// @brief 時間を GIF アニメーションのフレームインデックスに変換します。
		/// @param timeSec 時間（秒）
		/// @param delaysMillisec GIF アニメーションのフレーム時間（ミリ秒）を格納した配列
		/// @return 時間に対応する GIF アニメーションのフレームインデックス
		[[nodiscard]]
		static size_t GetFrameIndex(double timeSec, const Array<int32>& delaysMillisec) noexcept;

		/// @brief 時間を GIF アニメーションのフレームインデックスに変換します。
		/// @param timeSec 時間（秒）
		/// @param delaysMillisec GIF アニメーションのフレーム時間（ミリ秒）を格納した配列
		/// @param durationMillisec フレームの合計時間（ミリ秒）
		/// @return 時間に対応する GIF アニメーションのフレームインデックス
		[[nodiscard]]
		static size_t GetFrameIndex(double timeSec, const Array<int32>& delaysMillisec, int32 durationMillisec) noexcept;

	private:

		class AnimatedGIFReaderDetail;

		std::shared_ptr<AnimatedGIFReaderDetail> pImpl;
	};
}
