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
# include "Common.hpp"
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>

namespace s3d
{
	/// @brief 編集中テキストの文字スタイル
	enum class EditingTextCharStyle
	{
		/// @brief スタイルなし
		NoStyle = 0,
		/// @brief 下線,実線(_________________)
		Underline = 1 << 0,
		/// @brief 下線,破線(_ _ _ _ _ _ _ _ _)
		DashedUnderline = 1 << 1,
		/// @brief 下線のマスク
		UnderlineMask = 0b11, 
		/// @brief 反転(█████████████████)
		Highlight = 1 << 2
	};
	DEFINE_BITMASK_OPERATORS(EditingTextCharStyle)
}
