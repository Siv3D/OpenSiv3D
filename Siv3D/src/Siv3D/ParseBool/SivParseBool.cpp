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

# include <Siv3D/ParseBool.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Char.hpp>

namespace s3d
{
	bool ParseBool(const StringView s)
	{
		if (const auto opt = ParseBoolOpt(s))
		{
			return *opt;
		}
		else
		{
			throw ParseError{ U"ParseBool(\"{}\") failed"_fmt(s) };
		}
	}

	Optional<bool> ParseBoolOpt(const StringView s) noexcept
	{
		const char32* start	= s.data();
		const char32* end	= (start + s.size());

		while (start < end && IsSpace(start[0]))
		{
			++start;
		}

		while (start < end && IsSpace(end[-1]))
		{
			--end;
		}

		if (start >= end)
		{
			return none;
		}

		if (auto length = (end - start);
			length == 4)
		{
			if ((start[0] == U'T' || start[0] == U't')
				&& (start[1] == U'R' || start[1] == U'r')
				&& (start[2] == U'U' || start[2] == U'u')
				&& (start[3] == U'E' || start[3] == U'e'))
			{
				return true;
			}
		}
		else if (length == 5)
		{
			if ((start[0] == U'F' || start[0] == U'f')
				&& (start[1] == U'A' || start[1] == U'a')
				&& (start[2] == U'L' || start[2] == U'l')
				&& (start[3] == U'S' || start[3] == U's')
				&& (start[4] == U'E' || start[4] == U'e'))
			{
				return false;
			}
		}

		return none;
	}
}
