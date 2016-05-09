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
}
