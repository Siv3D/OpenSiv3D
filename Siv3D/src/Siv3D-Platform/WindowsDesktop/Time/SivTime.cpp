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
# include <Siv3D/Windows.hpp>
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

		int32 UTCOffsetMinutes()
		{
			long timeZone;		
			::_get_timezone(&timeZone);
			return -timeZone / 60;
		}
	}
}
