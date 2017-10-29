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

# pragma once
# include <type_traits>
# include "Types.hpp"

namespace s3d
{
	enum class Byte : unsigned char { };

	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>* = nullptr>
	[[nodiscard]] inline constexpr Byte operator <<(const Byte value, const Integer shift) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(value) << shift));
	}

	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>* = nullptr>
	[[nodiscard]] inline constexpr Byte operator >>(const Byte value, const Integer shift) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(value) >> shift));
	}

	[[nodiscard]] inline constexpr Byte operator |(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) | static_cast<unsigned int>(y)));
	}

	[[nodiscard]] inline constexpr Byte operator &(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) & static_cast<unsigned int>(y)));
	}

	[[nodiscard]] inline constexpr Byte operator ^(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y)));
	}

	[[nodiscard]] inline constexpr Byte operator ~(const Byte value) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(~static_cast<unsigned int>(value)));
	}

	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>* = nullptr>
	inline constexpr Byte& operator <<=(Byte& value, const Integer shift) noexcept
	{
		return value = (value << shift);
	}

	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>* = nullptr>
	inline constexpr Byte& operator>>=(Byte& value, const Integer shift) noexcept
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


//////////////////////////////////////////////////
//
//	Streams
//
//////////////////////////////////////////////////

	COStream& operator <<(COStream& os, const Byte& value);

	WOStream& operator <<(WOStream& os, const Byte& value);
}
