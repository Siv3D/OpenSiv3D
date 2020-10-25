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

# include <Siv3D/Profiler.hpp>
# include <Siv3D/Profiler/IProfiler.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Profiler
	{
		int32 FPS() noexcept
		{
			return SIV3D_ENGINE(Profiler)->getFPS();
		}
	}
}
