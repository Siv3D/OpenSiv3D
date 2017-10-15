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

# include "Siv3D/FormatLiteral.hpp"

namespace s3d
{
	detail::FormatHelper Fmt(const String& text)
	{
		return detail::FormatHelper{ text.c_str() };
	}

	detail::FormatHelper Fmt(const char32* text)
	{
		return detail::FormatHelper{ text };
	}

	inline namespace literals
	{
		inline namespace formatting_literals
		{
			detail::FormatHelper operator ""_fmt(const char32* text, size_t)
			{
				return detail::FormatHelper{ text };
			}
		}
	}
}
