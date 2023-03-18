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

# include <Siv3D/DLL.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CGamepad.hpp"

namespace s3d
{
	CGamepad::CGamepad()
		: m_states()
		, m_inputs{ {detail::Gamepad_impl(0), detail::Gamepad_impl(1),
					detail::Gamepad_impl(2), detail::Gamepad_impl(3),
					detail::Gamepad_impl(4), detail::Gamepad_impl(5),
					detail::Gamepad_impl(6), detail::Gamepad_impl(7),
					detail::Gamepad_impl(8), detail::Gamepad_impl(9),
					detail::Gamepad_impl(10), detail::Gamepad_impl(11),
					detail::Gamepad_impl(12), detail::Gamepad_impl(13),
					detail::Gamepad_impl(14), detail::Gamepad_impl(15) } } {}

	CGamepad::~CGamepad()
	{
		LOG_SCOPED_TRACE(U"CGamepad::~CGamepad()");

		for (int32 jid = 0; jid < Gamepad.MaxPlayerCount; ++jid)
		{
			detail::CloseJoystick(m_data.joysticks.data() + jid);
		}

		if (m_data.dinput)
		{
			m_data.dinput->Release();
			m_data.dinput = nullptr;
		}
	}

	void CGamepad::init()
	{
		LOG_SCOPED_TRACE(U"CGamepad::init()");
	}

	void CGamepad::update()
	{
		if (not m_initialized)
		{
			return;
		}

		{
			constexpr bool PollAll = true;

			std::lock_guard lock{ m_mutex };

			for (auto& joystick : m_data.joysticks)
			{
				if (joystick.present)
				{
					pollJoystick(&joystick, PollAll);
				}
			}

			m_currentInputs = m_data.joysticks;
		}

		for (uint32 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			auto& state = m_states[playerIndex];
			const auto& src = m_currentInputs[playerIndex];

			if (src.present)
			{
				if (not state.connected)
				{
					state.info.playerIndex	= playerIndex;
					state.info.vendorID		= src.vendorID;
					state.info.productID	= src.productID;
					state.info.name			= src.name;

					// has connected
					state.connected = true;

					LOG_INFO(U"🎮 Gamepad({}) `{}` connected"_fmt(playerIndex, state.info.name));
				}

				// axes
				{
					state.axes = src.axes.map([](float value) { return static_cast<double>(value); });
				}

				// buttons
				{
					const size_t buttonCount = src.buttons.size();
					state.buttons.resize(buttonCount);

					for (size_t i = 0; i < buttonCount; ++i)
					{
						const bool currentPressed = !!(src.buttons[i]);
						state.buttons[i].update(currentPressed);
					}
				}

				// hats
				{
					const size_t hatCount = src.hats.size();

					if (hatCount)
					{
						const bool up		= !!(src.hats[0] & detail::GLFW_HAT_UP);
						const bool right	= !!(src.hats[0] & detail::GLFW_HAT_RIGHT);
						const bool down		= !!(src.hats[0] & detail::GLFW_HAT_DOWN);
						const bool left		= !!(src.hats[0] & detail::GLFW_HAT_LEFT);

						state.povs[0].update(up);
						state.povs[1].update(right);
						state.povs[2].update(down);
						state.povs[3].update(left);

						if ((not up) && (not right) && (not down) && (not left))
						{
							state.povDegree = none;
						}
						else
						{
							state.povDegree = detail::GetPOVDirection(up, right, down, left) * 45;
						}
					}
					else
					{
						state.povDegree = none;
					}
				}
			}
			else
			{
				if (state.connected)
				{
					LOG_INFO(U"🎮 Gamepad({}) `{}` disconnected"_fmt(playerIndex, state.info.name));

					state.reset();
				}
			}
		}

		for (uint32 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			const auto& src = m_states[playerIndex];
			auto& dst = m_inputs[playerIndex];

			dst.axes = src.axes;
			dst.buttons.clear();

			for (uint32 i = 0; i < src.buttons.size(); ++i)
			{
				dst.buttons.emplace_back(InputDeviceType::Gamepad, static_cast<uint8>(i), static_cast<uint8>(playerIndex));
			}
		}
	}

