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

# include <Siv3D/Graphics.hpp>
# include <Siv3DEngine.hpp>
# include "IGraphics.hpp"

namespace s3d
{
	namespace Graphics
	{
		void SkipClearScreen()
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->skipClearScreen();
		}

		void SetTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setTargetFrameRateHz(targetFrameRateHz);
		}

		Optional<double> GetTargetFrameRateHz()
		{
			return Siv3DEngine::Get<ISiv3DGraphics>()->getTargetFrameRateHz();
		}

		double GetDisplayRefreshRateHz()
		{
			return Siv3DEngine::Get<ISiv3DGraphics>()->getDisplayRefreshRateHz();
		}

		double GetDPIScaling()
		{
			return Siv3DEngine::Get<ISiv3DGraphics>()->getDPIScaling();
		}
	}
}
