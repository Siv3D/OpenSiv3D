﻿//-----------------------------------------------
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
	}
}

# include "detail/FastMath.ipp"
