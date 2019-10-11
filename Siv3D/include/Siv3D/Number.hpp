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
# include <type_traits>
# include <limits>
# include <cmath>

namespace s3d
{
	/// <summary>
	/// 表現できる最大の数値
	/// </summary>
	template <class Type>
	constexpr Type Largest = std::numeric_limits<Type>::max();

	/// <summary>
	/// 表現できる最小の数値
	/// </summary>
	template <class Type>
	constexpr Type Smallest = std::numeric_limits<Type>::lowest();

	/// <summary>
	/// 正の無限大
	/// </summary>
	template <class FloatingPoint>
	constexpr FloatingPoint Inf = std::numeric_limits<FloatingPoint>::infinity();

	/// <summary>
	/// qNaN
	/// </summary>
	template <class FloatingPoint>
	constexpr FloatingPoint QNaN = std::numeric_limits<FloatingPoint>::quiet_NaN();

	/// <summary>
	/// sNaN
	/// </summary>
	template <class FloatingPoint>
	constexpr FloatingPoint SNaN = std::numeric_limits<FloatingPoint>::signaling_NaN();
    
    /// <summary>
    /// 数値が非数 (NaN) であるかを示します。
    /// </summary>
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 数値が非数 (NaN) である場合 true, それ以外の場合は false
    /// </returns>
    template <class Type>
	[[nodiscard]] inline bool IsNaN([[maybe_unused]] const Type value)
    {
		if constexpr (std::is_floating_point_v<Type>)
		{
			return std::isnan(value);
		}
		else
		{
			return false;
		}
    }
    
    /// <summary>
    /// 数値が有限値であるかを示します。
    /// </summary>
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 数値が有限値である場合 true, それ以外の場合は false
    /// </returns>
    template <class Type>
	[[nodiscard]] inline bool IsFinite([[maybe_unused]] const Type value)
    {
		if constexpr (std::is_floating_point_v<Type>)
		{
			return std::isfinite(value);
		}
		else
		{
			return true;
		}
    }

    /// <summary>
    /// 数値が無限であるかを示します。
    /// </summary>
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 数値が無限である場合 true, それ以外の場合は false
    /// </returns>
    template <class Type>
	[[nodiscard]] inline bool IsInfinity([[maybe_unused]] const Type value)
    {
		if constexpr (std::is_floating_point_v<Type>)
		{
			return std::isinf(value);
		}
		else
		{
			return false;
		}
    }
}
