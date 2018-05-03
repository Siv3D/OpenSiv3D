//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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

		void EnableAssetCreationWarning(const bool enabled)
		{
			Siv3DEngine::GetProfiler()->setAssetCreationWarningEnabled(enabled);
		}

		Statistics GetStatistics()
		{
			return Siv3DEngine::GetProfiler()->getStatistics();
		}
	}
}
