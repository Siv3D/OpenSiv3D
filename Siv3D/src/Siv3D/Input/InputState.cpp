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

# include "InputState.hpp"

namespace s3d
{
	void InputState::update(const bool currentPressed)
	{
		const bool previousPressed = m_pressed;
		m_pressed	= currentPressed;
		m_down		= (!previousPressed && m_pressed);
		m_up		= (previousPressed && !m_pressed);
		m_cleared	= false;

		if (m_down)
		{
			stopwatch.restart();
		}
		else if (m_up)
		{
			pressedDuration = stopwatch.elapsed();
			stopwatch.reset();
		}
		else if (m_pressed)
		{
			pressedDuration = stopwatch.elapsed();
		}
		else
		{
			pressedDuration = Duration{ 0 };
		}
	}

	void InputState::reset()
	{
		pressedDuration = Duration{ 0 };
		stopwatch.reset();
		m_up		= false;
		m_pressed	= false;
		m_down		= false;
		m_cleared	= false;
	}

	void InputState::clearInput()
	{
		m_cleared = true;
	}

	bool InputState::cleared() const noexcept
	{
		return m_cleared;
	}

	bool InputState::up() const noexcept
	{
		return m_up;
	}

	bool InputState::pressed() const noexcept
	{
		return ((not m_cleared) && m_pressed);
	}

	bool InputState::down() const noexcept
	{
		return ((not m_cleared) && m_down);
	}
}
