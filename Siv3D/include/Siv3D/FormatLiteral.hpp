//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "String.hpp"
# define FMT_USE_EXTERN_TEMPLATES 1
# include <ThirdParty/fmt/format.h>

namespace s3d
{
	namespace detail
	{
		struct FormatHelper
		{
			const fmt_s3d::basic_string_view<char32> str;

			FormatHelper() = default;

			FormatHelper(const char32* s, size_t length)
				: str(s, length) {}

			template <class... Args>
			[[nodiscard]] String operator()(Args&& ...args) const
			{
				return fmt_s3d::format(str, std::forward<Args>(args)...);
			}
		};
	}

	[[nodiscard]] detail::FormatHelper Fmt(const String& text);

	[[nodiscard]] detail::FormatHelper Fmt(const char32* text);


//////////////////////////////////////////////////
//
//	Literals
//
//	* examples *
//
//		Print << U"Year {} Calendar"_fmt(2017);
//
//		Print << U"{2}/{1}/{0}"_fmt(2017, 12, 25); 
//
//		Print << U"{:.2f} {:.5f}"_fmt(Math::Constants::Pi, Math::Constants::Pi); 
//
//////////////////////////////////////////////////

	inline namespace Literals
	{
		inline namespace FormatLiterals
		{
			[[nodiscard]] detail::FormatHelper operator ""_fmt(const char32* text, size_t length);
		}
	}
}
