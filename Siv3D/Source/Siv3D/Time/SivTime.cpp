//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../../../Include/Siv3D/Platform.hpp"
# if defined(SIV3D_TARGET_WINDOWS)

# include <ctime>
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include "../../../Include/Siv3D/Fwd.hpp"

namespace s3d
{
	namespace Time
	{
		namespace detail
		{
			inline double GetPerformanceFrequency()
			{
				LARGE_INTEGER frequency;
				::QueryPerformanceFrequency(&frequency);
				return static_cast<double>(frequency.QuadPart);
			}

			inline int64 GetPerformanceCount()
			{
				LARGE_INTEGER counter;
				::QueryPerformanceCounter(&counter);
				return counter.QuadPart;
			}

			inline uint64 Get100NanosecSinceEpoch()
			{
				::FILETIME fileTime;
				::GetSystemTimeAsFileTime(&fileTime);
				return (static_cast<uint64>(fileTime.dwHighDateTime) << 32) + fileTime.dwLowDateTime - 11644473600 * 10'000'000;
			}
		}

		uint64 GetSec()
		{
			static const double scale = 1 / detail::GetPerformanceFrequency();
			return static_cast<uint64>(detail::GetPerformanceCount() * scale);
		}

		uint64 GetMillisec()
		{
			static const double scale = 1'000 / detail::GetPerformanceFrequency();
			return static_cast<uint64>(detail::GetPerformanceCount() * scale);
		}

		uint64 GetMicrosec()
		{
			static const double scale = 1'000'000 / detail::GetPerformanceFrequency();
			return static_cast<uint64>(detail::GetPerformanceCount() * scale);
		}

		uint64 GetNanosec()
		{
			static const double scale = 1'000'000'000 / detail::GetPerformanceFrequency();
			return static_cast<uint64>(detail::GetPerformanceCount() * scale);
		}

		uint64 GetSecSinceEpoch()
		{
			return detail::Get100NanosecSinceEpoch() / 10'000'000;
		}

		uint64 GetMillisecSinceEpoch()
		{
			return detail::Get100NanosecSinceEpoch() / 10'000;
		}

		uint64 GetMicrosecSinceEpoch()
		{
			return detail::Get100NanosecSinceEpoch() / 10;
		}

		int32 UtcOffsetMinutes()
		{
			long timeZone;		
			::_get_timezone(&timeZone);
			return -timeZone / 60;
		}
	}
}

# elif defined(SIV3D_TARGET_OSX)

# include <mach/mach_time.h>
# include <sys/time.h>
# include "../../../Include/Siv3D/Fwd.hpp"
# include "../../../Include/Siv3D/Time.hpp"

namespace s3d
{
	namespace Time
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

		uint64 GetSec()
		{
			return GetNanosec() / (1000*1000*1000);
		}

		uint64 GetMillisec()
		{
			return GetNanosec() / (1000*1000);
		}

		uint64 GetMicrosec()
		{
			return GetNanosec() / (1000);
		}

		uint64 GetNanosec()
		{
            const static auto SteadyClock = detail::InitSteadyClock();
			return SteadyClock();
		}

		uint64 GetSecSinceEpoch()
		{
			return GetMicrosecSinceEpoch() / (1000*1000);
		}

		uint64 GetMillisecSinceEpoch()
		{
			return GetMicrosecSinceEpoch() / (1000);
		}

		uint64 GetMicrosecSinceEpoch()
		{
			struct timeval tv;
			::gettimeofday(&tv, nullptr);
			return tv.tv_sec * (1000*1000ULL) + tv.tv_usec;
		}

		int32 UtcOffsetMinutes()
		{
			struct timezone tz;
			::gettimeofday(nullptr, &tz);
			return -tz.tz_minuteswest;
		}
	}
}

# endif
