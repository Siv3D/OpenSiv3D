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

# include <ctime>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Date.hpp>

namespace s3d
{
	bool Date::isToday() const
	{
		::time_t t = ::time(nullptr);
		::tm lt;
		::localtime_r(&t, &lt);
		return (day == lt.tm_mday && month == (1 + lt.tm_mon) && year == (1900 + lt.tm_year));
	}

	Date Date::Today()
	{
		::time_t t = ::time(nullptr);
		::tm* lt = ::localtime(&t);
		return Date(1900 + lt->tm_year, lt->tm_mon + 1, lt->tm_mday);
	}
}
