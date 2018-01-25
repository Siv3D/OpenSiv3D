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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "CXInput.hpp"
# include "../EngineUtility.hpp"
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		static double CalculateAxeValue(int pos, int min, int max)
		{
			const double center = (min + max) * 0.5;

			const double range = max - min;

			return range ? ((pos - center) * 2 / range) : 0.0;
		}

		static double ApplyDeadZone(double value, const DeadZone& deadZone)
		{
			if (deadZone.type == DeadZoneType::None)
			{
				return value;
			}

			if (value < -deadZone.size)
			{
				value += deadZone.size;
			}
			else if (value > deadZone.size)
			{
				value -= deadZone.size;
			}
			else
			{
				return 0.0;
			}

			return Clamp(value / (deadZone.maxValue - deadZone.size), -1.0, 1.0);
		}

		static void ApplyDeadZone(double& x, double& y, const DeadZone& deadZone)
		{
			if (deadZone.type == DeadZoneType::None)
			{
				return;
			}
			else if (deadZone.type == DeadZoneType::Independent)
			{
				x = ApplyDeadZone(x, deadZone);
				y = ApplyDeadZone(y, deadZone);
				return;
			}

			const double lenSq = Vec2(x, y).lengthSq();
			const double t = ApplyDeadZone(lenSq, deadZone);
			const double scale = (t > 0.0) ? (t / lenSq)*1.001 : 0.0;

			x = Clamp(x * scale, -1.0, 1.0);
			y = Clamp(y * scale, -1.0, 1.0);
		}
	}

	CXInput::CXInput()
		: m_inputs{ detail::XInput_impl(0), detail::XInput_impl(1),
					detail::XInput_impl(2), detail::XInput_impl(3) }
	{

	}

	CXInput::~CXInput()
	{
		if (m_xInput)
		{
			::FreeLibrary(m_xInput);
		}
	}

	bool CXInput::init()
	{
		m_xInput = ::LoadLibraryW(L"xinput1_4.dll");

		if (!m_xInput)
		{
			m_xInput = ::LoadLibraryW(L"xinput9_1_0.dll");
		}

		if (!m_xInput)
		{
			return true;
		}

		p_XInputGetState = s3d::FunctionPointer(m_xInput, "XInputGetState");
		p_XInputSetState = s3d::FunctionPointer(m_xInput, "XInputSetState");

		if (!p_XInputGetState && !p_XInputSetState)
		{
			return true;
		}

		m_initialized = true;
	
		LOG_INFO(U"ℹ️ XInput initialized");

		update(true);

		return true;
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
				}

				continue;
			}
			
			if (!state.connected)
			{
				state.connected = true;
			}

			for (uint32 i = 0; i < state.buttons.size(); ++i)
			{
				const bool currentPressed = !!(xstate.Gamepad.wButtons & (0x1u << i));
				state.buttons[i].update(currentPressed);
			}

			state.leftTrigger = detail::ApplyDeadZone(xstate.Gamepad.bLeftTrigger / 255.0, state.deadZones[static_cast<int>(DeadZoneIndex::LefTrigger)]);
			state.rightTrigger = detail::ApplyDeadZone(xstate.Gamepad.bRightTrigger / 255.0, state.deadZones[static_cast<int>(DeadZoneIndex::RightTrigger)]);

			state.lx = detail::CalculateAxeValue(xstate.Gamepad.sThumbLX, SHRT_MIN, SHRT_MAX);
			state.ly = detail::CalculateAxeValue(xstate.Gamepad.sThumbLY, SHRT_MIN, SHRT_MAX);
			detail::ApplyDeadZone(state.lx, state.ly, state.deadZones[static_cast<int>(DeadZoneIndex::LeftThumb)]);

			state.rx = detail::CalculateAxeValue(xstate.Gamepad.sThumbRX, SHRT_MIN, SHRT_MAX);
			state.ry = detail::CalculateAxeValue(xstate.Gamepad.sThumbRY, SHRT_MIN, SHRT_MAX);
			detail::ApplyDeadZone(state.rx, state.ry, state.deadZones[static_cast<int>(DeadZoneIndex::RightThumb)]);
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

	MillisecondsF CXInput::pressedDuration(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_states[userIndex].buttons[index].pressedDuration;
	}

	const detail::XInput_impl& CXInput::getInput(const size_t userIndex) const
	{
		assert(userIndex < XInput.MaxUserCount);

		return m_inputs[userIndex];
	}
}

# endif