	Array<GamepadInfo> CGamepad::enumerate()
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		Array<GamepadInfo> result;

		for (uint32 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			const auto& joystick = m_currentInputs[playerIndex];

			if (not joystick.present)
			{
				continue;
			}

			const GamepadInfo info
			{
				.playerIndex	= playerIndex,
				.vendorID		= joystick.vendorID,
				.productID		= joystick.productID,
				.name			= joystick.name,
			};

			result << info;
		}

		return result;
	}

	bool CGamepad::isConnected(const size_t playerIndex)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_states[playerIndex].connected;
	}

	const GamepadInfo& CGamepad::getInfo(const size_t playerIndex)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_states[playerIndex].info;
	}

	bool CGamepad::down(const size_t playerIndex, const uint32 index)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			return m_states[playerIndex].buttons[index].down();
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].down();
		}

		return false;
	}

	bool CGamepad::pressed(const size_t playerIndex, const uint32 index)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			return m_states[playerIndex].buttons[index].pressed();
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].pressed();
		}

		return false;
	}

	bool CGamepad::up(const size_t playerIndex, const uint32 index)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			return m_states[playerIndex].buttons[index].up();
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].up();
		}

		return false;
	}

	void CGamepad::clearInput(const size_t playerIndex, const uint32 index)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			m_states[playerIndex].buttons[index].clearInput();
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			m_states[playerIndex].povs[(index - 0x80u)].clearInput();
		}
	}

	bool CGamepad::cleared(const size_t playerIndex, const uint32 index)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			return m_states[playerIndex].buttons[index].cleared();
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].cleared();
		}

		return false;
	}

	Duration CGamepad::pressedDuration(const size_t playerIndex, const uint32 index)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			return m_states[playerIndex].buttons[index].pressedDuration;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].pressedDuration;
		}

		return Duration{ 0.0 };
	}

	Optional<int32> CGamepad::povDegree(const size_t playerIndex)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_states[playerIndex].povDegree;
	}

	const detail::Gamepad_impl& CGamepad::getInput(const size_t playerIndex)
	{
		if (not m_initialized)
		{
			initDirectInput();
		}

		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_inputs[playerIndex];
	}

	void CGamepad::detectJoystickConnection()
	{
		if (not m_initialized)
		{
			return;
		}

		LOG_TRACE(U"CGamepad::detectJoystickConnection()");

		if (not m_data.dinput)
		{
			return;
		}

		std::lock_guard lock{ m_mutex };

		if (FAILED(m_data.dinput->EnumDevices(DI8DEVCLASS_GAMECTRL, detail::DeviceCallback, &m_data, DIEDFL_ATTACHEDONLY)))
		{
			return;
		}
	}

	void CGamepad::detectJoystickDisconnection()
	{
		if (not m_initialized)
		{
			return;
		}

		LOG_TRACE(U"CGamepad::detectJoystickDisconnection()");

		if (not m_data.dinput)
		{
			return;
		}

		std::lock_guard lock{ m_mutex };

		for (int32 jid = 0; jid < Gamepad.MaxPlayerCount; ++jid)
		{
			detail::GLFWjoystick* js = (m_data.joysticks.data() + jid);

			if (js->present)
			{
				pollJoystick(js, false);
			}
		}
	}

	void CGamepad::initDirectInput()
	{
		assert(not m_initialized);

		LOG_TRACE(U"CoCreateInstance(CLSID_DirectInput8)");

		if (FAILED(::CoCreateInstance(CLSID_DirectInput8, nullptr, CLSCTX_INPROC_SERVER, IID_IDirectInput8W, (void**)&m_data.dinput)))
		{
			return;
		}

		LOG_TRACE(U"IDirectInput8W->Initialize()");

		if (FAILED(m_data.dinput->Initialize(::GetModuleHandle(nullptr), DIRECTINPUT_VERSION)))
		{
			return;
		}

		m_initialized = true;

		detectJoystickConnection();

		update();
	}

	//
	// modified version of glfw/src/win32_joystick.c
	// 
	//========================================================================
	// GLFW 3.4 Win32 - www.glfw.org
	//------------------------------------------------------------------------
	// Copyright (c) 2002-2006 Marcus Geelnard
	// Copyright (c) 2006-2019 Camilla Löwy <elmindreda@glfw.org>
	//
	// This software is provided 'as-is', without any express or implied
	// warranty. In no event will the authors be held liable for any damages
	// arising from the use of this software.
	//
	// Permission is granted to anyone to use this software for any purpose,
	// including commercial applications, and to alter it and redistribute it
	// freely, subject to the following restrictions:
	//
	// 1. The origin of this software must not be misrepresented; you must not
	//    claim that you wrote the original software. If you use this software
	//    in a product, an acknowledgment in the product documentation would
	//    be appreciated but is not required.
	//
	// 2. Altered source versions must be plainly marked as such, and must not
	//    be misrepresented as being the original software.
	//
	// 3. This notice may not be removed or altered from any source
	//    distribution.
	//

	bool CGamepad::pollJoystick(detail::GLFWjoystick* js, const bool pollAll)
	{
		if (js->win32.device)
		{
			HRESULT result;
			DIJOYSTATE2 state;

			IDirectInputDevice8_Poll(js->win32.device);
			result = IDirectInputDevice8_GetDeviceState(js->win32.device, sizeof(state), &state);

			if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
			{
				IDirectInputDevice8_Acquire(js->win32.device);
				IDirectInputDevice8_Poll(js->win32.device);
				result = IDirectInputDevice8_GetDeviceState(js->win32.device, sizeof(state), &state);
			}

			if (FAILED(result))
			{
				CloseJoystick(js);
				LOG_INFO(U"🎮 Gamepad({}) disconnected"_fmt(js - m_data.joysticks.data()));
				return false;
			}

			if (not pollAll)
			{
				return true;
			}

			int32 ai = 0, bi = 0, pi = 0;

			for (int32 i = 0; i < js->win32.objectCount; ++i)
			{
				const void* data = (char*)&state + js->win32.objects[i].offset;

				switch (js->win32.objects[i].type)
				{
				case detail::_GLFW_TYPE_AXIS:
				case detail::_GLFW_TYPE_SLIDER:
					{
						const LONG value = *((LONG*)data);
						js->axes[ai] = (value < 0.0) ? (value / 32768.0f) : (value / 32767.0f);
						ai++;
						break;
					}

				case detail::_GLFW_TYPE_BUTTON:
					{
						const char value = (*((BYTE*)data) & 0x80) != 0;
						js->buttons[bi] = value;
						bi++;
						break;
					}

				case detail::_GLFW_TYPE_POV:
					{
						const uint32 states[9] =
						{
							detail::GLFW_HAT_UP,
							detail::GLFW_HAT_RIGHT_UP,
							detail::GLFW_HAT_RIGHT,
							detail::GLFW_HAT_RIGHT_DOWN,
							detail::GLFW_HAT_DOWN,
							detail::GLFW_HAT_LEFT_DOWN,
							detail::GLFW_HAT_LEFT,
							detail::GLFW_HAT_LEFT_UP,
							detail::GLFW_HAT_CENTERED
						};

						// Screams of horror are appropriate at this point
						int stateIndex = LOWORD(*(DWORD*)data) / (45 * DI_DEGREES);
						if (stateIndex < 0 || stateIndex > 8)
							stateIndex = 8;

						const size_t buttonCount = (js->buttons.size() - js->hats.size() * 4);
						const size_t base = (buttonCount + pi * 4);

						const uint32 value = states[stateIndex];
						js->buttons[base + 0] = (value & 0x01);
						js->buttons[base + 1] = (value & 0x02);
						js->buttons[base + 2] = (value & 0x04);
						js->buttons[base + 3] = (value & 0x08);
						js->hats[pi] = static_cast<uint8>(value);
						pi++;
						break;
					}
				}
			}
		}

		return true;
	}
}
