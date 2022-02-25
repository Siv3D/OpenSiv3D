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
	/// @brief PNG 圧縮時のフィルタ
	enum class PNGFilter : int32
	{
		None_	= 0x08,

		Sub		= 0x10,

		Up		= 0x20,

		Avg		= 0x40,

		Paeth	= 0x80,

		Default = (None_ | Sub | Up | Avg | Paeth),
	};
	DEFINE_BITMASK_OPERATORS(PNGFilter);
}
