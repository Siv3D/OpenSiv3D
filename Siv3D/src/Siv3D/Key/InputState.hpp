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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	struct InputState
	{
		Duration _pressedDuration{ 0 };

		Stopwatch stopwatch = Stopwatch{ true };

		bool up = false;

		bool pressed = false;

		bool down = false;

		void update(bool currentPressed)
		{
			const bool previousPressed = pressed;

			pressed = currentPressed;

			down = !previousPressed && pressed;

			up = previousPressed && !pressed;

			if (down)
			{
				stopwatch.restart();
			}
			else if (up)
			{
				_pressedDuration = stopwatch.elapsed();

				stopwatch.reset();
			}
			else if (pressed)
			{
				_pressedDuration = stopwatch.elapsed();
			}
			else
			{
				_pressedDuration = Duration(0);
			}
		}

		void clear()
		{
			_pressedDuration = Duration(0);

			stopwatch.restart();

			up = pressed = down = false;
		}
	};
}
