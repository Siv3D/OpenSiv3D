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
# include <Siv3D/Array.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/GamepadInfo.hpp>
# include <Siv3D/Input/InputState.hpp>

namespace s3d
{
	struct GamepadState
	{
		Array<InputState> buttons;

		std::array<InputState, 4> povs; // up, right, down, left

		Optional<int32> povDegree;

		Array<double> axes;

		GamepadInfo info;

		bool connected = false;

		void reset()
		{
			buttons.clear();

			for (auto& pov : povs)
			{
				pov.reset();
			}

			povDegree.reset();
			axes.clear();
			info = {};
			connected = false;
		}
	};

	namespace detail
	{
		[[nodiscard]]
		inline constexpr int32 GetPOVDirection(const bool up, const bool right, const bool down, const bool left) noexcept
		{
			if (up && left)
				return 7;
			else if (up && right)
				return 1;
			else if (up)
				return 0;
			else if (down && left)
				return 5;
			else if (down && right)
				return 3;
			else if (down)
				return 4;
			else if (left)
				return 6;
			else if (right)
				return 2;

			return -1;
		}
	}
}
