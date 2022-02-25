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

namespace s3d
{
	SIV3D_CONCEPT_INTEGRAL_
	inline constexpr Byte operator <<(const Byte value, const Int shift) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(value) << shift));
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline constexpr Byte operator >>(const Byte value, const Int shift) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(value) >> shift));
	}

	inline constexpr Byte operator |(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) | static_cast<unsigned int>(y)));
	}

	inline constexpr Byte operator &(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) & static_cast<unsigned int>(y)));
	}

	inline constexpr Byte operator ^(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y)));
	}

	inline constexpr Byte operator ~(const Byte value) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(~static_cast<unsigned int>(value)));
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline constexpr Byte& operator <<=(Byte& value, const Int shift) noexcept
	{
		return value = (value << shift);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline constexpr Byte& operator >>=(Byte& value, const Int shift) noexcept
	{
		return value = (value >> shift);
	}

	inline constexpr Byte& operator |=(Byte& x, const Byte y) noexcept
	{
		return x = (x | y);
	}

	inline constexpr Byte& operator &=(Byte& x, const Byte y) noexcept
	{
		return x = (x & y);
	}

	inline constexpr Byte& operator ^=(Byte& x, const Byte y) noexcept
	{
		return x = (x ^ y);
	}

	inline constexpr uint8 AsUint8(const Byte value) noexcept
	{
		return static_cast<uint8>(value);
	}
}
