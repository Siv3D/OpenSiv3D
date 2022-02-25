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

	/// @brief `P2BodyType::Static` の省略表記です。
	inline constexpr P2BodyType P2Static	= P2BodyType::Static;

	/// @brief `P2BodyType::Kinematic` の省略表記です。
	inline constexpr P2BodyType P2Kinematic	= P2BodyType::Kinematic;
	
	/// @brief `P2BodyType::Dynamic` の省略表記です。
	inline constexpr P2BodyType P2Dynamic	= P2BodyType::Dynamic;
}
