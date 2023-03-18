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
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CTextInput.hpp"

extern "C"
{
	using namespace s3d;
	
	CTextInput* pTextInput = nullptr;
	
	XIMCallback preeditStart;
	XIMCallback preeditDraw;
	XIMCallback preeditDone;
	XIMCallback preeditCaret;

	static void preeditStartCallback(XIC, XPointer, XPointer)
	{
		// do nothing
	}

	static void preeditDoneCallback(XIC, XPointer, XPointer)
	{
		// do nothing
	}

	static void preeditDrawCallback(XIC ic, XPointer client_data, XIMPreeditDrawCallbackStruct *call_data)
	{
		pTextInput->preeditDrawCallback(ic, client_data, call_data);
	}

	static void preeditCaretCallback(XIC, XPointer, XIMPreeditCaretCallbackStruct *)
	{
		// do nothing
	}

	XVaNestedList s3d_PreeditAttributes(XPointer client_data)
	{
		preeditStart.client_data = client_data;
		preeditStart.callback = (XIMProc)preeditStartCallback;
		preeditDone.client_data = client_data;
		preeditDone.callback = (XIMProc)preeditDoneCallback;
		preeditDraw.client_data = client_data;
		preeditDraw.callback = (XIMProc)preeditDrawCallback;
		preeditCaret.client_data = client_data;
		preeditCaret.callback = (XIMProc)preeditCaretCallback;

		return XVaCreateNestedList(0,
								   XNPreeditStartCallback, &preeditStart.client_data,
								   XNPreeditDoneCallback, &preeditDone.client_data,
								   XNPreeditDrawCallback, &preeditDraw.client_data,
								   XNPreeditCaretCallback, &preeditCaret.client_data,
								   NULL);
	}

	void s3d_InputText(char *text)
	{
		pTextInput->sendInputText(Unicode::FromUTF8(text));
	}

	void s3d_SetICFocus(XIC)
	{
		pTextInput->updateWindowFocus(true);
	}

	void s3d_UnsetICFocus(XIC)
	{
		pTextInput->updateWindowFocus(false);
	}

	XIC s3d_GetXICFromGLFWWindow(GLFWwindow *window);
}

namespace s3d
{
	CTextInput::CTextInput()
	{
		pTextInput = this;
	}
	
	CTextInput::~CTextInput()
	{
		LOG_SCOPED_TRACE(U"CTextInput::~CTextInput()");
		
		pTextInput = nullptr;
	}
	
	void CTextInput::init()
	{
		LOG_SCOPED_TRACE(U"CTextInput::init()");

		if (GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle()))
		{
			::glfwSetCharCallback(glfwWindow, OnCharacterInput);
		}
	}
	
	void CTextInput::update()
	{
		{
			std::lock_guard lock{ m_mutexChars };
			
			m_chars = m_internalChars;
			
			m_internalChars.clear();
		}
		
		{
			std::lock_guard lock{ m_mutexPreeditStatus };
			
			m_preeditText = m_internalPreeditText;

			m_preeditTextStyle = m_internalPreeditTextStyle;

			m_preeditCaret = m_internalPreeditCaret;
		}
	}
	
	void CTextInput::pushChar(const uint32 ch)
	{
		std::lock_guard lock{ m_mutexChars };
		
		m_internalChars.push_back(static_cast<char32>(ch));
	}
	
	const String& CTextInput::getChars() const
	{
		return m_chars;
	}
	
	const String& CTextInput::getEditingText() const
	{
		return m_preeditText;
	}
	
	void CTextInput::enableIME(const bool enabled)
	{
		m_imeEnabled = enabled;
		updateICFocus();
	}
	
	std::pair<int32, int32> CTextInput::getCursorIndex() const
	{
		return{ m_preeditCaret, 0 };
	}
	
	const Array<String>& CTextInput::getCandidates() const
	{
		static const Array<String> dummy;
		return dummy;
	}

	const Array<UnderlineStyle>& CTextInput::getEditingTextStyle() const
	{
		return m_preeditTextStyle;
	}

	void CTextInput::preeditDrawCallback(XIC, XPointer, XIMPreeditDrawCallbackStruct* call_data)
	{
		std::lock_guard lock{ m_mutexPreeditStatus };
		
		m_internalPreeditCaret = call_data->caret;
		
		if (call_data->text)
		{
			String text;
			if (call_data->text->encoding_is_wchar)
			{
				text = Unicode::FromWstring(call_data->text->string.wide_char);
			}
			else
			{
				text = Unicode::FromUTF8(call_data->text->string.multi_byte);
			}

			m_internalPreeditText.erase(call_data->chg_first, call_data->chg_length);
			m_internalPreeditText.insert(call_data->chg_first, text);

			m_internalPreeditTextStyle.erase(std::next(m_internalPreeditTextStyle.begin(), call_data->chg_first), std::next(m_internalPreeditTextStyle.begin(), call_data->chg_first + call_data->chg_length));
			m_internalPreeditTextStyle.insert(std::next(m_internalPreeditTextStyle.begin(), call_data->chg_first), text.length(), UnderlineStyle::NoStyle);

			auto itr = std::next(m_internalPreeditTextStyle.begin(), call_data->chg_first);
			UnderlineStyle style = UnderlineStyle::NoStyle;
			for(size_t idx = 0; idx < text.length(); idx++)
			{
				auto feedback = call_data->text->feedback[idx];
				if(feedback == 0)
				{
					*itr = style;
				}
				else
				{
					if (feedback & XIMReverse)
					{
						*itr |= UnderlineStyle::Highlight;
					}
					if (feedback & XIMHighlight)
					{
						*itr |= UnderlineStyle::DashedUnderline;
					}
					if (feedback & XIMUnderline)
					{
						*itr = (*itr & ~UnderlineStyle::UnderlineMask) | UnderlineStyle::Underline;
					}
				}
				itr++;
			}
		}
		else
		{
			m_internalPreeditTextStyle.erase(std::next(m_internalPreeditTextStyle.begin(), call_data->chg_first), std::next(m_internalPreeditTextStyle.begin(), call_data->chg_first + call_data->chg_length));
			m_internalPreeditText.erase(call_data->chg_first, call_data->chg_length);
		}


	}

	void CTextInput::updateWindowFocus(bool focus)
	{
		m_windowHasFocus = focus;
		updateICFocus();
	}

	void CTextInput::sendInputText(const String& text)
	{
		std::lock_guard lock { m_mutexChars };

		m_internalChars.append(text);
	}

	void CTextInput::updateICFocus()
	{
		XIC ic = s3d_GetXICFromGLFWWindow(static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle()));
		if (ic)
		{
			if (m_imeEnabled && m_windowHasFocus)
			{
				XSetICFocus(ic);
			}
			else
			{
				XUnsetICFocus(ic);
			}
		}
	}

	void CTextInput::OnCharacterInput(GLFWwindow*, const uint32 codePoint)
	{
		SIV3D_ENGINE(TextInput)->pushChar(codePoint);
	}
}
