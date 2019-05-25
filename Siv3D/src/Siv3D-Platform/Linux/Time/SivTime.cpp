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

# include <time.h>
# include <sys/time.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace detail
	{
		static uint64 clock_gettime_us()
		{
			timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);
			return static_cast<uint64>(ts.tv_sec * 1e9 + ts.tv_nsec);
		}
	}

	namespace Time
	{
		uint64 GetSec()
		{
			return GetNanosec() / 1'000'000'000;
		}
		
		uint64 GetMillisec()
		{
			return GetNanosec() / 1'000'000;
		}
		
		uint64 GetMicrosec()
		{
			return GetNanosec() / 1'000;
		}
		
		uint64 GetNanosec()
		{
			return detail::clock_gettime_us();
		}
		
		uint64 GetSecSinceEpoch()
		{
			return GetMicrosecSinceEpoch() / 1'000'000;
		}
		
		uint64 GetMillisecSinceEpoch()
		{
			return GetMicrosecSinceEpoch() / 1'000;
		}
		
		uint64 GetMicrosecSinceEpoch()
		{
			::timeval tv;
			::gettimeofday(&tv, nullptr);
			return tv.tv_sec * 1'000'000ULL + tv.tv_usec;
		}
		
		int32 UTCOffsetMinutes()
		{
			struct timeval tv;
			struct timezone tz;
			::gettimeofday(&tv, &tz);
			return -tz.tz_minuteswest;
		}
	}
}
