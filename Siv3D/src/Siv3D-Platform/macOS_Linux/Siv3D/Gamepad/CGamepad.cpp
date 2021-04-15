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

	}

	void CGamepad::init()
	{
		LOG_SCOPED_TRACE(U"CGamepad::init()");
	}

	void CGamepad::update()
	{

	}

	Array<GamepadInfo> CGamepad::enumerate()
	{
		return{};
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
			return m_states[playerIndex].buttons[index].down;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].down;
		}

		return false;
	}

	bool CGamepad::pressed(const size_t playerIndex, const uint32 index)
	{
		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			return m_states[playerIndex].buttons[index].pressed;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].pressed;
		}

		return false;
	}

	bool CGamepad::up(const size_t playerIndex, const uint32 index)
	{
		assert(playerIndex < Gamepad.MaxPlayerCount);

		if (index < m_states[playerIndex].buttons.size())
		{
			return m_states[playerIndex].buttons[index].up;
		}
		else if (InRange(index, 0x80u, 0x83u))
		{
			return m_states[playerIndex].povs[(index - 0x80u)].up;
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
