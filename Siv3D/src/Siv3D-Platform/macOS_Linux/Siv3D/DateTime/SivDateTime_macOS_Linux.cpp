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

# include <sys/time.h>
# include <Siv3D/Common.hpp>
# include <Siv3D/DateTime.hpp>

namespace s3d
{
	DateTime DateTime::Now() noexcept
	{
		::timeval tv;
		::tm lt;
		::gettimeofday(&tv, nullptr);
		::localtime_r(&tv.tv_sec, &lt);
		return DateTime((1900 + lt.tm_year), (1 + lt.tm_mon), (lt.tm_mday),
						lt.tm_hour, lt.tm_min, lt.tm_sec, tv.tv_usec / 1000);
	}

	DateTime DateTime::NowUTC() noexcept
	{
		::timeval tv;
		::tm gt;
		::gettimeofday(&tv, nullptr);
		::gmtime_r(&tv.tv_sec, &gt);
		return DateTime((1900 + gt.tm_year), (1 + gt.tm_mon), (gt.tm_mday),
						gt.tm_hour, gt.tm_min, gt.tm_sec, tv.tv_usec / 1000);
	}
}
