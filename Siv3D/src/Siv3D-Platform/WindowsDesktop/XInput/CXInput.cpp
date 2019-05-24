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

# include <Siv3D/DLL.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/XInput.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CXInput.hpp"

namespace s3d
{
	namespace detail
	{
		static double CalculateAxeValue(int32 pos, int32 min, int32 max)
		{
			const double center = (static_cast<double>(min) + max) * 0.5;

			const double range = static_cast<double>(max) - min;

			return range ? ((pos - center) * 2 / range) : 0.0;
		}
	}

	CXInput::CXInput()
		: m_inputs{{ detail::XInput_impl(0), detail::XInput_impl(1),
					 detail::XInput_impl(2), detail::XInput_impl(3) }}
	{

	}

	CXInput::~CXInput()
	{
		LOG_TRACE(U"CXInput::~CXInput()");

		if (m_xInput)
		{
			::FreeLibrary(m_xInput);
		}
	}

	void CXInput::init()
	{
		LOG_TRACE(U"CXInput::init()");

		m_xInput = DLL::LoadSystemLibrary(L"xinput1_4.dll");

		if (!m_xInput)
		{
			m_xInput = DLL::LoadSystemLibrary(L"xinput9_1_0.dll");
		}

		if (!m_xInput)
		{
			return;
		}

		p_XInputGetState = DLL::GetFunctionNoThrow(m_xInput, "XInputGetState");
		p_XInputSetState = DLL::GetFunctionNoThrow(m_xInput, "XInputSetState");

		if (!p_XInputGetState && !p_XInputSetState)
		{
			return;
		}

		m_initialized = true;
	
		LOG_INFO(U"ℹ️ CXInput initialized");

		update(true);
	}

	void CXInput::update(const bool deviceChanged)
	{
		if (!m_initialized)
		{
			return;
		}

		for (uint32 userIndex = 0; userIndex < XInput.MaxUserCount; ++userIndex)
		{
			auto& state = m_states[userIndex];

			if (!state.connected && !deviceChanged)
			{
				continue;
			}

			XINPUT_STATE xstate = {};

			const DWORD res = p_XInputGetState(userIndex, &xstate);

			if (res != ERROR_SUCCESS)
			{
				if (state.connected)
				{
					state.clear();

					LOG_INFO(U"🎮 XInput({}) disconnected"_fmt(userIndex));
				}

				continue;
			}
			
			if (!state.connected)
			{
				state.connected = true;

				LOG_INFO(U"🎮 XInput({}) connected"_fmt(userIndex));
			}

			for (uint32 i = 0; i < state.buttons.size(); ++i)
			{
				const bool currentPressed = !!(xstate.Gamepad.wButtons & (0x1u << i));
				state.buttons[i].update(currentPressed);
			}

			state.leftTrigger = state.deadZones[static_cast<int>(DeadZoneIndex::LefTrigger)].apply(xstate.Gamepad.bLeftTrigger / 255.0);
			state.rightTrigger = state.deadZones[static_cast<int>(DeadZoneIndex::RightTrigger)].apply(xstate.Gamepad.bRightTrigger / 255.0);

			state.lx = detail::CalculateAxeValue(xstate.Gamepad.sThumbLX, SHRT_MIN, SHRT_MAX);
			state.ly = detail::CalculateAxeValue(xstate.Gamepad.sThumbLY, SHRT_MIN, SHRT_MAX);
			state.deadZones[static_cast<int>(DeadZoneIndex::LeftThumb)].apply(state.lx, state.ly);

			state.rx = detail::CalculateAxeValue(xstate.Gamepad.sThumbRX, SHRT_MIN, SHRT_MAX);
			state.ry = detail::CalculateAxeValue(xstate.Gamepad.sThumbRY, SHRT_MIN, SHRT_MAX);
			state.deadZones[static_cast<int>(DeadZoneIndex::RightThumb)].apply(state.rx, state.ry);
		}

		for (uint32 userIndex = 0; userIndex < XInput.MaxUserCount; ++userIndex)
		{
			const auto& src = m_states[userIndex];
			auto& dst = m_inputs[userIndex];
			dst.leftTrigger = src.leftTrigger;
			dst.rightTrigger = src.rightTrigger;
			dst.leftThumbX = src.lx;
			dst.leftThumbY = src.ly;
			dst.rightThumbX = src.rx;
			dst.rightThumbY = src.ry;
		}
	}

	bool CXInput::isConnected(const size_t userIndex) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_states[userIndex].connected;
	}

	void CXInput::setDeadZone(const size_t userIndex, const DeadZoneIndex inputIndex, const DeadZone& deadZone)
	{
		assert(userIndex < XInput.MaxUserCount);

		m_states[userIndex].deadZones[static_cast<size_t>(inputIndex)] = deadZone;
	}

	void CXInput::setVibration(const size_t userIndex, double leftMotorSpeed, double rightMotorSpeed)
	{
		assert(userIndex < XInput.MaxUserCount);

		if (!m_initialized)
		{
			return;
		}

		leftMotorSpeed = Clamp(leftMotorSpeed, 0.0, 1.0);
		rightMotorSpeed = Clamp(rightMotorSpeed, 0.0, 1.0);

		const uint16 left = static_cast<uint16>(leftMotorSpeed * USHRT_MAX);
		const uint16 right = static_cast<uint16>(rightMotorSpeed * USHRT_MAX);
		XINPUT_VIBRATION vib{ left, right };
		p_XInputSetState(static_cast<DWORD>(userIndex), &vib);

		m_states[userIndex].vibrations = { leftMotorSpeed, rightMotorSpeed };
	}

	std::pair<double, double> CXInput::getVibration(const size_t userIndex) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_states[userIndex].vibrations;
	}

	void CXInput::pauseVibration(const size_t userIndex)
	{
		assert(userIndex < XInput.MaxUserCount);

		m_states[userIndex].vibrationPaused = true;

		XINPUT_VIBRATION vib{ 0, 0 };
		p_XInputSetState(static_cast<DWORD>(userIndex), &vib);
	}

	void CXInput::resumeVibration(const size_t userIndex)
	{
		assert(userIndex < XInput.MaxUserCount);

		if (m_states[userIndex].vibrationPaused)
		{
			m_states[userIndex].vibrationPaused = false;

			const uint16 left = static_cast<uint16>(m_states[userIndex].vibrations.first * USHRT_MAX);
			const uint16 right = static_cast<uint16>(m_states[userIndex].vibrations.second * USHRT_MAX);
			XINPUT_VIBRATION vib{ left, right };
			p_XInputSetState(static_cast<DWORD>(userIndex), &vib);
		}
	}

	bool CXInput::down(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_states[userIndex].buttons[index].down;
	}

	bool CXInput::pressed(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_states[userIndex].buttons[index].pressed;
	}

	bool CXInput::up(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_states[userIndex].buttons[index].up;
	}

	Duration CXInput::pressedDuration(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_states[userIndex].buttons[index]._pressedDuration;
	}

	const detail::XInput_impl& CXInput::getInput(const size_t userIndex) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_inputs[userIndex];
	}
}
