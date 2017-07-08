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

# pragma once
# include "Fwd.hpp"
# include "Rectangle.hpp"
# include "Array.hpp"

namespace s3d
{
	struct DisplayMode
	{
		Size size;

		double refreshRateHz;
	};

	struct DisplayOutput
	{
		String name;

		Rect displayRect;

		int32 rotation;

		Array<DisplayMode> displayModes;
	};

	namespace Graphics
	{
		void SetBackground(const ColorF& color);

		Array<DisplayOutput> EnumOutputs();

		bool SetFullScreen(bool fullScreen, const Size& size, size_t displayIndex = 0, double refreshRateHz = 60.0);

		void SetTargetFrameRateHz(const Optional<double>& targetFrameRateHz);

		Optional<double> GetTargetFrameRateHz();

		double GetDisplayRefreshRateHz();
	}
}
