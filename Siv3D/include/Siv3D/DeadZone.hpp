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
# include "PointVector.hpp"

namespace s3d
{
	/// @brief デッドゾーンの計算方式
	enum class DeadZoneType : uint8
	{
		/// @brief デッドゾーンなし
		None_,

		/// @brief 軸独立
		Independent,

		/// @brief 円形
		Circular
	};

	/// @brief デッドゾーンの設定
	struct DeadZone
	{
		/// @brief デッドゾーンの大きさ
		double size = 0.0;

		/// @brief 飽和地点
		double maxValue = 1.0;

		/// @brief デッドゾーンの計算方式
		DeadZoneType type = DeadZoneType::None_;

		[[nodiscard]]
		constexpr double operator ()(double value) const noexcept;

		[[nodiscard]]
		Vec2 operator ()(double x, double y) const noexcept;

		[[nodiscard]]
		Vec2 operator ()(Vec2 value) const noexcept;
	};
}

# include "detail/DeadZone.ipp"
