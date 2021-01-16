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
# include <utility>
# include "Common.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	namespace FastMath
	{
		/// @brief sin, cos の近似を高速に計算します。
		/// @param angleRadians ラジアン角
		/// @return sin, cos の近似結果
		[[nodiscard]]
		inline constexpr std::pair<float, float> SinCos(float angleRadians) noexcept;

		/// @brief sin, cos の近似を高速に計算します。
		/// @param angleRadians ラジアン角
		/// @return sin, cos の近似結果
		[[nodiscard]]
		inline constexpr std::pair<float, float> SinCos(double angleRadians) noexcept;

	# if __cpp_lib_bit_cast

		[[nodiscard]]
		inline constexpr float InvSqrt(float x) noexcept;

		[[nodiscard]]
		inline constexpr double InvSqrt(double x) noexcept;

		[[nodiscard]]
		inline constexpr double InvSqrtQuality(double x) noexcept;

	# endif
	}
}

# include "detail/FastMath.ipp"
