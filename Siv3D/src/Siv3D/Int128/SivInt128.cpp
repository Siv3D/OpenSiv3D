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

# include <sstream>
# include <Siv3D/Int128.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const int128 value)
	{
		std::ostringstream os;

		os << value;

		formatData.string.append(Unicode::WidenAscii(os.str()));
	}

	void Formatter(FormatData& formatData, const uint128 value)
	{
		std::ostringstream os;

		os << value;

		formatData.string.append(Unicode::WidenAscii(os.str()));
	}
}
