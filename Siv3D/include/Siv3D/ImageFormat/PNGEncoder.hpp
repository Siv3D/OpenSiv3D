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
# include <Siv3D/PNGFilter.hpp>
# include <Siv3D/Grid.hpp>

namespace s3d
{
	/// @brief PNG 形式画像のエンコーダ
	class PNGEncoder : public IImageEncoder
	{
	public:

		/// @brief デフォルトの PNG フィルタ (PNGFilter::Default)
		static constexpr PNGFilter DefaultFilter = PNGFilter::Default;

		/// @brief エンコーダの対応形式 `U"PNG"` を返します。
		/// @return 文字列 `U"PNG"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief PNG 形式を示す ImageFormat を返します。
		/// @return `ImageFormat::PNG`
		[[nodiscard]]
		ImageFormat imageFormat() const noexcept override;

		/// @brief PNG 形式のファイルに想定される拡張子一覧 `{ U"png" }` を返します。
		/// @return 配列 `{ U"png" }` 
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief Image を PNG 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Image
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Image& image, FilePathView path) const override;

		/// @brief Image を PNG 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Image
		/// @param path 保存するファイルのパス
		/// @param filter 使用するフィルタ
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Image& image, FilePathView path, PNGFilter filter) const;

		/// @brief 16-bit グレースケールデータ (Grid) を PNG 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Grid
		/// @param path 保存するファイルのパス
		/// @param filter 使用するフィルタ
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Grid<uint16>& image, FilePathView path, PNGFilter filter = DefaultFilter) const;

		/// @brief Image を PNG 形式でエンコードして書き出します。
		/// @param image エンコードする Image
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Image& image, IWriter& writer) const override;

		/// @brief Image を PNG 形式でエンコードして書き出します。
		/// @param image エンコードする Image
		/// @param writer 書き出し先の IWriter インタフェース
		/// @param filter 使用するフィルタ
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Image& image, IWriter& writer, PNGFilter filter) const;

		/// @brief 16-bit グレースケールデータ (Grid) を PNG 形式でエンコードして書き出します。
		/// @param image エンコードする Grid
		/// @param writer 書き出し先の IWriter インタフェース
		/// @param filter 使用するフィルタ
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Grid<uint16>& image, IWriter& writer, PNGFilter filter = DefaultFilter) const;

		/// @brief Image を PNG 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Image
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Image& image) const override;

		/// @brief Image を PNG 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Image
		/// @param filter 使用するフィルタ
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Image& image, PNGFilter filter) const;

		/// @brief 16-bit グレースケールデータ (Grid) を PNG 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Grid
		/// @param filter 使用するフィルタ
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Grid<uint16>& image, PNGFilter filter = DefaultFilter) const;
	};
}
