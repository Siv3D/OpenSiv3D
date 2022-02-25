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
	struct ProfilerStat
	{
		uint32 drawCalls = 0;

		uint32 triangleCount = 0;

		uint32 textureCount = 0;

		uint32 fontCount = 0;

		uint32 audioCount = 0;

		uint32 activeVoice = 0;

		void print() const;
	};
}
