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
# include "../Endian.hpp"

# if SIV3D_PLATFORM(WINDOWS)
#	include <cstdlib>
# elif SIV3D_PLATFORM(MACOS)
#	include <libkern/OSByteOrder.h>
# endif

namespace s3d
{
# if SIV3D_PLATFORM(WINDOWS)

	inline uint16 SwapEndian(const uint16 value) noexcept
	{
		return ::_byteswap_ushort(value);
	}

	inline uint32 SwapEndian(const uint32 value) noexcept
	{
		return ::_byteswap_ulong(value);
	}

	inline uint64 SwapEndian(const uint64 value) noexcept
	{
		return ::_byteswap_uint64(value);
	}

# elif SIV3D_PLATFORM(MACOS)

	inline uint16 SwapEndian(const uint16 value) noexcept
	{
		return OSSwapInt16(value);
	}

	inline uint32 SwapEndian(const uint32 value) noexcept
	{
		return OSSwapInt32(value);
	}

	inline uint64 SwapEndian(const uint64 value) noexcept
	{
		return OSSwapInt64(value);
	}

# else

	inline uint16 SwapEndian(const uint16 value) noexcept
	{
		return (value << 8) | (value >> 8);
	}

	inline uint32 SwapEndian(const uint32 value) noexcept
	{
		uint32 ret = value << 24;
		ret |= (value & 0x0000FF00) << 8;
		ret |= (value & 0x00FF0000) >> 8;
		ret |= value >> 24;
		return ret;
	}

	inline uint64 SwapEndian(uint64 value) noexcept
	{
		value = ((value & 0x00000000FFFFFFFFull) << 32) | ((value & 0xFFFFFFFF00000000ull) >> 32);
		value = ((value & 0x0000FFFF0000FFFFull) << 16) | ((value & 0xFFFF0000FFFF0000ull) >> 16);
		value = ((value & 0x00FF00FF00FF00FFull) << 8) | ((value & 0xFF00FF00FF00FF00ull) >> 8);
		return value;
	}

# endif
}