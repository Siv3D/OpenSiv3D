//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "String.hpp"

S3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
# include "ThirdParty/fmt/format.h"
S3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
		struct FormatHelper
		{
			const fmt::basic_string_view<char32> str;

			FormatHelper() = default;

			FormatHelper(const char32* s, size_t length)
				: str(s, length) {}

			template <class... Args>
			[[nodiscard]] String operator()(Args&& ...args) const
			{
				return fmt::format(str, std::forward<Args>(args)...);
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
//		Print << U"{:.2f} {:.5f}"_fmt(Math::Pi, Math::Pi); 
//
//////////////////////////////////////////////////

	namespace Literals
	{
		[[nodiscard]] detail::FormatHelper operator ""_fmt(const char32* text, size_t length);
	}
}

# ifndef NO_S3D_USING

	using namespace s3d::Literals;

# endif
