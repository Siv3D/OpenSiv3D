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

# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CKeyboard.hpp"

namespace s3d
{
	CKeyboard::CKeyboard()
	{

	}

	CKeyboard::~CKeyboard()
	{
		LOG_TRACE(U"CKeyboard::CKeyboard()");
	}

	void CKeyboard::init()
	{
		LOG_TRACE(U"CKeyboard::init()");

		m_hWnd = static_cast<HWND>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());

		LOG_INFO(U"ℹ️ CKeyboard initialized");
	}

	void CKeyboard::update()
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

	bool CKeyboard::down(const uint32 index) const
	{
		return m_states[index].down;
	}

	bool CKeyboard::pressed(const uint32 index) const
	{
		return m_states[index].pressed;
	}

	bool CKeyboard::up(const uint32 index) const
	{
		return m_states[index].up;
	}

	Duration CKeyboard::pressedDuration(const uint32 index) const
	{
		return m_states[index]._pressedDuration;
	}
}
