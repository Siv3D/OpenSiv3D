//-----------------------------------------------
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
# if  __has_include(<bit>)
#	include <bit>
# endif
# include "Common.hpp"
# include "Concepts.hpp"

namespace s3d
{
	/// @brief 半精度浮動小数点数
	struct HalfFloat
	{
	private:

		uint16 m_bits;

	public:

		SIV3D_NODISCARD_CXX20
		HalfFloat() = default;

		SIV3D_NODISCARD_CXX20
		HalfFloat(float value) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		HalfFloat(Arithmetic value) noexcept;

		HalfFloat& operator =(float value) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		HalfFloat& operator =(Arithmetic value);

		[[nodiscard]]
		operator float() const noexcept;

		[[nodiscard]]
		bool operator ==(const HalfFloat other) const noexcept;

		[[nodiscard]]
		bool operator !=(const HalfFloat other) const noexcept;

		[[nodiscard]]
		uint16 getBits() const noexcept;

		void setBits(const uint16 bits) noexcept;

		[[nodiscard]]
		bool isNaN() const noexcept;

		[[nodiscard]]
		bool isInfinity() const noexcept;

		[[nodiscard]]
		int32 getSign() const noexcept;
	};
}

template <>
struct std::hash<s3d::HalfFloat>
{
	[[nodiscard]]
	size_t operator()(const s3d::HalfFloat& value) const noexcept
	{
		return std::hash<s3d::uint16>()(value.getBits());
	}
};

# include "detail/HalfFloat.ipp"
