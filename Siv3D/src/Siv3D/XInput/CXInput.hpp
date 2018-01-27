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
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <XInput.h>
# include "IXInput.hpp"
# include "../Key/InputState.hpp"

namespace s3d
{
	struct XInputState
	{
		std::array<InputState, 16> buttons;

		double leftTrigger = 0.0, rightTrigger = 0.0;

		double lx = 0.0, ly = 0.0, rx = 0.0, ry = 0.0;

		std::array<DeadZone, 4> deadZones;

		std::pair<double, double> vibrations = { 0,0 };

		bool vibrationPaused = false;

		bool connected = false;

		void clear()
		{
			for (auto& button : buttons)
			{
				button.clear();
			}

			leftTrigger = rightTrigger = 0.0;

			lx = ly = rx = ry = 0.0;

			vibrations = { 0.0, 0.0 };

			vibrationPaused = false;

			connected = false;
		}
	};

	class CXInput : public ISiv3DXInput
	{
	private:

		HINSTANCE m_xInput = nullptr;

		decltype(XInputGetState)* p_XInputGetState = nullptr;
		
		decltype(XInputSetState)* p_XInputSetState = nullptr;

		bool m_initialized = false;

		std::array<XInputState, 4> m_states;

		std::array<detail::XInput_impl, 4> m_inputs;

	public:

		CXInput();

		~CXInput() override;

		bool init() override;

		void update(bool deviceChanged) override;

		bool isConnected(size_t userIndex) const override;

		void setDeadZone(size_t userIndex, DeadZoneIndex inputIndex, const DeadZone& deadZone) override;

		void setVibration(size_t userIndex, double leftMotorSpeed, double rightMotorSpeed) override;

		std::pair<double, double> getVibration(size_t userIndex) const override;

		void pauseVibration(size_t userIndex) override;

		void resumeVibration(size_t userIndex) override;

		bool down(size_t userIndex, uint32 index) const override;

		bool pressed(size_t userIndex, uint32 index) const override;

		bool up(size_t userIndex, uint32 index) const override;

		MillisecondsF pressedDuration(size_t userIndex, uint32 index) const override;

		const detail::XInput_impl& getInput(size_t userIndex) const override;
	};
}

# endif
