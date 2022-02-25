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
# if  __has_include(<bit>)
#	include <bit>
# endif
# if  __has_include(<compare>)
#	include <compare>
# endif
# include "Common.hpp"
# include "Concepts.hpp"

// 定数式ではreinterpret_castができず、bit_castが必須のため、
// bit_castが使えるときのみconstexprとするためのマクロ
# if __cpp_lib_bit_cast
# define SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE constexpr
# else
# define SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE
# endif

namespace s3d
{
	/// @brief 半精度浮動小数点数
	struct HalfFloat
	{
	public:

		SIV3D_NODISCARD_CXX20
		HalfFloat() = default;

		SIV3D_NODISCARD_CXX20
		SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE HalfFloat(float value) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE HalfFloat(Arithmetic value) noexcept;

		SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE HalfFloat& operator =(float value) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE HalfFloat& operator =(Arithmetic value);

		[[nodiscard]]
		SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE operator float() const noexcept;

		[[nodiscard]]
		constexpr bool operator ==(const HalfFloat other) const noexcept;

#if __cpp_impl_three_way_comparison
		[[nodiscard]]
		SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE auto operator <=>(const HalfFloat other) const noexcept;
#else
		[[nodiscard]]
		constexpr bool operator !=(const HalfFloat other) const noexcept;
#endif

		[[nodiscard]]
		constexpr uint16 getBits() const noexcept;

		constexpr void setBits(const uint16 bits) noexcept;

		[[nodiscard]]
		constexpr bool isNaN() const noexcept;

		[[nodiscard]]
		constexpr bool isInfinity() const noexcept;

		[[nodiscard]]
		constexpr int32 getSign() const noexcept;

	private:

		uint16 m_bits;
	};
}

template <>
struct std::hash<s3d::HalfFloat>
{
	[[nodiscard]]
	size_t operator ()(const s3d::HalfFloat& value) const noexcept
	{
		return std::hash<s3d::uint16>()(value.getBits());
	}
};

# include "detail/HalfFloat.ipp"

#undef SIV3D_CONSTEXPR_IF_BITCAST_AVAILABLE
