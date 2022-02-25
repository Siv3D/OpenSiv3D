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
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief ゲームパッドの情報
	struct GamepadInfo
	{
		/// @brief 現在接続されているプレイヤーインデックス
		uint32 playerIndex = 0;

		/// @brief ベンダー ID
		uint32 vendorID = 0;

		/// @brief プロダクト ID
		uint32 productID = 0;

		/// @brief ゲームパッドの名称
		String name;
	};

	namespace System
	{
		/// @brief 使用可能なゲームパッドの一覧を返します。
		/// @return 使用可能なゲームパッドの一覧
		[[nodiscard]]
		Array<GamepadInfo> EnumerateGamepads();
	}
}
