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
# include "NamedParameter.hpp"

namespace s3d
{
	/// <summary>
	/// 文字セット
	/// </summary>
	/// <remarks>
	/// 文字セットを変換する機能を提供します。
	/// </remarks>
	namespace CharacterSet
	{
		/// <summary>
		/// マルチバイト ASCII 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="asciiStr">
		/// ASCII 文字で構成されたマルチバイト文字列
		/// </param>
		/// <remarks>
		/// Widen() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String WidenAscii(CStringView asciiStr);

		/// <summary>
		/// マルチバイト文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// マルチバイト文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String Widen(CStringView str);

		/// <summary>
		/// ワイド ASCII 文字列をマルチバイト文字列に変換します。
		/// </summary>
		/// <param name="asciiStr">
		/// ASCII 文字で構成されたワイド文字列
		/// </param>
		/// <remarks>
		/// Narrow() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換されたマルチバイト文字列
		/// </returns>
		std::string NarrowAscii(StringView asciiStr);

		/// <summary>
		/// ワイド文字列をマルチバイト文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換されたマルチバイト文字列
		/// </returns>
		std::string Narrow(StringView str);

		/// <summary>
		/// UTF-8 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String FromUTF8(UTF8StringView str);

		/// <summary>
		/// UTF-16 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String FromUTF16(const std::u16string& str);

		/// <summary>
		/// UTF-32 文字列をワイド文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-32 文字列
		/// </param>
		/// <returns>
		/// 変換されたワイド文字列
		/// </returns>
		String FromUTF32(const std::u32string& str);

		/// <summary>
		/// ワイド文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-8 文字列
		/// </returns>
		std::string ToUTF8(StringView str);

		/// <summary>
		/// ワイド文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-16 文字列
		/// </returns>
		std::u16string ToUTF16(StringView str);

		/// <summary>
		/// ワイド文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// ワイド文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u32string ToUTF32(StringView str);

		/// <summary>
		/// UTF-8 文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-16 文字列
		/// </returns>
		std::u16string UTF8ToUTF16(UTF8StringView str);

		/// <summary>
		/// UTF-8 文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u32string UTF8ToUTF32(UTF8StringView str);

		/// <summary>
		/// UTF-16 文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-8 文字列
		/// </returns>
		std::string UTF16ToUTF8(const std::u16string& str);

		/// <summary>
		/// UTF-16 文字列を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u32string UTF16ToUTF32(const std::u16string& str);

		/// <summary>
		/// UTF-32 文字列を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-8 文字列
		/// </returns>
		std::string UTF32ToUTF8(const std::u32string& str);

		/// <summary>
		/// UTF-32 文字列を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="str">
		/// UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された UTF-32 文字列
		/// </returns>
		std::u16string UTF32ToUTF16(const std::u32string& str);

		std::pair<char32_t, int32> GetUTF32CodePoint(const char* utf8, size_t length);

		std::array<char16_t, 2> GetUTF16CodePoint(char32_t ch);

		size_t CountCodePoints(StringView str);

		/// <summary>
		/// 文字列をパーセントエンコードします。
		/// </summary>
		/// <param name="str">
		/// パーセントエンコードする文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		String PercentEncode(StringView str, Arg::upperCase_<bool> upperCase = (Arg::upperCase = true));
	}
}
