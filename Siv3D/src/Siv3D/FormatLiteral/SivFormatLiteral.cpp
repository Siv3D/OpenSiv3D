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

# include <Siv3D/FormatLiteral.hpp>

namespace s3d
{
	detail::FormatHelper Fmt(const String& text)
	{
		return detail::FormatHelper(text.c_str(), text.size());
	}

	detail::FormatHelper Fmt(const char32* text)
	{
		return detail::FormatHelper(text, std::char_traits<char32>::length(text));
	}

	namespace Literals
	{
		namespace FormatLiterals
		{
			detail::FormatHelper operator ""_fmt(const char32* text, const size_t length)
			{
				return detail::FormatHelper(text, length);
			}
		}
	}
}
