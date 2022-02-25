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
# include "Common.hpp"
# include "FormatData.hpp"
# include <ThirdParty/absl/numeric/int128.h>

namespace s3d
{
	/// @brief 符号付き 128-bit 整数型 | Signed integer type with width of 128 bits
	using int128 = absl::int128;

	/// @brief　符号無し 128-bit 整数型 | Unsigned integer type with width of 128 bits
	using uint128 = absl::uint128;

	[[nodiscard]]
	inline constexpr int128 MakeInt128(int64 high, uint64 low) noexcept;

	[[nodiscard]]
	inline constexpr uint128 MakeUint128(uint64 high, uint64 low) noexcept;

	void Formatter(FormatData& formatData, int128 value);

	void Formatter(FormatData& formatData, uint128 value);
}

# include "detail/Int128.ipp"
