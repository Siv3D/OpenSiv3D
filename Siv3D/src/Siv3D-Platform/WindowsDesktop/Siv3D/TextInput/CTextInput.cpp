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
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Print/IPrint.hpp>
# include "CTextInput.hpp"

namespace s3d
{
	CTextInput::CTextInput()
		: m_pVideo{ std::make_unique<SDL_VideoData>() } {}

	CTextInput::~CTextInput()
	{
		LOG_SCOPED_TRACE(U"CTextInput::~CTextInput()");

		IME_Quit(m_pVideo.get());

		::ImmReleaseContext(m_hWnd, m_hImc);
	}

	void CTextInput::init()
	{
		LOG_SCOPED_TRACE(U"CTextInput::init()");

		//::CoInitialize(nullptr);

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		LOG_VERBOSE(U":ImmGetContext()");
		m_hImc = ::ImmGetContext(m_hWnd);

		m_pVideo->pTextInput = this;

		LOG_VERBOSE(U":WIN_InitKeyboard()");
		WIN_InitKeyboard(m_pVideo.get());

		LOG_VERBOSE(U":IME_Init()");
		IME_Init(m_pVideo.get(), m_hWnd);

		LOG_VERBOSE(U":IME_Enable()");
		IME_Enable(m_pVideo.get(), m_hWnd);
	}

	void CTextInput::update()
	{
		SIV3D_ENGINE(Print)->showUnhandledEditingText(m_editingTextHandled ? String{} : m_editingText);

		{
			std::lock_guard lock{ m_mutex };

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

	void CTextInput::pushChar(const uint32 ch)
	{
		std::lock_guard lock{ m_mutex };

		m_internalChars.push_back(static_cast<char32>(ch));
	}

	const String& CTextInput::getChars() const
	{
		return m_chars;
	}

	const String& CTextInput::getEditingText() const
	{
		m_editingTextHandled = true;

		return m_editingText;
	}

	void CTextInput::enableIME(const bool enabled)
	{
		if (m_enabled == enabled)
		{
			return;
		}

		if (not enabled)
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

	std::pair<int32, int32> CTextInput::getCursorIndex() const
	{
		return{ m_cursorPos, m_targetLength };
	}

	const Array<String>& CTextInput::getCandidates() const
	{
		return m_candidates;
	}

	bool CTextInput::process(UINT msg, WPARAM wParam, LPARAM* lParam)
	{
		return IME_HandleMessage(m_hWnd, msg, wParam, lParam, m_pVideo.get());
	}

	void CTextInput::sendEditingText(const String& text, const int32 cursorPos, const int32 targetLength)
	{
		std::lock_guard lock{ m_mutex };

		m_internalEditingText = text;

		m_internalCursorPos = cursorPos;

		m_internalTargetLength = targetLength;
	}

	void CTextInput::sendCandidates(const Array<String>& candidates)
	{
		std::lock_guard lock{ m_mutex };

		m_internalCandidates = candidates;
	}

	void CTextInput::sendInputText(const String& text)
	{
		std::lock_guard lock{ m_mutex };

		m_internalChars.append(text);
	}
}
