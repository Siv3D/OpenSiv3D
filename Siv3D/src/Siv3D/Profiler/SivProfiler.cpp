//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <Siv3D/Profiler.hpp>
# include "IProfiler.hpp"

namespace s3d
{
	namespace Profiler
	{
		int32 FPS()
		{
			return Siv3DEngine::Get<ISiv3DProfiler>()->getFPS();
		}

		void EnableAssetCreationWarning(const bool enabled)
		{
			Siv3DEngine::Get<ISiv3DProfiler>()->setAssetCreationWarningEnabled(enabled);
		}

		Statistics GetStatistics()
		{
			return Siv3DEngine::Get<ISiv3DProfiler>()->getStatistics();
		}
	}
}
