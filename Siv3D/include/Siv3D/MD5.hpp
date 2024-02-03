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
# include "MD5Value.hpp"
# include "Blob.hpp"

namespace s3d
{
	namespace MD5
	{
		/// @brief バイナリデータから MD5 ハッシュを計算します。
		/// @param data データの先頭ポインタ
		/// @param size データのサイズ（バイト）
		/// @return 計算された MD5 ハッシュ
		[[nodiscard]]
		MD5Value FromBinary(const void* const data, size_t size);

		/// @brief バイナリデータから MD5 ハッシュを計算します。
		/// @param blob バイナリデータ
		/// @return 計算された MD5 ハッシュ
		[[nodiscard]]
		MD5Value FromBinary(const Blob& blob);

		/// @brief 文字列 (UTF-32) から MD5 ハッシュを計算します。
		/// @param view 文字列 (UTF-32)
		/// @return 計算された MD5 ハッシュ
		[[nodiscard]]
		MD5Value FromText(StringView view);

		/// @brief 文字列 (UTF-8) から MD5 ハッシュを計算します。
		/// @param view 文字列 (UTF-8)
		/// @return 計算された MD5 ハッシュ
		[[nodiscard]]
		MD5Value FromText(std::string_view view);

		/// @brief ファイルから MD5 ハッシュを計算します。
		/// @param path ファイルのパス
		/// @return 計算された MD5 ハッシュ
		[[nodiscard]]
		MD5Value FromFile(FilePathView path);
	}
}
