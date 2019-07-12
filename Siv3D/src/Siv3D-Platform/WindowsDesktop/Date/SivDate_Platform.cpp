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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/Windows.hpp>
# include <Siv3D/Date.hpp>

namespace s3d
{
	bool Date::isToday() const
	{
		SYSTEMTIME sysTime;
		::GetLocalTime(&sysTime);
		return (day == sysTime.wDay && month == sysTime.wMonth && year == sysTime.wYear);
	}

	Date Date::Today()
	{
		SYSTEMTIME sysTime;
		::GetLocalTime(&sysTime);
		return Date(sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	}
}
