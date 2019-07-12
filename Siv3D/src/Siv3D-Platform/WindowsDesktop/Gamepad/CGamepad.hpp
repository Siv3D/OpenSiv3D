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
# include <Siv3D/Windows.hpp>
# include <Siv3D/Optional.hpp>
# include <Gamepad/IGamepad.hpp>
# include <Key/InputState.hpp>

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

		void init() override;

		void update(bool deviceChanged) override;

		bool isConnected(size_t userIndex) const override;

		const GamepadInfo& getInfo(size_t userIndex) const override;

		bool down(size_t userIndex, uint32 index) const override;

		bool pressed(size_t userIndex, uint32 index) const override;

		bool up(size_t userIndex, uint32 index) const override;

		Duration pressedDuration(size_t userIndex, uint32 index) const override;

		Optional<int32> povDegree(size_t userIndex) const override;

		const detail::Gamepad_impl& getInput(size_t userIndex) const override;
	};
}
