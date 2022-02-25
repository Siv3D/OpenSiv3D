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
# include <Siv3D/IImageEncoder.hpp>
# include <Siv3D/WebPMethod.hpp>
# include <Siv3D/PredefinedYesNo.hpp>

namespace s3d
{
	/// @brief WebP 形式画像のエンコーダ
	class WebPEncoder : public IImageEncoder
	{
	public:

		/// @brief デフォルトのエンコード品質 (90.0)
		static constexpr double DefaultQuality = 90.0;

		/// @brief エンコーダの対応形式 `U"WebP"` を返します。
		/// @return 文字列 `U"WebP"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief WebP 形式を示す ImageFormat を返します。
		/// @return `ImageFormat::WebP`
		[[nodiscard]]
		ImageFormat imageFormat() const noexcept override;

		/// @brief WebP 形式のファイルに想定される拡張子一覧 `{ U"webp" }` を返します。
		/// @return 配列 `{ U"webp" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief Image を WebP 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Image
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Image& image, FilePathView path) const override;
		
		/// @brief Image を WebP 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Image
		/// @param path 保存するファイルのパス
		/// @param lossless ロスレス形式にするか
		/// @param quality エンコード品質 [0, 100], 低いと低画質高圧縮
		/// @param method エンコード手法
		/// @return 
		bool save(const Image& image, FilePathView path, Lossless lossless, double quality, WebPMethod method) const;

		/// @brief Image を WebP 形式でエンコードして書き出します。
		/// @param image エンコードする Image
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Image& image, IWriter& writer) const override;

		/// @brief Image を WebP 形式でエンコードして書き出します。
		/// @param image エンコードする Image
		/// @param writer 書き出し先の IWriter インタフェース
		/// @param lossless ロスレス形式にするか
		/// @param quality エンコード品質 [0, 100], 低いと低画質高圧縮
		/// @param method エンコード手法
		/// @return 
		bool encode(const Image& image, IWriter& writer, Lossless lossless, double quality, WebPMethod method) const;

		/// @brief Image を WebP 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Image
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Image& image) const override;

		/// @brief Image を WebP 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Image
		/// @param lossless ロスレス形式にするか
		/// @param quality エンコード品質 [0, 100], 低いと低画質高圧縮
		/// @param method エンコード手法
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Image& image, Lossless lossless, double quality, WebPMethod method) const;
	};
}
