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
# include "../Common.hpp"
# include "P2Fwd.hpp"

namespace s3d
{
	/// @brief 部品 (P2Shape) の材質
	struct P2Material
	{
		/// @brief 部品の密度 (kg / m^2) です。大きいほど面積当たりの重さが大きくなります。
		double density = 1.0;

		/// @brief 部品の反発係数です。大きいほど反発しやすくなります。通常は [0.0, 1.0] の範囲です。
		double restitution = 0.1;

		/// @brief 部品の摩擦係数です。大きいほど摩擦が働きます。通常は [0.0, 1.0] の範囲です。
		double friction = 0.2;

		/// @brief 反発が発生する速度の下限 (m/s)
		/// @remark 部品がこれ以上の速さでぶつかると反発します
		double restitutionThreshold = 1.0;
	};
}
