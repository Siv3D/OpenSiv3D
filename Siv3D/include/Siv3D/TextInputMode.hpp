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
	enum class TextInputMode : uint32
	{
		DenyControl		= 0x00,

		AllowEnter		= 0x01,

		AllowTab		= 0x02,

		AllowBackSpace	= 0x04,

		AllowDelete		= 0x08,

		AllowEnterTab					= AllowEnter | AllowTab,

		AllowEnterBackSpace				= AllowEnter | AllowBackSpace,

		AllowEnterBackSpaceDelete		= AllowEnter | AllowBackSpace | AllowDelete,

		AllowTabBackSpace				= AllowTab | AllowBackSpace,

		AllowTabBackSpaceDelete			= AllowTab | AllowBackSpace | AllowDelete,

		AllowBackSpaceDelete			= AllowBackSpace | AllowDelete,

		AllowEnterTabBackSpace			= AllowEnter | AllowTab | AllowBackSpace,

		AllowEnterTabBackSpaceDelete	= AllowEnter | AllowTab | AllowBackSpace | AllowDelete,

		Default							= AllowEnterTabBackSpaceDelete,
	};
	DEFINE_BITMASK_OPERATORS(TextInputMode);
}
