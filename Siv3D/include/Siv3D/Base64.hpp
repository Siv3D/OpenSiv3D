//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Blob.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	namespace Base64
	{
		/// @brief データを Base64 エンコードします。
		/// @param data 入力データ
		/// @param size 入力データのサイズ（バイト）
		/// @return Base64 エンコードされた入力データ
		[[nodiscard]]
		String Encode(const void* data, size_t size);

		/// @brief データを Base64 エンコードし、dst に格納します。
		/// @param data 入力データ
		/// @param size 入力データのサイズ（バイト）
		/// @param dst Base64 エンコードされた入力データの格納先
		void Encode(const void* data, size_t size, String& dst);

		/// @brief データを Base64 エンコードし、dst に格納します。
		/// @param data 入力データ
		/// @param size 入力データのサイズ（バイト）
		/// @param dst Base64 エンコードされた入力データの格納先
		void Encode(const void* data, size_t size, std::string& dst);

		/// @brief Base64 データをデコードします。
		/// @param base64 入力 Base64
		/// @param skipValidation 妥当性をチェックするかどうか
		/// @throw Error 妥当性チェックが有効で、不正な入力が見つかった場合
		/// @return デコードされたデータ
		[[nodiscard]]
		Blob Decode(StringView base64, SkipValidation skipValidation = SkipValidation::No);

		/// @brief Base64 データをデコードします。
		/// @param base64 入力 Base64
		/// @param skipValidation 妥当性をチェックするかどうか
		/// @throw Error 妥当性チェックが有効で、不正な入力が見つかった場合
		/// @return デコードされたデータ
		[[nodiscard]]
		Blob Decode(std::string_view base64, SkipValidation skipValidation = SkipValidation::No);
	}
}
