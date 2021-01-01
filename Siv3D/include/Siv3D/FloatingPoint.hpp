//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	/// 浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	template <class Float32, std::enable_if_t<std::is_same_v<Float32, float>>* = nullptr>
	[[nodiscard]]
	inline SIV3D_CONSTEXPR_BITCAST uint32 AsUint32(Float32 value) noexcept;

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	/// 浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	template <class Float64, std::enable_if_t<std::is_same_v<Float64, double>>* = nullptr>
	[[nodiscard]]
	inline SIV3D_CONSTEXPR_BITCAST uint64 AsUint64(Float64 value) noexcept;
}

# include "detail/FloatingPoint.ipp"
