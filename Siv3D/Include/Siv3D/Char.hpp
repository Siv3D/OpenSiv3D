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
# include <wchar.h>
# include "Types.hpp"
# include "Utility.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr char32_t halfWidthSpace = U' ';
		constexpr char32_t fullWidthSpace = U'　';
	}

	/// <summary>
	/// 10 進数の数字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 10 進数の数字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsDigit(const char32_t ch) noexcept
	{
		return (ch - U'0') <= (U'9' - U'0');
	}

	/// <summary>
	/// アルファベットの小文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// アルファベットの小文字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsLower(const char32_t ch) noexcept
	{
		return (ch - U'a') <= (U'z' - U'a');
	}

	/// <summary>
	/// アルファベットの大文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// アルファベットの大文字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsUpper(const char32_t ch) noexcept
	{
		return (ch - U'A') <= (U'Z' - U'A');
	}

	/// <summary>
	/// アルファベットであるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// アルファベットである場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsAlpha(const char32_t ch) noexcept
	{
		return IsLower(ch) || IsUpper(ch);
	}

	/// <summary>
	/// アルファベットもしくは数字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// アルファベットもしくは数字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsAlnum(const char32_t ch) noexcept
	{
		return IsDigit(ch) || IsAlpha(ch);
	}

	/// <summary>
	/// 16 進数の数字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 16 進数の数字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsXdigit(const char32_t ch) noexcept
	{
		return IsDigit(ch) || ((ch - U'A') <= (U'F' - U'A')) || ((ch - U'a') <= (U'f' - U'a'));
	}

	/// <summary>
	/// 制御文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 制御文字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsControl(const char32_t ch) noexcept
	{
		return (ch <= 0x1F) || ((ch - 0x7F) <= (0x9F - 0x7F));
	}

	/// <summary>
	/// 空白文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <remarks>
	/// ' ', '\t', '　' が該当します。
	/// </remarks>
	/// <returns>
	/// 空白文字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsBlank(const char32_t ch) noexcept
	{
		return (ch == detail::halfWidthSpace) || (ch == U'\t') || (ch == detail::fullWidthSpace);
	}

	/// <summary>
	/// 空白類文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <remarks>
	/// ' ', '\t', '\n', '\v', '\f', '\r', '　' が該当します。
	/// </remarks>
	/// <returns>
	/// 空白類文字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsSpace(const char32_t ch) noexcept
	{
		return ((ch - U'\t') <= (U'\r' - U'\t')) || (ch == detail::halfWidthSpace) || (ch == detail::fullWidthSpace);
	}

	/// <summary>
	/// 印字可能文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 印字可能文字である場合 true, それ以外の場合は false
	/// </returns>
	inline bool IsPrint(const char32_t ch)
	{
		return !!::iswprint(static_cast<wchar_t>(ch));
	}

	/// <summary>
	/// 絵文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <remarks>
	/// 参考: http://www.asahi-net.or.jp/~ax2s-kmtn/ref/unicode/emoji.html
	/// </remarks>
	/// <returns>
	/// 絵文字である場合 true, それ以外の場合は false
	/// </returns>
	inline constexpr bool IsEmoji(const char32_t ch) noexcept
	{
		return InRange<char32_t>(ch, 0x2600, 0x27BF)
			|| InRange<char32_t>(ch, 0x1F300, 0x1F6FF)
			|| InRange<char32_t>(ch, 0x1F900, 0x1F9FF);
	}

	inline constexpr int32 CaseInsensitiveCompare(const wchar a, const wchar b) noexcept
	{
		return (a + IsUpper(a) * 32) < (b + IsUpper(b) * 32) ? -1 : (a + IsUpper(a) * 32) != (b + IsUpper(b) * 32);
	}

	inline constexpr bool IsHighSurrogate(const char16_t ch) noexcept
	{
		return InRange<char16_t>(ch, 0xD800, 0xDBFF);
	}

	inline constexpr bool IsLowSurrogate(const char16_t ch) noexcept
	{
		return InRange<char16_t>(ch, 0xDC00, 0xDFFF);
	}
}
