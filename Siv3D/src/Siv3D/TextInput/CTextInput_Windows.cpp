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

# include <Siv3D/Windows.hpp>
# include <imm.h>
# include "../Siv3DEngine.hpp"
# include "CTextInput_Windows.hpp"
# include "../Print/IPrint.hpp"
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CTextInput_Windows::CTextInput_Windows()
		: m_pVideo(std::make_unique<SDL_VideoData>())
	{

	}

	CTextInput_Windows::~CTextInput_Windows()
	{
		IME_Quit(m_pVideo.get());

		::ImmReleaseContext(m_hWnd, m_hImc);
	}

	bool CTextInput_Windows::init()
	{
		m_hWnd = Siv3DEngine::GetWindow()->getHandle();

		m_hImc = ::ImmGetContext(m_hWnd);

		m_pVideo->pTextInput = this;

		WIN_InitKeyboard(m_pVideo.get());

		IME_Init(m_pVideo.get(), m_hWnd);

		IME_Enable(m_pVideo.get(), m_hWnd);

		return true;
	}

	void CTextInput_Windows::update()
	{
		Siv3DEngine::GetPrint()->showUnhandledEditingText(m_editingTextHandled ? U"" : m_editingText);

		{
			std::lock_guard<std::mutex> lock(m_mutex);

			m_editingText = m_internalEditingText;

			m_cursorPos = m_internalCursorPos;

			m_targetLength = m_internalTargetLength;

			m_candidates = m_internalCandidates;

			m_chars = m_internalChars;

			m_internalChars.clear();
		}

		if (m_editingText)
		{
			m_editingTextHandled = false;
		}

		if (!m_editingText)
		{
			if (KeyDelete.down() || (KeyDelete.pressedDuration() > SecondsF(0.33) && m_deletePress > SecondsF(0.06)))
			{
				m_chars.push_back(char32(0x7F));
				m_deletePress.restart();
			}
		}
	}

	void CTextInput_Windows::pushChar(const uint32 ch)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_internalChars.push_back(static_cast<char32>(ch));
	}

	const String& CTextInput_Windows::getChars() const
	{
		return m_chars;
	}
	
	const String& CTextInput_Windows::getEditingText() const
	{
		m_editingTextHandled = true;

		return m_editingText;
	}

	void CTextInput_Windows::enableIME(bool enabled)
	{
		if (m_enabled == enabled)
		{
			return;
		}

		if (!enabled)
		{
			WIN_StopTextInput(m_pVideo.get(), m_hWnd);
		}
		else
		{
			// [Siv3D ToDo] does not work
			WIN_StartTextInput(m_pVideo.get(), m_hWnd);
		}

		m_enabled = enabled;
	}

	std::pair<int32, int32> CTextInput_Windows::getCursorIndex() const
	{
		return{ m_cursorPos, m_targetLength };
	}

	const Array<String>& CTextInput_Windows::getCandidates() const
	{
		return m_candidates;
	}

	bool CTextInput_Windows::process(UINT msg, WPARAM wParam, LPARAM *lParam)
	{
		return IME_HandleMessage(m_hWnd, msg, wParam, lParam, m_pVideo.get());
	}

	void CTextInput_Windows::sendEditingText(const String& text, const int32 cursorPos, const int32 targetLength)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_internalEditingText = text;

		m_internalCursorPos = cursorPos;

		m_internalTargetLength = targetLength;
	}

	void CTextInput_Windows::sendCandidates(const Array<String>& candidates)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_internalCandidates = candidates;
	}

	void CTextInput_Windows::sendInputText(const String& text)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_internalChars.append(text);
	}
}

# endif
