//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include "CKeyboard_Windows.hpp"

namespace s3d
{
	CKeyboard_Windows::CKeyboard_Windows()
	{

	}

	CKeyboard_Windows::~CKeyboard_Windows()
	{

	}

	bool CKeyboard_Windows::init()
	{
		m_hWnd = Siv3DEngine::GetWindow()->getHandle();

		return true;
	}

	void CKeyboard_Windows::update()
	{
		if (!m_inputAttached)
		{
			::AttachThreadInput(::GetWindowThreadProcessId(m_hWnd, nullptr), ::GetCurrentThreadId(), TRUE);

			m_inputAttached = true;
		}

		uint8 buf[256] = {};

		if (::GetKeyboardState(buf))
		{
			for (size_t i = 0; i < m_states.size(); ++i)
			{
				const bool pressed = (buf[i] >> 7) & 0x1;

				m_states[i].update(pressed);
			}
		}
	}

	bool CKeyboard_Windows::down(const uint32 index) const
	{
		return m_states[index].down;
	}

	bool CKeyboard_Windows::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}

	bool CKeyboard_Windows::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	MillisecondsF CKeyboard_Windows::pressedDuration(const uint32 index) const
	{
		return m_states[index].pressedDuration;
	}
}

# endif
