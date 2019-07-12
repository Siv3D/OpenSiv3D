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
# include <Siv3D/Monitor.hpp>
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

		Array<Size> GetFullscreenResolutions(const double minRefreshRate)
		{
			const Array<DisplayOutput> outputs = Graphics::EnumOutputs();
			const size_t currentMonitorIndex = System::GetCurrentMonitorIndex();

			if (currentMonitorIndex > outputs.size())
			{
				return{};
			}

			Array<Size> availableResolutions;

			for (const auto& displayMode : outputs[currentMonitorIndex].displayModes)
			{
				const Size resolution = displayMode.size;

				if ((displayMode.refreshRateHz > minRefreshRate)
					&& !availableResolutions.includes(resolution))
				{
					availableResolutions << resolution;
				}
			}

			return availableResolutions;
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
