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

# include <mach/mach_time.h>
# include <sys/time.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace detail
	{
		static uint64 SteadyFull()
		{
			::mach_timebase_info_data_t base;
			::mach_timebase_info(&base);
			return static_cast<uint64>(::mach_absolute_time() * static_cast<double>(base.numer) / base.denom);
		}
		
		inline decltype(::mach_absolute_time)* InitSteadyClock()
		{
			::mach_timebase_info_data_t base;
			::mach_timebase_info(&base);
			return (base.numer == base.denom) ? ::mach_absolute_time : SteadyFull;
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
			const static auto SteadyClock = detail::InitSteadyClock();
			return SteadyClock();
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
			struct timezone tz;
			::gettimeofday(nullptr, &tz);
			return -tz.tz_minuteswest;
		}
	}
}
