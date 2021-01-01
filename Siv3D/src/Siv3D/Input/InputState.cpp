//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "InputState.hpp"

namespace s3d
{
	void InputState::update(const bool currentPressed)
	{
		const bool previousPressed = pressed;
		pressed	= currentPressed;
		down	= (!previousPressed && pressed);
		up		= (previousPressed && !pressed);

		if (down)
		{
			stopwatch.restart();
		}
		else if (up)
		{
			pressedDuration = stopwatch.elapsed();
			stopwatch.reset();
		}
		else if (pressed)
		{
			pressedDuration = stopwatch.elapsed();
		}
		else
		{
			pressedDuration = Duration{ 0 };
		}
	}

	void InputState::clear()
	{
		pressedDuration = Duration{ 0 };
		stopwatch.reset();
		up		= false;
		pressed	= false;
		down	= false;
	}
}
