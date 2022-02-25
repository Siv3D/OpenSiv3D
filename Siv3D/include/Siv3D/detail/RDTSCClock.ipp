//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

# if !(defined(_M_X64) || defined(__x86_64__) || SIV3D_PLATFORM(WEB))

// Use std::chrono instead of RDTSC on environments neither x86_64 nor Web
# include <chrono>

# endif

namespace s3d
{
	namespace Platform
	{
	# if defined(_M_X64) || defined(__x86_64__)
	
		# if SIV3D_PLATFORM(WINDOWS)

			inline uint64 Rdtsc() noexcept
			{
				return ::__rdtsc();
			}

		# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

			inline uint64 Rdtsc() noexcept
			{
				uint32 hi, lo;
				__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
				return static_cast<uint64>(lo) | (static_cast<uint64>(hi) << 32);
			}

		# else

			# error Unimplemented

		# endif

	# elif SIV3D_PLATFORM(WEB)

		inline uint64 Rdtsc() noexcept
		{
			// workaround
			return static_cast<uint64>(emscripten_get_now() * 1e+6);
		}

	# else

		inline uint64 Rdtsc() noexcept
		{
			// Workaround for environments neither x86_64 nor Web
			auto now = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
		}

	# endif
	}

	inline uint64 RDTSCClock::cycles() const noexcept
	{
		return (Platform::Rdtsc() - m_start);
	}
}
