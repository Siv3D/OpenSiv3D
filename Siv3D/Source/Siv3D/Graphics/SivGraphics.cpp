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
# include "IGraphics.hpp"

namespace s3d
{
	namespace Graphics
	{
		void SetSetBackground(const ColorF& color)
		{
			color;
		}

		Array<DisplayOutput> EnumOutputs()
		{
			return Siv3DEngine::GetGraphics()->enumOutputs();
		}

		bool SetFullScreen(const bool fullScreen, const Size& size, const size_t displayIndex, const double refreshRateHz)
		{
			return Siv3DEngine::GetGraphics()->setFullScreen(fullScreen, size, displayIndex, refreshRateHz);
		}
	}
}
