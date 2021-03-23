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
	/// @brief 部品 (P2Shape) のフィルタ
	/// @reamark 部品 (P2Shape) にカテゴリビットフラグを指定し、特定のビットフラグを持つ部品と干渉しないようにできます。
	struct P2Filter
	{
		uint16 categoryBits = 0b0000'0000'0000'0001;

		uint16 maskBits = 0b1111'1111'1111'1111;

		int16 groupIndex = 0;
	};
}
