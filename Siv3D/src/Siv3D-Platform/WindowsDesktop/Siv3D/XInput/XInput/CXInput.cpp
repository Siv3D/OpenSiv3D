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

# include "CXInput.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static double CalculateAxeValue(const int32 pos, const int32 min, const int32 max) noexcept
		{
			const double center = (static_cast<double>(min) + max) * 0.5;

			const double range = static_cast<double>(max) - min;

			return range ? ((pos - center) * 2 / range) : 0.0;
		}
	}

	CXInput::CXInput()
		: m_inputs{ { detail::XInput_impl{ 0 },
					  detail::XInput_impl{ 1 },
					  detail::XInput_impl{ 2 },
					  detail::XInput_impl{ 3 }} } {}

	CXInput::~CXInput()
	{
		LOG_SCOPED_TRACE(U"CXInput::~CXInput()");

		if (m_xInput)
		{
			::FreeLibrary(m_xInput);
		}
	}

	void CXInput::init()
	{
		LOG_SCOPED_TRACE(U"CXInput::init()");

		m_xInput = DLL::LoadSystemLibraryNoThrow(L"xinput1_4.dll");

		if (not m_xInput)
		{
			m_xInput = DLL::LoadSystemLibraryNoThrow(L"xinput9_1_0.dll");
		}

		if (not m_xInput)
		{
			return;
		}

		p_XInputGetState = DLL::GetFunctionNoThrow(m_xInput, "XInputGetState");
		p_XInputSetState = DLL::GetFunctionNoThrow(m_xInput, "XInputSetState");

		if ((not p_XInputGetState) || (not p_XInputSetState))
		{
			return;
		}

		m_initialized = true;

		update(true);
	}

	void CXInput::update(const bool deviceChanged)
	{
		if (not m_initialized)
		{
			return;
		}

		for (uint32 userIndex = 0; userIndex < XInput.MaxPlayerCount; ++userIndex)
		{
			auto& state = m_states[userIndex];

			if ((not state.connected) && (not deviceChanged))
			{
				continue;
			}

			XINPUT_STATE xstate = {};

			const DWORD res = p_XInputGetState(userIndex, &xstate);

			if (res != ERROR_SUCCESS)
			{
				if (state.connected)
				{
					state.reset();

					LOG_INFO(U"🎮 XInput({}) disconnected"_fmt(userIndex));
				}

				continue;
			}
			
			if (not state.connected)
			{
				state.connected = true;

				LOG_INFO(U"🎮 XInput({}) connected"_fmt(userIndex));
			}

			for (uint32 i = 0; i < state.buttons.size(); ++i)
			{
				const bool currentPressed = !!(xstate.Gamepad.wButtons & (0x1u << i));
				state.buttons[i].update(currentPressed);
			}

			state.leftTrigger = state.deadZones[static_cast<int>(DeadZoneIndex::LefTrigger)](xstate.Gamepad.bLeftTrigger / 255.0);
			state.rightTrigger = state.deadZones[static_cast<int>(DeadZoneIndex::RightTrigger)](xstate.Gamepad.bRightTrigger / 255.0);

			{
				state.lx = detail::CalculateAxeValue(xstate.Gamepad.sThumbLX, SHRT_MIN, SHRT_MAX);
				state.ly = detail::CalculateAxeValue(xstate.Gamepad.sThumbLY, SHRT_MIN, SHRT_MAX);

				Vec2 leftThumb = state.deadZones[FromEnum(DeadZoneIndex::LeftThumb)](state.lx, state.ly);
				state.lx = leftThumb.x;
				state.ly = leftThumb.y;
			}

			{
				state.rx = detail::CalculateAxeValue(xstate.Gamepad.sThumbRX, SHRT_MIN, SHRT_MAX);
				state.ry = detail::CalculateAxeValue(xstate.Gamepad.sThumbRY, SHRT_MIN, SHRT_MAX);

				Vec2 rightThumb = state.deadZones[FromEnum(DeadZoneIndex::RightThumb)](state.rx, state.ry);
				state.rx = rightThumb.x;
				state.ry = rightThumb.y;
			}
		}

		for (uint32 userIndex = 0; userIndex < XInput.MaxPlayerCount; ++userIndex)
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

	bool CXInput::isConnected(const uint32 playerIndex) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].connected;
	}

	void CXInput::setDeadZone(const uint32 playerIndex, const DeadZoneIndex inputIndex, const DeadZone& deadZone)
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		m_states[playerIndex].deadZones[static_cast<size_t>(inputIndex)] = deadZone;
	}

	void CXInput::setVibration(const uint32 playerIndex, const XInputVibration& vibration)
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		if (not m_initialized)
		{
			return;
		}

		const double leftMotorSpeed = Clamp(vibration.leftMotor, 0.0, 1.0);
		const double rightMotorSpeed = Clamp(vibration.rightMotor, 0.0, 1.0);

		const uint16 left = static_cast<uint16>(leftMotorSpeed * USHRT_MAX);
		const uint16 right = static_cast<uint16>(rightMotorSpeed * USHRT_MAX);
		XINPUT_VIBRATION vib{ left, right };
		p_XInputSetState(static_cast<DWORD>(playerIndex), &vib);

		m_states[playerIndex].vibration = { leftMotorSpeed, rightMotorSpeed };
	}

	const XInputVibration& CXInput::getVibration(const uint32 playerIndex) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].vibration;
	}

	void CXInput::pauseVibration(const uint32 playerIndex)
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		m_states[playerIndex].vibrationPaused = true;

		XINPUT_VIBRATION vib{ 0, 0 };
		p_XInputSetState(static_cast<DWORD>(playerIndex), &vib);
	}

	void CXInput::resumeVibration(const uint32 playerIndex)
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		if (m_states[playerIndex].vibrationPaused)
		{
			m_states[playerIndex].vibrationPaused = false;

			const uint16 left = static_cast<uint16>(m_states[playerIndex].vibration.leftMotor * USHRT_MAX);
			const uint16 right = static_cast<uint16>(m_states[playerIndex].vibration.rightMotor * USHRT_MAX);
			XINPUT_VIBRATION vib{ left, right };
			p_XInputSetState(static_cast<DWORD>(playerIndex), &vib);
		}
	}

	bool CXInput::down(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].down();
	}

	bool CXInput::pressed(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].pressed();
	}

	bool CXInput::up(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].up();
	}

	void CXInput::clearInput(const uint32 playerIndex, const uint32 index)
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		m_states[playerIndex].buttons[index].clearInput();
	}

	bool CXInput::cleared(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].cleared();
	}

	Duration CXInput::pressedDuration(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].pressedDuration;
	}

	const detail::XInput_impl& CXInput::getInput(const uint32 playerIndex) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_inputs[playerIndex];
	}
}
