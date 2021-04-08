//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CXInput.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CXInput::CXInput()
		: m_inputs{ { detail::XInput_impl{ 0 },
					  detail::XInput_impl{ 1 },
					  detail::XInput_impl{ 2 },
					  detail::XInput_impl{ 3 },
					  detail::XInput_impl{ 4 },
					  detail::XInput_impl{ 5 },
					  detail::XInput_impl{ 6 },
					  detail::XInput_impl{ 7 } } } {}

	CXInput::~CXInput()
	{
		LOG_SCOPED_TRACE(U"CXInput::~CXInput()");
	}

	void CXInput::init()
	{
		LOG_SCOPED_TRACE(U"CXInput::init()");

		m_gamePad = std::make_unique<DirectX::GamePad>();
	}

	void CXInput::update()
	{
		for (int32 playerIndex = 0; playerIndex < XInput.MaxPlayerCount; ++playerIndex)
		{
			auto& state = m_states[playerIndex];
			const bool previousConnected = state.connected;

			const auto caps = m_gamePad->GetCapabilities(playerIndex);
			const auto current = m_gamePad->GetState(playerIndex, DirectX::GamePad::DEAD_ZONE_NONE);

			state.connected = current.connected;

			if (caps.connected)
			{
				if (not previousConnected)
				{
					LOG_INFO(U"🎮 XInput({}) connected"_fmt(playerIndex));
				}

				state.buttons[0].update(current.dpad.up);
				state.buttons[1].update(current.dpad.down);
				state.buttons[2].update(current.dpad.left);
				state.buttons[3].update(current.dpad.right);
				state.buttons[4].update(current.buttons.start);
				state.buttons[5].update(current.buttons.back);
				state.buttons[6].update(current.buttons.leftStick);
				state.buttons[7].update(current.buttons.rightStick);
				state.buttons[8].update(current.buttons.leftShoulder);
				state.buttons[9].update(current.buttons.rightShoulder);
				state.buttons[12].update(current.buttons.a);
				state.buttons[13].update(current.buttons.b);
				state.buttons[14].update(current.buttons.x);
				state.buttons[15].update(current.buttons.y);

				state.leftTrigger = state.deadZones[FromEnum(DeadZoneIndex::LefTrigger)](current.triggers.left);
				state.rightTrigger = state.deadZones[FromEnum(DeadZoneIndex::RightTrigger)](current.triggers.right);

				{
					Vec2 leftThumb = state.deadZones[FromEnum(DeadZoneIndex::LeftThumb)](current.thumbSticks.leftX, current.thumbSticks.leftY);
					state.lx = leftThumb.x;
					state.ly = leftThumb.y;
				}

				{
					Vec2 rightThumb = state.deadZones[FromEnum(DeadZoneIndex::RightThumb)](current.thumbSticks.rightX, current.thumbSticks.rightY);
					state.rx = rightThumb.x;
					state.ry = rightThumb.y;
				}
			}
			else
			{
				if (previousConnected)
				{
					LOG_INFO(U"🎮 XInput({}) disconnected"_fmt(playerIndex));
				}

				state.clear();
			}

			auto& dst = m_inputs[playerIndex];
			dst.leftTrigger		= state.leftTrigger;
			dst.rightTrigger	= state.rightTrigger;
			dst.leftThumbX		= state.lx;
			dst.leftThumbY		= state.ly;
			dst.rightThumbX		= state.rx;
			dst.rightThumbY		= state.ry;
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

		m_states[playerIndex].vibration.leftMotor = Clamp(vibration.leftMotor, 0.0, 1.0);
		m_states[playerIndex].vibration.rightMotor = Clamp(vibration.rightMotor, 0.0, 1.0);
		m_states[playerIndex].vibration.leftTrigger = Clamp(vibration.leftTrigger, 0.0, 1.0);
		m_states[playerIndex].vibration.rightTrigger = Clamp(vibration.rightTrigger, 0.0, 1.0);

		m_gamePad->SetVibration(playerIndex,
			static_cast<float>(m_states[playerIndex].vibration.leftMotor),
			static_cast<float>(m_states[playerIndex].vibration.rightMotor),
			static_cast<float>(m_states[playerIndex].vibration.leftTrigger),
			static_cast<float>(m_states[playerIndex].vibration.rightTrigger));
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
		m_gamePad->SetVibration(playerIndex, 0.0f, 0.0f, 0.0f, 0.0f);
	}

	void CXInput::resumeVibration(const uint32 playerIndex)
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		if (m_states[playerIndex].vibrationPaused)
		{
			m_states[playerIndex].vibrationPaused = false;
			m_gamePad->SetVibration(playerIndex,
				static_cast<float>(m_states[playerIndex].vibration.leftMotor),
				static_cast<float>(m_states[playerIndex].vibration.rightMotor),
				static_cast<float>(m_states[playerIndex].vibration.leftTrigger),
				static_cast<float>(m_states[playerIndex].vibration.rightTrigger));
		}
	}

	bool CXInput::down(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].down;
	}

	bool CXInput::pressed(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].pressed;
	}

	bool CXInput::up(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].up;
	}

	Duration CXInput::pressedDuration(const uint32 playerIndex, const uint32 index) const
	{
		assert(playerIndex < XInput.MaxPlayerCount);

		return m_states[playerIndex].buttons[index].pressedDuration;
	}

	const detail::XInput_impl& CXInput::getInput(const uint32 playerIndex) const
	{
		return m_inputs[playerIndex];
	}
}
