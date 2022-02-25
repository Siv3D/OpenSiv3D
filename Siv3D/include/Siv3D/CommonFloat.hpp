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
	/// @brief 異なる数値型どうしの計算結果として使う浮動小数点数型
	/// @tparam T 数値型
	/// @tparam U 数値型
# if __cpp_lib_concepts
	template <Concept::Arithmetic T, Concept::Arithmetic U>
# else
	template <class T, class U, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T>, std::is_arithmetic<U>>>* = nullptr>
# endif
	struct CommonFloat
	{
		using type = std::conditional_t<!std::is_floating_point_v<T> && !std::is_floating_point_v<U>, double, std::common_type_t<T, U>>;
	};

	/// @brief 異なる数値型どうしの計算結果として使う浮動小数点数型
	/// @tparam T 数値型
	/// @tparam U 数値型
# if __cpp_lib_concepts
	template <Concept::Arithmetic T, Concept::Arithmetic U>
# else
	template <class T, class U, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T>, std::is_arithmetic<U>>>* = nullptr>
# endif
	using CommonFloat_t = typename CommonFloat<T, U>::type;
}
