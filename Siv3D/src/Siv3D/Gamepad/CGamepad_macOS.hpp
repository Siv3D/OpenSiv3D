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

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/Optional.hpp>
# include "IGamepad.hpp"
# include "../Key/InputState.hpp"

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

		void clear()
		{
			buttons.clear();

			for (auto& pov : povs)
			{
				pov.clear();
			}

			povDegree.reset();

			axes.clear();

			info.index = 0;
			info.vendorID = info.productID = 0;
			info.name.clear();

			connected = false;
		}
	};

	class CGamepad : public ISiv3DGamepad
	{
	private:

		std::array<GamepadState, Gamepad.MaxUserCount> m_states;

		std::array<detail::Gamepad_impl, Gamepad.MaxUserCount> m_inputs;

	public:

		CGamepad();

		~CGamepad() override;

		bool init() override;

		void update(bool deviceChanged) override;

		bool isConnected(size_t userIndex) const override;

		const GamepadInfo& getInfo(size_t userIndex) const override;

		bool down(size_t userIndex, uint32 index) const override;

		bool pressed(size_t userIndex, uint32 index) const override;

		bool up(size_t userIndex, uint32 index) const override;

		MillisecondsF pressedDuration(size_t userIndex, uint32 index) const override;

		Optional<int32> povDegree(size_t userIndex) const override;

		const detail::Gamepad_impl& getInput(size_t userIndex) const override;
	};
}

# endif
