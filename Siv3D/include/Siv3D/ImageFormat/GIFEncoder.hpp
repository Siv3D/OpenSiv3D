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

namespace s3d
{
	/// @brief GIF 形式画像のエンコーダ
	class GIFEncoder : public IImageEncoder
	{
	public:

		/// @brief エンコーダの対応形式 `U"GIF"` を返します。
		/// @return 文字列 `U"GIF"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief GIF 形式を示す ImageFormat を返します。
		/// @return `ImageFormat::GIF`
		[[nodiscard]]
		ImageFormat imageFormat() const noexcept override;

		/// @brief GIF 形式のファイルに想定される拡張子一覧 `{ U"gif" }` を返します。
		/// @return 配列 `{ U"gif" }` 
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;
		
		/// @brief Image を GIF 形式でエンコードしてファイルに保存します。
		/// @param image エンコードする Image
		/// @param path 保存するファイルのパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(const Image& image, FilePathView path) const override;
		
		/// @brief Image を GIF 形式でエンコードして書き出します。
		/// @param image エンコードする Image
		/// @param writer 書き出し先の IWriter インタフェース
		/// @return 書き出しに成功した場合 true, それ以外の場合は false
		bool encode(const Image& image, IWriter& writer) const override;

		/// @brief Image を GIF 形式でエンコードした結果を Blob で返します。
		/// @param image エンコードする Image
		/// @return エンコード結果
		[[nodiscard]]
		Blob encode(const Image& image) const override;
	};
}
