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
# include <Siv3D/IImageDecoder.hpp>
# include <Siv3D/Grid.hpp>

namespace s3d
{
	/// @brief PNG 形式画像データのデコーダ
	class PNGDecoder : public IImageDecoder
	{
	public:

		/// @brief デコーダの対応形式 `U"PNG"` を返します。
		/// @return 文字列 `U"PNG"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief PNG 形式を示す ImageFormat を返します。
		/// @return `ImageFormat::PNG`
		[[nodiscard]]
		ImageFormat imageFormat() const noexcept override;

		/// @brief PNG 形式の先頭データであるかを返します。
		/// @param bytes データの先頭 16 バイト
		/// @return PNG 形式と推測される場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isHeader(const uint8(&bytes)[16]) const override;

		/// @brief PNG 形式のファイルに想定される拡張子一覧 `{ U"png" }` を返します。
		/// @return 配列 `{ U"png" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief PNG 形式の画像ファイルから画像情報を取得します。
		/// @param path 画像ファイルのパス
		/// @return 画像情報。取得に失敗した場合は none
		[[nodiscard]]
		Optional<ImageInfo> getImageInfo(FilePathView path) const override;

		/// @brief PNG 形式の画像データから画像情報を取得します。
		/// @param reader 画像データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 画像情報。取得に失敗した場合は none
		[[nodiscard]]
		Optional<ImageInfo> getImageInfo(IReader& reader, FilePathView pathHint = {}) const override;

		/// @brief PNG 形式の画像ファイルをデコードして Image を作成します。
		/// @param path 画像ファイルのパス
		/// @return 作成した Image
		[[nodiscard]]
		Image decode(FilePathView path) const override;

		/// @brief PNG 形式の画像データをデコードして Image を作成します。
		/// @param reader 画像データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 作成した Image
		[[nodiscard]]
		Image decode(IReader& reader, FilePathView pathHint = {}) const override;

		/// @brief 16-bit グレースケール PNG の画像ファイルをデコードして Grid を作成します。
		/// @param path 画像ファイルのパス
		/// @return 作成した Grid
		[[nodiscard]]
		Grid<uint16> decodeGray16(FilePathView path) const override;

		/// @brief 16-bit グレースケール PNG の画像データをデコードして Grid を作成します。
		/// @param reader 画像データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 作成した Grid
		[[nodiscard]]
		Grid<uint16> decodeGray16(IReader& reader, FilePathView pathHint = {}) const override;
	};
}
