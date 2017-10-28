//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <ctime>
# ifndef NOMINMAX
#	define  NOMINMAX
# endif
# ifndef STRICT
#	define  STRICT
# endif
# ifndef WIN32_LEAN_AND_MEAN
#	define  WIN32_LEAN_AND_MEAN
# endif
# ifndef _WIN32_WINNT
#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
# endif
# ifndef NTDDI_VERSION
#	define  NTDDI_VERSION NTDDI_WIN7
# endif
# include <Windows.h>
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	namespace detail
	{
		inline double GetPerformanceFrequency()
		{
			::LARGE_INTEGER frequency;
			::QueryPerformanceFrequency(&frequency);
			return static_cast<double>(frequency.QuadPart);
		}

		inline int64 GetPerformanceCount()
		{
			::LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			return counter.QuadPart;
		}

		inline uint64 Get100NanosecSinceEpoch()
		{
			::FILETIME fileTime;
			::GetSystemTimeAsFileTime(&fileTime);
			return (static_cast<uint64>(fileTime.dwHighDateTime) << 32) + fileTime.dwLowDateTime - (11'644'473'600 * 10'000'000);
		}
	}

	namespace Time
	{
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

# elif defined(SIV3D_TARGET_MACOS)

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

		int32 UtcOffsetMinutes()
		{
			struct timezone tz;
			::gettimeofday(nullptr, &tz);
			return -tz.tz_minuteswest;
		}
	}
}

# elif defined (SIV3D_TARGET_LINUX)

# include <time.h>
# include <sys/time.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace Time
	{
		namespace detail
		{
			uint64 clock_gettime_ns()
			{
				timespec ts;
				clock_gettime(CLOCK_MONOTONIC, &ts);
				return static_cast<uint64>(ts.tv_sec * 1e9 + ts.tv_nsec);
			}
		}

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
			return detail::clock_gettime_ns();
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

		int32 UtcOffsetMinutes()
		{
			struct timeval tv;
			struct timezone tz;
			::gettimeofday(&tv, &tz);
			return -tz.tz_minuteswest;
		}
	}
}

# endif
