﻿//-----------------------------------------------
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
# include <limits>

namespace s3d
{
	/// <summary>
	/// 表現できる最大の数値を返します。
	/// </summary>
	/// <returns>
	/// 表現できる最大の数値
	/// </returns>
	template <class Type>
	[[nodiscard]] inline constexpr Type Largest()
	{
		return std::numeric_limits<Type>::max();
	}

	/// <summary>
	/// 表現できる最小の数値を返します。
	/// </summary>
	/// <returns>
	/// 表現できる最小の数値
	/// </returns>
	template <class Type>
	[[nodiscard]] inline constexpr Type Smallest()
	{
		return std::numeric_limits<Type>::lowest();
	}

	/// <summary>
	/// 正の無限大を返します。
	/// </summary>
	/// <returns>
	/// 正の無限大
	/// </returns>
	template <class Type, std::enable_if_t<std::is_floating_point_v<Type>>* = nullptr>
	[[nodiscard]] inline constexpr Type Infinity()
	{
		return std::numeric_limits<Type>::infinity();
	}
    
    /// <summary>
    /// 数値が非数 (NaN) であるかを示します。
    /// </summary>
    /// <param name="value">
    /// 数値
    /// </param>
    /// <returns>
    /// 数値が非数 (NaN) である場合 true, それ以外の場合は false
    /// </returns>
    template <class Type, std::enable_if_t<std::is_floating_point_v<Type>>* = nullptr>
	[[nodiscard]] inline bool IsNaN(const Type value)
    {
        return std::isnan(value);
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
