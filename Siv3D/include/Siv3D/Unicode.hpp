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
# include <string>
# include "Fwd.hpp"
# include "Utility.hpp"

namespace s3d
{
	namespace Unicode
	{
		inline constexpr bool IsHighSurrogate(const char16 ch) noexcept
		{
			return InRange<char16>(ch, 0xD800, 0xDBFF);
		}

		inline constexpr bool IsLowSurrogate(const char16 ch) noexcept
		{
			return InRange<char16>(ch, 0xDC00, 0xDFFF);
		}

		/// <summary>
		/// マルチバイト ASCII 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="asciiString">
		/// ASCII 文字で構成されたマルチバイト文字列
		/// </param>
		/// <remarks>
		/// Widen() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String WidenAscii(std::string_view asciiText);

		/// <summary>
		/// マルチバイト文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// マルチバイト文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String Widen(std::string_view text);

		/// <summary>
		/// ワイド ASCII 文字列をマルチバイト文字列に変換します。
		/// </summary>
		/// <param name="asciiString">
		/// ASCII 文字で構成されたワイド文字列
		/// </param>
		/// <remarks>
		/// Narrow() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換されたマルチバイト文字列
		/// </returns>
		std::string NarrowAscii(StringView asciiString);

		/// <summary>
		/// ワイド文字列をマルチバイト文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換されたマルチバイト文字列
		/// </returns>
		std::string Narrow(StringView text);

		/// <summary>
		/// UTF-8 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String FromUTF8(std::string_view text);

		/// <summary>
		/// UTF-16 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String FromUTF16(std::u16string_view text);

		/// <summary>
		/// UTF-32 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-32 文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String FromUTF32(std::u32string_view text);

		/// <summary>
		/// ワイド文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-8 文字列
		/// </returns>
		std::string ToUTF8(StringView text);

		/// <summary>
		/// ワイド文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-16 文字列
		/// </returns>
		std::u16string ToUTF16(StringView text);

		/// <summary>
		/// ワイド文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u32string ToUTF32(StringView text);

		/// <summary>
		/// UTF-8 文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-16 文字列
		/// </returns>
		std::u16string UTF8ToUTF16(std::string_view text);

		/// <summary>
		/// UTF-8 文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u32string UTF8ToUTF32(std::string_view text);

		/// <summary>
		/// UTF-16 文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-8 文字列
		/// </returns>
		std::string UTF16ToUTF8(std::u16string_view text);

		/// <summary>
		/// UTF-16 文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u32string UTF16ToUTF32(std::u16string_view text);

		/// <summary>
		/// UTF-32 文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-8 文字列
		/// </returns>
		std::string UTF32ToUTF8(std::u32string_view text);

		/// <summary>
		/// UTF-32 文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="text">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u16string UTF32ToUTF16(std::u32string_view text);


		size_t CountCodePoints(StringView str);
	}
}
