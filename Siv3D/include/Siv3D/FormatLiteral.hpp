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
# include "String.hpp"
# include "ThirdParty/fmt/format.h"

namespace s3d
{
	namespace detail
	{
		struct FormatHelper
		{
			const char32* str;

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

	inline namespace literals
	{
		inline namespace formatting_literals
		{
			[[nodiscard]] detail::FormatHelper operator ""_fmt(const char32* text, size_t);
		}
	}
}

# ifndef NO_S3D_USING

	using namespace s3d::literals;

# endif
