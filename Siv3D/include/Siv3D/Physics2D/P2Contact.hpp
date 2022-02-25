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
	/// @brief 2 つの物体に発生した衝突に関する情報
	struct P2Contact
	{
		/// @brief 衝突時した点の座標
		Vec2 point = { 0.0, 0.0 };
		
		/// @brief 衝突時の法線方向の力
		double normalImpulse = 0.0;
		
		/// @brief 衝突時の接線方向の力
		double tangentImpulse = 0.0;
	};
}
