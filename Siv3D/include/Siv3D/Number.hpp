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
# include <limits>
# include <cmath>
# include "Common.hpp"
# include "Concepts.hpp"

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
	SIV3D_CONCEPT_FLOATING_POINT
	constexpr Float Inf = std::numeric_limits<Float>::infinity();

	/// <summary>
	/// qNaN
	/// </summary>
	SIV3D_CONCEPT_FLOATING_POINT
	constexpr Float QNaN = std::numeric_limits<Float>::quiet_NaN();

	/// <summary>
	/// sNaN
	/// </summary>
	SIV3D_CONCEPT_FLOATING_POINT
	constexpr Float SNaN = std::numeric_limits<Float>::signaling_NaN();

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
	[[nodiscard]]
	inline bool IsNaN(Type value) noexcept;

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
	[[nodiscard]]
	inline bool IsFinite(Type value) noexcept;

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
	[[nodiscard]]
	inline bool IsInfinity(Type value) noexcept;
}

# include "detail/Number.ipp"
