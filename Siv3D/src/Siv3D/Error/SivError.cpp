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

# include <Siv3D/Error.hpp>

namespace s3d
{
	std::ostream& operator <<(std::ostream& output, const Error& value)
	{
		return (output << '[' << value.type() << "] " << value.what().narrow());
	}

	std::wostream& operator <<(std::wostream& output, const Error& value)
	{
		return (output << L'[' << value.type() << L"] " << value.what().toWstr());
	}

	std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const Error& value)
	{
		return output << (U'[' + value.type() + U"] " + value.what());
	}

	void Formatter(FormatData& formatData, const Error& value)
	{
		const String s = (U"["_s + value.type() + U"] " + value.what());

		formatData.string.append(s);
	}
}
