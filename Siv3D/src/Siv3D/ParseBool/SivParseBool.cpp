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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/ParseBool.hpp>

namespace s3d
{
	bool ParseBool(const StringView view)
	{
		return ParseBoolOpt(view).value_or(false);
	}

	Optional<bool> ParseBoolOpt(const StringView view)
	{
		const char32* start = view.data();
		const char32* end = start + view.size();

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

		if ((end - start) == 4)
		{
			if ((start[0] == U'T' || start[0] == U't')
				&& (start[1] == U'R' || start[1] == U'r')
				&& (start[2] == U'U' || start[2] == U'u')
				&& (start[3] == U'E' || start[3] == U'e'))
			{
				return true;
			}
		}
		else if ((end - start) == 5)
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
