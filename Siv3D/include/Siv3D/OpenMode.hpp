//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>

namespace s3d
{
	/// @brief ファイルのオープンモード
	enum class OpenMode : uint8
	{
		/// @brief 新規作成
		Trunc			= 1 << 1,

		/// @brief 追加
		Append			= 1 << 2,
	};
	DEFINE_BITMASK_OPERATORS(OpenMode);
}
