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
# include <Siv3D/Char.hpp>
# include <Siv3D/Windows.hpp>
# include <Siv3D/DateTime.hpp>
# include <Siv3D/FormatUtility.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr DateTime ToDateTime(const SYSTEMTIME& in)
		{
			return{ in.wYear, in.wMonth, in.wDay, in.wHour, in.wMinute, in.wSecond, in.wMilliseconds };
		}
	}

	DateTime DateTime::Yesterday()
	{
		return Date::Yesterday();
	}

	DateTime DateTime::Today()
	{
		return Date::Today();
	}

	DateTime DateTime::Tomorrow()
	{
		return Date::Tomorrow();
	}

	DateTime DateTime::Now()
	{
		SYSTEMTIME sysTime;
		::GetLocalTime(&sysTime);
		return detail::ToDateTime(sysTime);
	}

	DateTime DateTime::NowUTC()
	{
		SYSTEMTIME sysTime;
		::GetSystemTime(&sysTime);
		return detail::ToDateTime(sysTime);
	}
}
