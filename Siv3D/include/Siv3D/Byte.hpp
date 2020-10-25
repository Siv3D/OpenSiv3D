﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <type_traits>
# include <functional>
# include "Common.hpp"
# include "FormatData.hpp"

namespace s3d
{
	/// @brief 1 バイトを表現する型
	enum class Byte : unsigned char {};

	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline constexpr Byte operator <<(Byte value, Int shift) noexcept;

	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline constexpr Byte operator >>(Byte value, Int shift) noexcept;

	[[nodiscard]]
	inline constexpr Byte operator |(Byte x, Byte y) noexcept;

	[[nodiscard]]
	inline constexpr Byte operator &(Byte x, Byte y) noexcept;

	[[nodiscard]]
	inline constexpr Byte operator ^(Byte x, Byte y) noexcept;

	[[nodiscard]]
	inline constexpr Byte operator ~(Byte value) noexcept;

	SIV3D_CONCEPT_INTEGRAL
	inline constexpr Byte& operator <<=(Byte& value, Int shift) noexcept;

	SIV3D_CONCEPT_INTEGRAL
	inline constexpr Byte& operator >>=(Byte& value, Int shift) noexcept;

	inline constexpr Byte& operator |=(Byte& x, Byte y) noexcept;

	inline constexpr Byte& operator &=(Byte& x, Byte y) noexcept;

	inline constexpr Byte& operator ^=(Byte& x, Byte y) noexcept;

	[[nodiscard]]
	inline constexpr uint8 AsUint8(Byte value) noexcept;
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Byte& value);

	std::ostream& operator <<(std::ostream& output, const Byte& value);

	std::wostream& operator <<(std::wostream& output, const Byte& value);

	std::istream& operator >>(std::istream& input, Byte& value);

	std::wistream& operator >>(std::wistream& input, Byte& value);
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

template <>
struct std::hash<s3d::Byte>
{
	[[nodiscard]]
	size_t operator()(const s3d::Byte& value) const noexcept
	{
		return hash<s3d::uint8>()(static_cast<s3d::uint8>(value));
	}
};

# include "detail/Byte.ipp"
