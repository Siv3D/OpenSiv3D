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
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>

namespace s3d
{
	/// @brief 下線のスタイル
	enum class UnderlineStyle : uint8
	{
		/// @brief スタイルなし
		NoStyle = 0,
		/// @brief 実線(_________________)
		Underline = 1 << 0,
		/// @brief 破線(_ _ _ _ _ _ _ _ _)
		DashedUnderline = 1 << 1,
		/// @brief 下線のマスク
		UnderlineMask = 0b11, 
		/// @brief 反転(█████████████████)
		Highlight = 1 << 2
	};
	DEFINE_BITMASK_OPERATORS(UnderlineStyle)
}
