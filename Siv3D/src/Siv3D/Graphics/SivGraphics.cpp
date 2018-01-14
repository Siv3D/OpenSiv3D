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
# include "IGraphics.hpp"

namespace s3d
{
	namespace Graphics
	{
		void SetBackground(const ColorF& color)
		{
			Siv3DEngine::GetGraphics()->setClearColor(color);
		}

		Array<DisplayOutput> EnumOutputs()
		{
			return Siv3DEngine::GetGraphics()->enumOutputs();
		}

		bool SetFullScreen(const bool fullScreen, const Size& size, const size_t displayIndex, const double refreshRateHz)
		{
			return Siv3DEngine::GetGraphics()->setFullScreen(fullScreen, size, displayIndex, refreshRateHz);
		}

		void SetTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
		{
			Siv3DEngine::GetGraphics()->setTargetFrameRateHz(targetFrameRateHz);
		}

		Optional<double> GetTargetFrameRateHz()
		{
			return Siv3DEngine::GetGraphics()->getTargetFrameRateHz();
		}

		double GetDisplayRefreshRateHz()
		{
			return Siv3DEngine::GetGraphics()->getDisplayRefreshRateHz();
		}
	}
}
