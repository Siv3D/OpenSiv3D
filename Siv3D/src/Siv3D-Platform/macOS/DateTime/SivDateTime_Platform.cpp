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
# include <Siv3D/DateTime.hpp>
# include <sys/time.h>

namespace s3d
{
	DateTime DateTime::Now()
	{
		::timeval tv;
		::tm lt;
		::gettimeofday(&tv, nullptr);
		::localtime_r(&tv.tv_sec, &lt);
		return DateTime((1900 + lt.tm_year), (1 + lt.tm_mon), (lt.tm_mday),
						lt.tm_hour, lt.tm_min, lt.tm_sec, tv.tv_usec / 1000);
	}

	DateTime DateTime::NowUTC()
	{
		::timeval tv;
		::tm gt;
		::gettimeofday(&tv, nullptr);
		::gmtime_r(&tv.tv_sec, &gt);
		return DateTime((1900 + gt.tm_year), (1 + gt.tm_mon), (gt.tm_mday),
						gt.tm_hour, gt.tm_min, gt.tm_sec, tv.tv_usec / 1000);
	}
}
