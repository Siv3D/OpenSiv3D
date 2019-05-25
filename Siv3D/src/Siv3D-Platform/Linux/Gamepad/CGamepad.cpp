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

# include <Siv3D/PointVector.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CGamepad.hpp"

namespace s3d
{
	CGamepad::CGamepad()
		: m_inputs{ {detail::Gamepad_impl(0), detail::Gamepad_impl(1),
					detail::Gamepad_impl(2), detail::Gamepad_impl(3),
					detail::Gamepad_impl(4), detail::Gamepad_impl(5),
					detail::Gamepad_impl(6), detail::Gamepad_impl(7),
					detail::Gamepad_impl(8), detail::Gamepad_impl(9),
					detail::Gamepad_impl(10), detail::Gamepad_impl(11),
					detail::Gamepad_impl(12), detail::Gamepad_impl(13),
					detail::Gamepad_impl(14), detail::Gamepad_impl(15) } }
	{

	}

	CGamepad::~CGamepad()
	{
		LOG_TRACE(U"CGamepad::~CGamepad()");
	}

	void CGamepad::init()
	{
		LOG_TRACE(U"CGamepad::init()");

		update(true);

		LOG_INFO(U"ℹ️ Gamepad initialized");
	}

	void CGamepad::update(const bool)
	{
		/*
		for (uint32 userIndex = 0; userIndex < Gamepad.MaxUserCount; ++userIndex)
		{
			auto& state = m_states[userIndex];
			
			if (::glfwJoystickPresent(userIndex))
			{
				if (!state.connected)
				{
					unsigned vendorID = 0, productID = 0, version = 0;
					const char* name = siv3dGetJoystickInfo(userIndex, &vendorID, &productID, &version);
					
					if (!name)
					{
						continue;
					}
					
					state.info.index = userIndex;
					state.info.vendorID = vendorID;
					state.info.productID = productID;
					state.info.name = Unicode::Widen(name);
					
					// has connected
					state.connected = true;
					
					LOG_INFO(U"🎮 Gamepad({}) `{}` connected"_fmt(userIndex, state.info.name));
				}
				
				state.axes.clear();
				
				int32 axesCount = 0;
				
				if (const float* axes = ::glfwGetJoystickAxes(userIndex, &axesCount); axes && axesCount)
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
				
				if (const uint8* buttons = ::glfwGetJoystickButtons(userIndex, &buttonCount); buttons && buttonCount)
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
				
				const int32 d = siv3dGetJoystickHat(userIndex);
				
				if (d == -1)
				{
					state.povDegree = none;
				}
				else
				{
					state.povDegree = d * 45;
					
					const bool up = (d == 0) || (d == 1) || (d == 7);
					const bool right = (d == 3) || (d == 2) || (d == 1);
					const bool down = (d == 5) || (d == 4) || (d == 3);
					const bool left = (d == 7) || (d == 6) || (d == 5);
					
					state.povs[0].update(up);
					state.povs[1].update(right);
					state.povs[2].update(down);
					state.povs[3].update(left);
				}
			}
			else
			{
				if (state.connected)
				{
					LOG_INFO(U"🎮 Gamepad({}) `{}` disconnected"_fmt(userIndex, state.info.name));
					
					// has disconnected
					state.clear();
				}
			}
		}
		
		for (uint8 userIndex = 0; userIndex < Gamepad.MaxUserCount; ++userIndex)
		{
			const auto& src = m_states[userIndex];
			auto& dst = m_inputs[userIndex];
			
			dst.axes = src.axes;
			dst.buttons.clear();
			
			for (uint32 i = 0; i < src.buttons.size(); ++i)
			{
				dst.buttons << Key(InputDevice::Gamepad, static_cast<uint8>(i), userIndex);
			}
		}
		 */
	}

	bool CGamepad::isConnected(const size_t userIndex) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return m_states[userIndex].connected;
	}

	const GamepadInfo& CGamepad::getInfo(const size_t userIndex) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return m_states[userIndex].info;
	}

	bool CGamepad::down(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		if (index < m_states[userIndex].buttons.size())
		{
			return m_states[userIndex].buttons[index].down;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[userIndex].povs[index - 0x80u].down;
		}

		return false;
	}

	bool CGamepad::pressed(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < Gamepad.MaxUserCount);
		
		if (index < m_states[userIndex].buttons.size())
		{
			return m_states[userIndex].buttons[index].pressed;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[userIndex].povs[index - 0x80u].pressed;
		}

		return false;
	}

	bool CGamepad::up(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		if (index < m_states[userIndex].buttons.size())
		{
			return m_states[userIndex].buttons[index].up;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[userIndex].povs[index - 0x80u].up;
		}

		return false;
	}

	Duration CGamepad::pressedDuration(const size_t userIndex, const uint32 index) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		if (index < m_states[userIndex].buttons.size())
		{
			return m_states[userIndex].buttons[index]._pressedDuration;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[userIndex].povs[index - 0x80u]._pressedDuration;
		}

		return MillisecondsF(0.0);
	}

	Optional<int32> CGamepad::povDegree(const size_t userIndex) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return m_states[userIndex].povDegree;
	}

	const detail::Gamepad_impl& CGamepad::getInput(const size_t userIndex) const
	{
		assert(userIndex < Gamepad.MaxUserCount);

		return m_inputs[userIndex];
	}
}
