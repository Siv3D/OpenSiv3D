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

# pragma once

# if SIV3D_PLATFORM(WEB)
#	include <emscripten.h>
# endif

namespace s3d
{
	namespace Platform
	{
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

	# elif SIV3D_PLATFORM(WEB)

		inline uint64 Rdtsc() noexcept
		{
			// workaround
			return static_cast<uint64>(emscripten_get_now() * 1e+6);
		}
		
	# else

		# error Unimplemented

	# endif
	}

	inline uint64 RDTSCClock::cycles() const noexcept
	{
		return (Platform::Rdtsc() - m_start);
	}

	inline void RDTSCClock::log() const
	{
		Logger(cycles(), U"cycles"_sv);
	}

	inline void RDTSCClock::console() const
	{
		Console(cycles(), U"cycles"_sv);
	}

	inline void RDTSCClock::print() const
	{
		Print(cycles(), U"cycles"_sv);
	}
}
