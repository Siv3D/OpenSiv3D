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
	namespace detail
	{
		String FindGamepadName(const int32 vendorID, const int32 productID);

		String GetDeviceName(const uint32 index, const wchar_t *szRegKey);

		constexpr static double CalculateAxeValue(int32 pos, int32 min, int32 max) noexcept
		{
			const int32 center = (min + max) / 2;
			const int32 r = (max - min) / 2;

			return r ? Clamp(static_cast<double>(pos - center) / r, -1.0, 1.0) : 0.0;
		}

		static constexpr int32 Get8Direction(const int32 angle)
		{
			const double deg = angle / 100.0;

			if (deg <= 22.5)
				return 0;
			else if (deg <= 67.5)
				return 1;
			else if (deg <= 112.5)
				return 2;
			else if (deg <= 157.5)
				return 3;
			else if (deg <= 202.5)
				return 4;
			else if (deg <= 247.5)
				return 5;
			else if (deg <= 292.5)
				return 6;
			else if (deg <= 337.5)
				return 7;
			else
				return 0;
		}
	}

	CGamepad::CGamepad()
		: m_states()
		, m_inputs{ {detail::Gamepad_impl(0), detail::Gamepad_impl(1),
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

	void CGamepad::update(const bool deviceChanged)
	{
		for (uint32 userIndex = 0; userIndex < Gamepad.MaxUserCount; ++userIndex)
		{
			auto& state = m_states[userIndex];

			JOYINFOEX info = {};
			info.dwSize = sizeof(JOYINFOEX);
			info.dwFlags = JOY_RETURNALL;
			JOYCAPSW caps = {};

			if ((state.connected || deviceChanged)
				&& (::joyGetPosEx(userIndex, &info) == JOYERR_NOERROR)
				&& (::joyGetDevCapsW(userIndex, &caps, sizeof(caps)) == JOYERR_NOERROR))
			{
				if (!state.connected)
				{
					state.info.index = userIndex;
					state.info.vendorID = caps.wMid;
					state.info.productID = caps.wPid;

					if (const auto name = detail::FindGamepadName(state.info.vendorID, state.info.productID))
					{
						state.info.name = name;
					}
					else
					{
						state.info.name = detail::GetDeviceName(userIndex, caps.szRegKey);
					}

					// has connected
					state.connected = true;

					LOG_INFO(U"🎮 Gamepad({}) `{}` connected"_fmt(userIndex, state.info.name));
				}

				state.axes.clear();
				state.axes << detail::CalculateAxeValue(info.dwXpos, caps.wXmin, caps.wXmax);
				state.axes << detail::CalculateAxeValue(info.dwYpos, caps.wYmin, caps.wYmax);

				if (caps.wCaps & JOYCAPS_HASZ)
				{
					state.axes << detail::CalculateAxeValue(info.dwZpos, caps.wZmin, caps.wZmax);
				}

				if (caps.wCaps & JOYCAPS_HASR)
				{
					state.axes << detail::CalculateAxeValue(info.dwRpos, caps.wRmin, caps.wRmax);
				}

				if (caps.wCaps & JOYCAPS_HASU)
				{
					state.axes << detail::CalculateAxeValue(info.dwUpos, caps.wUmin, caps.wUmax);
				}

				if (caps.wCaps & JOYCAPS_HASV)
				{
					state.axes << detail::CalculateAxeValue(info.dwVpos, caps.wVmin, caps.wVmax);
				}

				state.buttons.resize(caps.wNumButtons);

				for (size_t i = 0; i < state.buttons.size(); ++i)
				{
					const bool currentPressed = !!(info.dwButtons & (0x1u << i));
					state.buttons[i].update(currentPressed);
				}

				if ((caps.wCaps & JOYCAPS_HASPOV)
					|| (caps.wCaps & JOYCAPS_POV4DIR)
					|| (caps.wCaps & JOYCAPS_POVCTS))
				{
					const uint32 value = info.dwPOV;

					if (value == JOY_POVCENTERED)
					{
						state.povDegree = none;

						for (auto& pov : state.povs)
						{
							pov.update(false);
						}
					}
					else
					{
						state.povDegree = value / 100;

						const int32 d = detail::Get8Direction(value);
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
