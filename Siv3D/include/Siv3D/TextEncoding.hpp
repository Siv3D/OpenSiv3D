//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "BinaryReader.hpp"

namespace s3d
{
	/// <summary>
	/// テキストファイルのエンコーディング形式
	/// </summary>
	/// <remarks>
	/// テキストファイルの文字エンコーディング形式を示します。
	/// </remarks>
	enum class TextEncoding
	{
		Unknown,

		/// <summary>
		/// UTF-8
		/// </summary>
		UTF8_NO_BOM,

		/// <summary>
		/// UTF-8 with BOM
		/// </summary>
		UTF8,

		/// <summary>
		/// UTF-16(LE) with BOM
		/// </summary>
		UTF16LE,

		/// <summary>
		/// UTF-16(BE) with BOM
		/// </summary>
		UTF16BE,

		/// <summary>
		/// デフォルト [UTF-8]
		/// </summary>
		Default = UTF8,		
	};

	namespace Unicode
	{
		/// <summary>
		/// ファイルがテキストファイルである場合、そのエンコーディング形式を返します。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// テキストファイルのエンコーディング形式
		/// </returns>
		[[nodiscard]] TextEncoding GetTextEncoding(const IReader& reader);

		/// <summary>
		/// ファイルがテキストファイルである場合、そのエンコーディング形式を返します。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// テキストファイルのエンコーディング形式
		/// </returns>
		[[nodiscard]] inline TextEncoding GetTextEncoding(const FilePathView path)
		{
			return GetTextEncoding(BinaryReader(path));
		}

		/// <summary>
		/// テキストファイルの BOM のサイズ（バイト）を返します。
		/// </summary>
		/// <param name="encoding">
		/// エンコーディング形式
		/// </param>
		/// <returns>
		/// テキストファイルの BOM のサイズ（バイト）
		/// </returns>
		[[nodiscard]] inline constexpr int32 GetBOMSize(TextEncoding encoding) noexcept
		{
			switch (encoding)
			{
			case TextEncoding::UTF8:
				return 3;
			case TextEncoding::UTF16LE:
			case TextEncoding::UTF16BE:
				return 2;
			default:
				return 0;
			}
		}
	}
}
