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
# include <Siv3D/Gamepad/IGamepad.hpp>
# include <Siv3D/Gamepad/GamepadState.hpp>

namespace s3d
{
	class CGamepad final : public ISiv3DGamepad
	{
	public:

		CGamepad();

		~CGamepad() override;

		void init() override;

		void update() override;

		Array<GamepadInfo> enumerate() override;

		bool isConnected(size_t playerIndex) override;

		const GamepadInfo& getInfo(size_t playerIndex) override;

		bool down(size_t playerIndex, uint32 index) override;

		bool pressed(size_t playerIndex, uint32 index) override;

		bool up(size_t playerIndex, uint32 index) override;

		void clearInput(size_t playerIndex, uint32 index) override;

		bool cleared(size_t playerIndex, uint32 index) override;

		Duration pressedDuration(size_t playerIndex, uint32 index) override;

		Optional<int32> povDegree(size_t playerIndex) override;

		const detail::Gamepad_impl& getInput(size_t playerIndex) override;

	private:
		
		std::array<GamepadState, Gamepad.MaxPlayerCount> m_states;

		std::array<detail::Gamepad_impl, Gamepad.MaxPlayerCount> m_inputs;
	};
}
