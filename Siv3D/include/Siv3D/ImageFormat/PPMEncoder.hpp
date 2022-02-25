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
# include <Siv3D/PPMType.hpp>

namespace s3d
{
	/// @brief PPM 形式画像のエンコーダ
	class PPMEncoder : public IImageEncoder
	{
	public:

		/// @brief デフォルトの PPM フォーマット (PPMType::AsciiRGB)
		static constexpr PPMType DefaultFromat = PPMType::AsciiRGB;

		/// @brief エンコーダの対応形式 `U"PPM"` を返します。
		/// @return 文字列 `U"PPM"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief PPM 形式を示す ImageFormat を返します。
		/// @return `ImageFormat::PPM`
		[[nodiscard]]
		ImageFormat imageFormat() const noexcept override;

		/// @brief PPM 形式のファイルに想定される拡張子一覧 `{ U"ppm", U"pgm", U"pbm", U"pnm" }` を返します。
		/// @return 配列 `{ U"ppm", U"pgm", U"pbm", U"pnm" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief Image を PPM 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Image
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Image& image, FilePathView path) const override;

		/// @brief Image を PPM 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Image
		/// @param path 保存するファイルのパス
		/// @param format PPM フォーマット
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Image& image, FilePathView path, PPMType format) const;

		/// @brief Image を PPM 形式でエンコードして書き出します。
		/// @param image エンコードする Image
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Image& image, IWriter& writer) const override;

		/// @brief Image を PPM 形式でエンコードして書き出します。
		/// @param image エンコードする Image
		/// @param writer 書き出し先の IWriter インタフェース
		/// @param format PPM フォーマット
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Image& image, IWriter& writer, PPMType format) const;

		/// @brief Image を PPM 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Image
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Image& image) const override;

		/// @brief Image を PPM 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Image
		/// @param format PPM フォーマット
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Image& image, PPMType format) const;
	};
}
