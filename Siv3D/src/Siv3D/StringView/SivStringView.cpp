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

# include <Siv3D/StringView.hpp>
# include <Siv3D/Format.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const StringView& value)
	{
		formatData.string.append(value);
	}

	std::ostream& operator <<(std::ostream& output, const StringView& value)
	{
		return output << Unicode::Narrow(value);
	}

	std::wostream& operator <<(std::wostream& output, const StringView& value)
	{
		return output << Unicode::ToWString(value);
	}
}
