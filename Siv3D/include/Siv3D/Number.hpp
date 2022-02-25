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
# include <limits>
# include <cmath>
# include "Common.hpp"
# include "Concepts.hpp"

namespace s3d
{
	/// @brief 表現できる最大の数値
	/// @tparam Type 数値型
	template <class Type>
	constexpr Type Largest = std::numeric_limits<Type>::max();

	/// @brief 表現できる最小の数値
	/// @tparam Type 数値型
	template <class Type>
	constexpr Type Smallest = std::numeric_limits<Type>::lowest();

	/// @brief 正の無限大
	SIV3D_CONCEPT_FLOATING_POINT
	constexpr Float Inf = std::numeric_limits<Float>::infinity();

	/// @brief qNaN
	SIV3D_CONCEPT_FLOATING_POINT
	constexpr Float QNaN = std::numeric_limits<Float>::quiet_NaN();

	/// @brief sNaN
	SIV3D_CONCEPT_FLOATING_POINT
	constexpr Float SNaN = std::numeric_limits<Float>::signaling_NaN();

	/// @brief 数値が非数 (NaN) であるかを示します。
	/// @tparam Type 数値型
	/// @param value 数値
	/// @remark 無限は非数ではありません。
	/// @return 数値が非数 (NaN) である場合 true, それ以外の場合は false
	template <class Type>
	[[nodiscard]]
	inline bool IsNaN(Type value) noexcept;

	/// @brief 数値が有限値であるかを示します。
	/// @tparam Type 数値型
	/// @param value 数値
	/// @return 数値が有限値である場合 true, それ以外の場合は false
	template <class Type>
	[[nodiscard]]
	inline bool IsFinite(Type value) noexcept;

	/// @brief 数値が無限であるかを示します。
	/// @tparam Type 数値型
	/// @param value 数値
	/// @return 数値が無限である場合 true, それ以外の場合は false
	template <class Type>
	[[nodiscard]]
	inline bool IsInfinity(Type value) noexcept;
}

# include "detail/Number.ipp"
