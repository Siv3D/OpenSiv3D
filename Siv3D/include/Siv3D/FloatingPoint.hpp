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

namespace s3d
{
	/// @brief 浮動小数点数値のビット列を整数として解釈します。
	/// @tparam Float32 float 型
	/// @param value float 型の値
	/// @return ビット列を整数として解釈した値
	template <class Float32, std::enable_if_t<std::is_same_v<Float32, float>>* = nullptr>
	[[nodiscard]]
	inline SIV3D_CONSTEXPR_BITCAST uint32 AsUint32(Float32 value) noexcept;

	/// @brief 浮動小数点数値のビット列を整数として解釈します。
	/// @tparam Float64 double 型
	/// @param value double 型の値
	/// @return ビット列を整数として解釈した値
	template <class Float64, std::enable_if_t<std::is_same_v<Float64, double>>* = nullptr>
	[[nodiscard]]
	inline SIV3D_CONSTEXPR_BITCAST uint64 AsUint64(Float64 value) noexcept;
}

# include "detail/FloatingPoint.ipp"
