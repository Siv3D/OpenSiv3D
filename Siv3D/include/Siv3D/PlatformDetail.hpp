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

# pragma once
# include <string>
# include "Fwd.hpp"

# if SIV3D_PLATFORM(WINDOWS)
#	include <intrin.h>
# endif

namespace s3d::Platform
{
//////////////////////////////////////////////////
//
// ポインタのサイズとメモリアライメント
//
//////////////////////////////////////////////////

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	constexpr size_t PointerSize = 8;
	constexpr size_t AllocatorAlignment = 16;

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

	constexpr size_t PointerSize = 8;
	constexpr size_t AllocatorAlignment = 16;

# else

# error Unimplemented

# endif

//////////////////////////////////////////////////
//
// 実行ファイル埋め込みリソース
// Embedded Resource
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	inline constexpr bool HasEmbeddedResource = true;

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

	inline constexpr bool HasEmbeddedResource = false;

# else

# error Unimplemented

# endif


//////////////////////////////////////////////////
//
// アライメントされたメモリの確保と開放
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	inline void* AlignedMalloc(size_t size, size_t alignment)
	{
		return ::_aligned_malloc(size, alignment);
	}

	inline void AlignedFree(void* const p)
	{
		::_aligned_free(p);
	}

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

	inline void* AlignedMalloc(size_t size, size_t alignment)
	{
		if (alignment > Platform::AllocatorAlignment)
		{
			void* p;
			::posix_memalign(&p, alignment, size);
			return p;
		}
		else
		{
			return std::malloc(size);
		}
	}

	inline void AlignedFree(void* const p)
	{
		std::free(p);
	}

# else

# error Unimplemented

# endif

//////////////////////////////////////////////////
//
// ファイルパスのネイティブ文字列型
// Native file path type
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	using NativeFilePath = std::wstring;

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

	using NativeFilePath = std::string;

# else

# error Unimplemented

# endif

//////////////////////////////////////////////////
//
// RDTSC の取得
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	__forceinline uint64 Rdtsc()
	{
		return ::__rdtsc();
	}

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

	inline uint64 Rdtsc()
	{
		uint32 hi, lo;
		__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
		return static_cast<uint64>(lo) | (static_cast<uint64>(hi) << 32);
	}

# else

# error Unimplemented

# endif

}

//////////////////////////////////////////////////
//
// ConcurrentTask::is_done
//
//////////////////////////////////////////////////

# if SIV3D_PLATFORM(WINDOWS)

	# define SIV3D_CONCURRENT_TASK_IS_DONE base_type::_Is_ready()

# elif SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

	# define SIV3D_CONCURRENT_TASK_IS_DONE (base_type::wait_for(std::chrono::seconds(0)) == std::future_status::ready)

# else

# error Unimplemented

# endif
