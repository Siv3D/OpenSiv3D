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

namespace s3d
{
	struct KeyEvent
	{
		uint64 timeMillisec = 0;

		uint32 eventIndex = 0;

		uint8 code = 0;

		bool down = false;

		bool up = false;
	};
}
