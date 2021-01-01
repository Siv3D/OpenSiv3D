//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <time.h>
# include <Siv3D/Common.hpp>
# include <Siv3D/Time.hpp>

namespace s3d
{
	namespace detail
	{
		inline uint64 clock_gettime_ns() noexcept
		{
			timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);
			return static_cast<uint64>(ts.tv_sec * 1'000'000'000ULL + ts.tv_nsec);
		}
	}

	namespace Time
	{
		uint64 GetSec() noexcept
		{
			return GetNanosec() / 1'000'000'000;
		}
		
		uint64 GetMillisec() noexcept
		{
			return GetNanosec() / 1'000'000;
		}
		
		uint64 GetMicrosec() noexcept
		{
			return GetNanosec() / 1'000;
		}
		
		uint64 GetNanosec() noexcept
		{
			return detail::clock_gettime_ns();
		}
	}
}
