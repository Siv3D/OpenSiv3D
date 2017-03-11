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

		Rect desktopRect;

		int32 rotation;

		Array<DisplayMode> displayModes;
	};

	namespace Graphics
	{
		// [x] Windows | [ ] macOS | [ ] Linux
		void SetBackground(const ColorF& color);

		// [x] Windows | [ ] macOS | [ ] Linux
		Array<DisplayOutput> EnumOutputs();

		// [x] Windows | [ ] macOS | [ ] Linux
		bool SetFullScreen(bool fullScreen, const Size& size, size_t displayIndex = 0, double refreshRateHz = 60.0);
	}
}
