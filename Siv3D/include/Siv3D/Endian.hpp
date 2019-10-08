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
# include "Fwd.hpp"
# if SIV3D_PLATFORM(WINDOWS)
#	include <cstdlib>
# elif SIV3D_PLATFORM(MACOS)
#	include <libkern/OSByteOrder.h>
# endif

namespace s3d
{
# if SIV3D_PLATFORM(WINDOWS)

	[[nodiscard]] inline uint16 SwapEndian(uint16 value) noexcept
	{
		return ::_byteswap_ushort(value);
	}

	[[nodiscard]] inline uint32 SwapEndian(uint32 value) noexcept
	{
		return ::_byteswap_ulong(value);
	}

	[[nodiscard]] inline uint64 SwapEndian(uint64 value) noexcept
	{
		return ::_byteswap_uint64(value);
	}

# elif SIV3D_PLATFORM(MACOS)

	[[nodiscard]] inline uint16 SwapEndian(uint16 value) noexcept
	{
		return OSSwapInt16(value);
	}

	[[nodiscard]] inline uint32 SwapEndian(uint32 value) noexcept
	{
		return OSSwapInt32(value);
	}

	[[nodiscard]] inline uint64 SwapEndian(uint64 value) noexcept
	{
		return OSSwapInt64(value);
	}

# else

	[[nodiscard]] inline uint16 SwapEndian(uint16 value) noexcept
	{
		return (value << 8) | (value >> 8);
	}

	[[nodiscard]] inline uint32 SwapEndian(uint32 value) noexcept
	{
		uint32 ret = value << 24;
		ret |= (value & 0x0000FF00) << 8;
		ret |= (value & 0x00FF0000) >> 8;
		ret |= value >> 24;
		return ret;
	}

	[[nodiscard]] inline uint64 SwapEndian(uint64 value) noexcept
	{
		value = ((value & 0x00000000FFFFFFFFull) << 32) | ((value & 0xFFFFFFFF00000000ull) >> 32);
		value = ((value & 0x0000FFFF0000FFFFull) << 16) | ((value & 0xFFFF0000FFFF0000ull) >> 16);
		value = ((value & 0x00FF00FF00FF00FFull) <<  8) | ((value & 0xFF00FF00FF00FF00ull) >>  8);
		return value;
	}

# endif
}
