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

# include <time.h>
# include <sys/time.h>
# include <Siv3D/Common.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace detail
	{
		inline uint64 GetTimeNS() noexcept
		{
			timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);
			return ((ts.tv_sec * 1'000'000'000ULL) + ts.tv_nsec);
		}

		const static uint64 g_BaseTimeNS = GetTimeNS();

		inline uint64 GetApplicationTimeNS() noexcept
		{
			return (GetTimeNS() - g_BaseTimeNS);
		}
	}

	namespace Time
	{
		uint64 GetSec() noexcept
		{
			return (detail::GetApplicationTimeNS() /  1'000'000'000);
		}
		
		uint64 GetMillisec() noexcept
		{
			return (detail::GetApplicationTimeNS() /  1'000'000);
		}
		
		uint64 GetMicrosec() noexcept
		{
			return (detail::GetApplicationTimeNS() / 1'000);
		}
		
		uint64 GetNanosec() noexcept
		{
			return detail::GetApplicationTimeNS();
		}

			uint64 GetSecSinceEpoch()
		{
			return (GetMicrosecSinceEpoch() / 1'000'000);
		}
		
		uint64 GetMillisecSinceEpoch()
		{
			return (GetMicrosecSinceEpoch() / 1'000);
		}
		
		uint64 GetMicrosecSinceEpoch()
		{
			::timeval tv;
			::gettimeofday(&tv, nullptr);
			return (tv.tv_sec * 1'000'000ULL + tv.tv_usec);
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
