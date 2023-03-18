//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <ctime>
# include <Siv3D/Common.hpp>
# include <Siv3D/Date.hpp>

namespace s3d
{
	Date Date::Today() noexcept
	{
		::time_t t = ::time(nullptr);
		::tm* lt = ::localtime(&t);
		return Date(1900 + lt->tm_year, lt->tm_mon + 1, lt->tm_mday);
	}
}
