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
		struct FormatHelper : std::u32string_view
		{
			using std::u32string_view::u32string_view;

			/// @brief フォーマット指定子 `{}` を含む文字列リテラルへ、変換する値を渡します。
			/// @tparam ...Args 変換する値の型
			/// @param ...args 変換する値
			/// @remark 文字列リテラルのあとに _fmt() サフィックスを付けると、文字列リテラル内に記述した `{}` という箇所に、( ) 内に記述した引数が文字列化されて挿入されます。
			/// @return `{}` という箇所に値を変換して挿入した文字列
			template <class... Args>
			[[nodiscard]]
			String operator()(Args&& ...args) const
			{
				return fmt::format(*this, std::forward<Args>(args)...);
			}
		};
	}

	inline constexpr detail::FormatHelper Fmt(const char32* s) noexcept
	{
		return detail::FormatHelper{ s, std::char_traits<char32>::length(s) };
	}

	inline constexpr detail::FormatHelper Fmt(const StringView s) noexcept
	{
		return detail::FormatHelper{ s.data(), s.size() };
	}

	inline detail::FormatHelper Fmt(const String& s) noexcept
	{
		return detail::FormatHelper{ s.c_str(), s.size() };
	}

	inline detail::FormatHelper Fmt(const std::u32string& s) noexcept
	{
		return detail::FormatHelper{ s.c_str(), s.size() };
	}

	inline namespace Literals
	{
		inline namespace FormatLiterals
		{
			inline constexpr detail::FormatHelper operator ""_fmt(const char32* s, const size_t length) noexcept
			{
				return detail::FormatHelper{ s, length };
			}
		}
	}
}
