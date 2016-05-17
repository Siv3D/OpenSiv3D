//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
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
		/// <summary>
		/// ANSI
		/// </summary>
		ANSI,

		/// <summary>
		/// UTF-8
		/// </summary>
		UTF8,

		/// <summary>
		/// UTF-16 リトルエンディアン
		/// </summary>
		UTF16LE,

		/// <summary>
		/// UTF-16 ビッグエンディアン
		/// </summary>
		UTF16BE,

		/// <summary>
		/// デフォルト [UTF-8]
		/// </summary>
		Default = UTF8,
	};

	namespace CharacterSet
	{
		/// <summary>
		/// ファイルがテキストファイルである場合、そのエンコーディング形式を返します。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <param name="bomSize">
		/// [out] テキストファイルに含まれている BOM のサイズ
		/// </param>
		/// <returns>
		/// テキストファイルのエンコーディング形式
		/// </returns>
		TextEncoding GetEncoding(const IReader& reader, int32& bomSize);

		/// <summary>
		/// ファイルがテキストファイルである場合、そのエンコーディング形式を返します。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="bomSize">
		/// [out] テキストファイルに含まれている BOM のサイズ
		/// </param>
		/// <returns>
		/// テキストファイルのエンコーディング形式
		/// </returns>
		inline TextEncoding GetEncoding(const FilePath& path, int32& bomSize)
		{
			return GetEncoding(BinaryReader(path), bomSize);
		}
	}
}
