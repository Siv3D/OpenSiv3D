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
# include "Random.hpp"
# include "Duration.hpp"

namespace s3d
{
	/// @brief 現在のスレッドの乱数エンジンを用いて、0 以上 max 以下の範囲の時間を生成して返します。
	/// @param max 生成する時間の最大値
	/// @return 生成されたランダムな時間
	[[nodiscard]]
	inline Duration Random(const Duration& max) noexcept;

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Duration Random(const Duration& max, URBG&& urbg) noexcept;

	/// @brief 現在のスレッドの乱数エンジンを用いて、min 以上 max 以下の範囲の時間を生成して返します。
	/// @param min 生成する時間の最小値
	/// @param max 生成する時間の最大値
	/// @return 生成されたランダムな時間
	[[nodiscard]]
	inline Duration Random(const Duration& min, const Duration& max) noexcept;

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Duration Random(const Duration& min, const Duration& max, URBG&& urbg) noexcept;
}

# include "detail/RandomDuration.ipp"
