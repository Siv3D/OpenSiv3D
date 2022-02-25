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
# include "Common.hpp"
# include "IReader.hpp"
# include "StringView.hpp"

namespace s3d
{
	/// @brief テキストファイルのエンコーディング形式
	enum class TextEncoding : uint8
	{
		/// @brief 不明なエンコーティング
		Unknown,

		/// @brief UTF-8
		UTF8_NO_BOM,

		/// @brief UTF-8 with BOM
		UTF8_WITH_BOM,

		/// @brief UTF-16(LE) with BOM
		UTF16LE,

		/// @brief UTF-16(BE) with BOM
		UTF16BE,

		/// @brief デフォルト [UTF-8]
		Default = UTF8_NO_BOM,
	};

	namespace Unicode
	{
		/// @brief ファイルがテキストファイルである場合、そのエンコーディング形式を返します。
		/// @param reader IReader
		/// @return テキストファイルのエンコーディング形式	
		[[nodiscard]]
		TextEncoding GetTextEncoding(const IReader& reader);

		/// @brief ファイルがテキストファイルである場合、そのエンコーディング形式を返します。
		/// @param path ファイルパス
		/// @return テキストファイルのエンコーディング形式
		[[nodiscard]]
		TextEncoding GetTextEncoding(FilePathView path);

		/// @brief テキストファイルの BOM のサイズ（バイト）を返します。
		/// @param encoding エンコーディング形式
		/// @return テキストファイルの BOM のサイズ（バイト）
		[[nodiscard]]
		inline constexpr int32 GetBOMSize(TextEncoding encoding) noexcept;
	}
}

# include "detail/TextEncoding.ipp"
