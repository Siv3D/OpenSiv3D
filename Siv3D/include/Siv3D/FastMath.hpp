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
		/// @brief sin, cos を高速に近似計算します。
		/// @param angleRadians ラジアン角
		/// @return sin, cos の近似結果
		[[nodiscard]]
		inline constexpr std::pair<float, float> SinCos(float angleRadians) noexcept;

		/// @brief sin, cos を高速に近似計算します。
		/// @param angleRadians ラジアン角
		/// @return sin, cos の近似結果
		[[nodiscard]]
		inline constexpr std::pair<float, float> SinCos(double angleRadians) noexcept;

	# if __cpp_lib_bit_cast

		/// @brief 逆平方根を高速に近似計算します。
		/// @param x 逆平方根を計算する値
		/// @return 逆平方根の近似結果
		[[nodiscard]]
		inline constexpr float InvSqrt(float x) noexcept;

		/// @brief 逆平方根を高速に近似計算します。
		/// @param x 逆平方根を計算する値
		/// @return 逆平方根の近似結果
		[[nodiscard]]
		inline constexpr double InvSqrt(double x) noexcept;

		/// @brief 精度の高い逆平方根を高速に近似計算します。
		/// @param x 逆平方根を計算する値
		/// @remark `FastMath::InvSqrt()` よりもコストがかかりますが、結果の精度が向上します
		/// @return 逆平方根の近似結果
		[[nodiscard]]
		inline constexpr double InvSqrtQuality(double x) noexcept;

	# endif
	}
}

# include "detail/FastMath.ipp"
