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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include "CGamepad.hpp"

extern "C"
{
	GLFWAPI const char* siv3dGetJoystickInfo(int joy, unsigned* vendorID, unsigned* productID, unsigned* version);
}

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

	}

	void CGamepad::init()
	{
		LOG_SCOPED_TRACE(U"CGamepad::init()");
		
		update();
	}

	void CGamepad::update()
	{
		for (uint32 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			auto& state = m_states[playerIndex];
			
			if (::glfwJoystickPresent(playerIndex))
			{
				if (not state.connected)
				{
					unsigned vendorID = 0, productID = 0, version = 0;
					const char* name = siv3dGetJoystickInfo(playerIndex, &vendorID, &productID, &version);
					
					if (!name)
					{
						continue;
					}
					
					state.info.playerIndex	= playerIndex;
					state.info.vendorID		= vendorID;
					state.info.productID	= productID;
					state.info.name = Unicode::Widen(name);
					
					// has connected
					state.connected = true;
					
					LOG_INFO(U"🎮 Gamepad({}) `{}` connected"_fmt(playerIndex, state.info.name));
				}
				
				state.axes.clear();
				
				int32 axesCount = 0;

				if (const float* axes = ::glfwGetJoystickAxes(playerIndex, &axesCount); axes && axesCount)
				{
					for (int32 i = 0; i < axesCount; ++i)
					{
						state.axes << axes[i];
					}
				}
				else
				{
					state.axes << 0.0 << 0.0;
				}

				int32 buttonCount = 0;
				
				if (const uint8* buttons = ::glfwGetJoystickButtons(playerIndex, &buttonCount); buttons && buttonCount)
				{
					state.buttons.resize(buttonCount);

					for (int32 i = 0; i < buttonCount; ++i)
					{
						const bool currentPressed = !!(buttons[i] & GLFW_PRESS);
						state.buttons[i].update(currentPressed);
					}
				}
				else
				{
					state.buttons.clear();
				}
				
				int32 hatCount = 0;
				
				if (const uint8* hats = ::glfwGetJoystickHats(playerIndex, &hatCount))
				{
					const bool up = !!(hats[0] & GLFW_HAT_UP);
					const bool right = !!(hats[0] & GLFW_HAT_RIGHT);
					const bool down = !!(hats[0] & GLFW_HAT_DOWN);
					const bool left = !!(hats[0] & GLFW_HAT_LEFT);
					
					state.povs[0].update(up);
					state.povs[1].update(right);
					state.povs[2].update(down);
					state.povs[3].update(left);
					
					if (!up && !right && !down && !left)
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
			else
			{
				if (state.connected)
				{
					LOG_INFO(U"🎮 Gamepad({}) `{}` disconnected"_fmt(playerIndex, state.info.name));
					
					// has disconnected
					state.reset();
				}
			}
		}
		
		for (uint8 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			const auto& src = m_states[playerIndex];
			auto& dst = m_inputs[playerIndex];
			
			dst.axes = src.axes;
			dst.buttons.clear();
			
			for (uint32 i = 0; i < src.buttons.size(); ++i)
			{
				dst.buttons.emplace_back(InputDeviceType::Gamepad, static_cast<uint8>(i), playerIndex);
			}
		}
	}

	Array<GamepadInfo> CGamepad::enumerate()
	{
		Array<GamepadInfo> results;
		
		for (uint32 playerIndex = 0; playerIndex < Gamepad.MaxPlayerCount; ++playerIndex)
		{
			unsigned vendorID = 0, productID = 0, version = 0;
			const char* name = siv3dGetJoystickInfo(playerIndex, &vendorID, &productID, &version);
			
			if (name)
			{
				GamepadInfo info;
				info.playerIndex	= playerIndex;
				info.vendorID		= vendorID;
				info.productID		= productID;
				info.name = Unicode::Widen(name);
				results << info;
			}
		}
		
		return results;
	}

	bool CGamepad::isConnected(const size_t playerIndex)
	{
		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_states[playerIndex].connected;
	}

	const GamepadInfo& CGamepad::getInfo(const size_t playerIndex)
	{
		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_states[playerIndex].info;
	}

	bool CGamepad::down(const size_t playerIndex, const uint32 index)
	{
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
		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_states[playerIndex].povDegree;
	}

	const detail::Gamepad_impl& CGamepad::getInput(const size_t playerIndex)
	{
		assert(playerIndex < Gamepad.MaxPlayerCount);

		return m_inputs[playerIndex];
	}
}
