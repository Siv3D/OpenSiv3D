//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace detail
	{
		struct FormatHelper : fmt::basic_string_view<char32>
		{
			using fmt::basic_string_view<char32>::basic_string_view;

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
