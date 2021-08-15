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
	/// @brief PNG 圧縮時のフィルタ
	enum class ScriptCompileOption : uint32
	{
		Default = 0b00,

		BuildWithLineCues = 0b01,
	};
	DEFINE_BITMASK_OPERATORS(ScriptCompileOption);
}
