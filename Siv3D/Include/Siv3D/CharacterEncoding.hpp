//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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
	enum class CharacterEncoding
	{
		Unknown,

		/// <summary>
		/// UTF-8
		/// </summary>
		UTF8,

		/// <summary>
		/// UTF-8 with BOM
		/// </summary>
		UTF8_BOM,

		/// <summary>
		/// UTF-16(LE) with BOM
		/// </summary>
		UTF16LE_BOM,

		/// <summary>
		/// UTF-16(BE) with BOM
		/// </summary>
		UTF16BE_BOM,

		/// <summary>
		/// デフォルト [UTF-8]
		/// </summary>
		Default = UTF8_BOM,		
	};

	namespace CharacterSet
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
		CharacterEncoding GetEncoding(const IReader& reader);

		/// <summary>
		/// ファイルがテキストファイルである場合、そのエンコーディング形式を返します。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// テキストファイルのエンコーディング形式
		/// </returns>
		inline CharacterEncoding GetEncoding(const FilePath& path)
		{
			return GetEncoding(BinaryReader(path));
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
		inline constexpr int32 GetBOMSize(CharacterEncoding encoding)
		{
			return encoding == CharacterEncoding::UTF8_BOM ? 3
				: (encoding == CharacterEncoding::UTF16LE_BOM || encoding == CharacterEncoding::UTF16BE_BOM) ? 2 : 0;
		}
	}
}
