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

namespace s3d
{
	/// @brief 物体の種類に関するフラグ
	enum class P2BodyType : uint8
	{
		/// @brief 物体は常に固定され、力の影響を受けません。地面や壁などに使います。
		Static,

		/// @brief 物体は力の影響を受けませんが、移動することができます。動く床などに使います。
		Kinematic,

		/// @brief 物体は力の影響を受けて動き回ります。
		Dynamic
	};
}
