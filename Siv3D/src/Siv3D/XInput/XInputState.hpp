//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include <Siv3D/Common.hpp>
# include <Siv3D/DeadZone.hpp>
# include <Siv3D/Input/InputState.hpp>

namespace s3d
{
	struct XInputState
	{
		std::array<InputState, 16> buttons;

		double leftTrigger = 0.0, rightTrigger = 0.0;

		double lx = 0.0, ly = 0.0, rx = 0.0, ry = 0.0;

		std::array<DeadZone, 4> deadZones;

		XInputVibration vibration;

		bool vibrationPaused = false;

		bool connected = false;

		void reset()
		{
			for (auto& button : buttons)
			{
				button.reset();
			}

			leftTrigger = rightTrigger = 0.0;

			lx = ly = rx = ry = 0.0;

			vibration = {};

			vibrationPaused = false;

			connected = false;
		}
	};
}
