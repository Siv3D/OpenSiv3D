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

namespace s3d
{
	namespace detail
	{
		inline constexpr char32 halfWidthSpace = U' ';

		inline constexpr char32 fullWidthSpace = U'　';

		[[nodiscard]]
		inline constexpr int32 Compare(char32 a, char32 b) noexcept
		{
			return ((a < b) ? -1 : (a > b));
		}
	}

	inline constexpr bool IsASCII(const char32 ch) noexcept
	{
		return (ch <= 0x7F);
	}

	inline constexpr bool IsDigit(const char32 ch) noexcept
	{
		return ((ch - U'0') <= (U'9' - U'0'));
	}

	inline constexpr bool IsLower(const char32 ch) noexcept
	{
		return ((ch - U'a') <= (U'z' - U'a'));
	}

	inline constexpr bool IsUpper(const char32 ch) noexcept
	{
		return ((ch - U'A') <= (U'Z' - U'A'));
	}

	inline constexpr char32 ToLower(const char32 ch) noexcept
	{
		if (IsUpper(ch))
		{
			return (ch + ('a' - 'A'));
		}
		else
		{
			return ch;
		}
	}

	inline constexpr char32 ToUpper(const char32 ch) noexcept
	{
		if (IsLower(ch))
		{
			return (ch - ('a' - 'A'));
		}
		else
		{
			return ch;
		}
	}

	inline constexpr bool IsAlpha(const char32 ch) noexcept
	{
		return (IsLower(ch) || IsUpper(ch));
	}

	inline constexpr bool IsAlnum(const char32 ch) noexcept
	{
		return (IsDigit(ch) || IsAlpha(ch));
	}

	inline constexpr bool IsXdigit(const char32 ch) noexcept
	{
		return (IsDigit(ch)
			|| ((ch - U'A') <= (U'F' - U'A'))
			|| ((ch - U'a') <= (U'f' - U'a')));
	}

	inline constexpr bool IsControl(const char32 ch) noexcept
	{
		return ((ch <= 0x1F) || ((ch - 0x7F) <= (0x9F - 0x7F)));
	}

	inline constexpr bool IsBlank(const char32 ch) noexcept
	{
		return ((ch == detail::halfWidthSpace)
			|| (ch == U'\t')
			|| (ch == detail::fullWidthSpace));
	}

	inline constexpr bool IsSpace(const char32 ch) noexcept
	{
		return ((ch == detail::halfWidthSpace)
			|| (ch - U'\t') <= (U'\r' - U'\t'))
			|| (ch == detail::fullWidthSpace);
	}

	inline bool IsPrint(const char32 ch)
	{
		if (ch < 0xFFFF)
		{
			return static_cast<bool>(::iswprint(static_cast<wchar_t>(ch)));
		}
		else
		{
			return true;
		}
	}

	inline constexpr int32 CaseInsensitiveCompare(const char32 a, const char32 b) noexcept
	{
		if (IsAlpha(a) && IsAlpha(b))
		{
			return detail::Compare(ToLower(a), ToLower(b));
		}
		else
		{
			return detail::Compare(a, b);
		}
	}

	inline constexpr bool CaseInsensitiveEquals(const char32 a, const char32 b) noexcept
	{
		return (ToLower(a) == ToLower(b));
	}
}
