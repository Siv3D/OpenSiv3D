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

# include <Siv3D/Error.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Error& value)
	{
		const String text = U"[Exception] " + value.what();

		formatData.string.append(text);
	}

	std::ostream& operator <<(std::ostream& output, const Error& value)
	{
		return output << "[Exception] " << value.what().narrow();
	}

	std::wostream& operator <<(std::wostream& output, const Error& value)
	{
		return output << L"[Exception] " << value.what().toWstr();
	}
}
