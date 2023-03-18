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

# include <ctime>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace detail
	{
		const static int64 g_QPC_Freq = [](){
			::LARGE_INTEGER frequency;
			::QueryPerformanceFrequency(&frequency);
			return frequency.QuadPart;
		}();

		const static int64 g_QPC_Base = []() {
			::LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			return counter.QuadPart;
		}();

		inline int64 GetCount() noexcept
		{
			::LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			return (counter.QuadPart - g_QPC_Base);
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
		uint64 GetSec() noexcept
		{
			static const double QPF_Sec = (1.0 / detail::g_QPC_Freq);
			return static_cast<uint64>(detail::GetCount() * QPF_Sec);
		}

		uint64 GetMillisec() noexcept
		{
			static const double QPF_Millisec = (1'000.0 / detail::g_QPC_Freq);
			return static_cast<uint64>(detail::GetCount() * QPF_Millisec);
		}

		uint64 GetMicrosec() noexcept
		{
			static const double QPF_Microsec = (1'000'000.0 / detail::g_QPC_Freq);
			return static_cast<uint64>(detail::GetCount() * QPF_Microsec);
		}

		uint64 GetNanosec() noexcept
		{
			static const double QPF_Nanosec = (1'000'000'000.0 / detail::g_QPC_Freq);
			return static_cast<uint64>(detail::GetCount() * QPF_Nanosec);
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
