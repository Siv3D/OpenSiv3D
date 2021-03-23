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
# include "../Common.hpp"
# include "P2Fwd.hpp"

namespace s3d
{
	/// @brief 2 つの物体の接触に関する情報
	struct P2Contact
	{
		/// @brief 接している点の座標
		Vec2 point = { 0.0, 0.0 };
		
		/// @brief 法線方向の力
		double normalImpulse = 0.0;
		
		/// @brief 接線方向の力
		double tangentImpulse = 0.0;

		void clearImpulse() noexcept;
	};
}

# include "detail/P2Contact.ipp"
