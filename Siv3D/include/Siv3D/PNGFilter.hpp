﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>

namespace s3d
{
	enum class PNGFilter
	{
		None = 0x08,

		Sub = 0x10,

		Up = 0x20,

		Avg = 0x40,

		Paeth = 0x80,

		Default = None | Sub | Up | Avg | Paeth,
	};
	DEFINE_BITMASK_OPERATORS(PNGFilter);
}
