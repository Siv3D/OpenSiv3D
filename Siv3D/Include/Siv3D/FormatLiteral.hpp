//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "String.hpp"
# include "../fmt/format.h"

namespace s3d
{
	namespace detail
	{
		template <class Char>
		std::basic_string<Char> GetTag(const Char*& format_str)
		{
			const Char* beg = format_str;

			if (*format_str == Char(':'))
			{
				++format_str;
			}

			const Char *end = format_str;

			while (*end && *end != Char('}'))
			{
				++end;
			}

			if (*end != L'}')
			{
				FMT_THROW(fmt::FormatError("missing '}' in format string"));
			}

			format_str = end + 1;

			return std::basic_string<Char>(beg, end);
		}

		struct FormatHelper
		{
			const wchar* str;

			template <class... Args>
			String operator()(Args&& ...args) const
			{
                return fmt::format(str, std::forward<Args>(args)...);
			}

			template <class... Args>
			String args(Args&& ...args) const
			{
				return operator()(std::forward<Args>(args)...);
			}
		};
	}

	inline detail::FormatHelper Fmt(const String& s)
	{
		return detail::FormatHelper{ s.c_str() };
	}

	inline detail::FormatHelper Fmt(const wchar* s)
	{
		return detail::FormatHelper{ s };
	}

	inline namespace literals
	{
		inline namespace formatting_literals
		{
			inline detail::FormatHelper operator ""_fmt(const wchar* s, size_t)
			{
				return detail::FormatHelper{ s };
			}
		}
	}
}

namespace fmt
{
	template <class ArgFormatter, class Type>
	void format_arg(BasicFormatter<s3d::wchar, ArgFormatter>& f, const s3d::wchar*& format_str, const Type& value)
	{
		s3d::detail::GetTag(format_str);

		f.writer() << s3d::Format(value).str();
	}
}
