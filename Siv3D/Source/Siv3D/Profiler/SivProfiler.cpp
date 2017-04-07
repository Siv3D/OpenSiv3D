//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "IProfiler.hpp"
# include <Siv3D/Profiler.hpp>

namespace s3d
{
	namespace Profiler
	{
		int32 FPS()
		{
			return Siv3DEngine::GetProfiler()->getFPS();
		}
	}
}
