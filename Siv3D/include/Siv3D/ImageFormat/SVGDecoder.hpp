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

namespace s3d
{
	/// @brief SVG 形式画像データのデコーダ
	class SVGDecoder : public IImageDecoder
	{
	public:

		/// @brief デコーダの対応形式 `U"SVG"` を返します。
		/// @return 文字列 `U"SVG"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief SVG 形式を示す ImageFormat を返します。
		/// @return `ImageFormat::SVG`
		[[nodiscard]]
		ImageFormat imageFormat() const noexcept override;

		/// @brief SVG 形式の先頭データであるかを返します。
		/// @param bytes データの先頭 16 バイト
		/// @return SVG 形式と推測される場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isHeader(const uint8(&bytes)[16]) const override;

		/// @brief SVG 形式のファイルに想定される拡張子一覧 `{ U"svg" }` を返します。
		/// @return 配列 `{ U"svg" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief SVG 形式の画像ファイルから画像情報を取得します。
		/// @param path 画像ファイルのパス
		/// @return 画像情報。取得に失敗した場合は none
		[[nodiscard]]
		Optional<ImageInfo> getImageInfo(FilePathView path) const override;

		/// @brief SVG 形式の画像データから画像情報を取得します。
		/// @param reader 画像データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 画像情報。取得に失敗した場合は none
		[[nodiscard]]
		Optional<ImageInfo> getImageInfo(IReader& reader, FilePathView pathHint = {}) const override;

		/// @brief SVG 形式の画像ファイルをデコードして Image を作成します。
		/// @param path 画像ファイルのパス
		/// @return 作成した Image
		[[nodiscard]]
		Image decode(FilePathView path) const override;

		/// @brief SVG 形式の画像データをデコードして Image を作成します。
		/// @param reader 画像データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 作成した Image
		[[nodiscard]]
		Image decode(IReader& reader, FilePathView pathHint = {}) const override;
	};
}
