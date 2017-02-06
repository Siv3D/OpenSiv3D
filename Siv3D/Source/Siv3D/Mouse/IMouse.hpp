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
# include <utility>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	constexpr uint32 MouseButtonCount = 8;

	struct InputState
	{
		MillisecondsF pressedDuration{ 0 };

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
				pressedDuration = stopwatch.elapsedF();

				stopwatch.reset();
			}
			else if (pressed)
			{
				pressedDuration = stopwatch.elapsedF();
			}
			else
			{
				pressedDuration = MillisecondsF(0);
			}
		}
	};

	class ISiv3DMouse
	{
	public:

		static ISiv3DMouse* Create();

		virtual ~ISiv3DMouse() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual bool down(uint32 index) const = 0;

		virtual bool pressed(uint32 index) const = 0;

		virtual bool up(uint32 index) const = 0;

		virtual MillisecondsF pressedDuration(uint32 index) const = 0;
	};
}
