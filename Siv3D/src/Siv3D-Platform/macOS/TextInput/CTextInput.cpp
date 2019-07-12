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

# include <Siv3D/EngineLog.hpp>
# include <Siv3DEngine.hpp>
# include "CTextInput.hpp"
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/System.hpp>

extern "C"
{
	using namespace s3d;
	
	CTextInput* pTextInput = nullptr;
	
	void s3d_OnHaveMarkedText(const char* text)
	{
		pTextInput->onHaveMarkedText(text);
	}
}

namespace s3d
{
	CTextInput::CTextInput()
	{
		pTextInput = this;
	}
	
	CTextInput::~CTextInput()
	{
		LOG_TRACE(U"CTextInput::~CTextInput()");
		
		pTextInput = nullptr;
	}
	
	void CTextInput::init()
	{		
		LOG_TRACE(U"CTextInput::init()");

		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(Siv3DEngine::Get<ISiv3DWindow>()->getHandle());
		
		::glfwSetCharCallback(glfwWindow, OnCharacterInput);
		
		LOG_INFO(U"ℹ️ CTextInput initialized");
	}
	
	void CTextInput::update()
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			
			m_chars = Unicode::FromUTF16(m_internalChars);
			
			m_internalChars.clear();
		}
		
		const bool hadMarkedText = !m_markedText.isEmpty();
		bool haveMarkedText;
		{
			std::lock_guard<std::mutex> lock(m_mutexMarkedText);
			
			m_markedText = m_internalMarkedText;
			
			haveMarkedText = m_haveMarkedText;
		}
		
		if (!m_markedText)
		{
			m_markedText.clear();
		}
		
		if(!haveMarkedText && !hadMarkedText)
		{
			if (m_chars.empty() && (KeyEnter.down() || (KeyEnter.pressedDuration() > SecondsF(0.33) && m_enterPress > SecondsF(0.06))))
			{
				m_chars.push_back(U'\r');
				m_enterPress.restart();
			}
			
			if (KeyTab.down() || (KeyTab.pressedDuration() > SecondsF(0.33) && m_tabPress > SecondsF(0.06)))
			{
				m_chars.push_back(U'\t');
				m_tabPress.restart();
			}
			
			if (KeyBackspace.down() || (KeyBackspace.pressedDuration() > SecondsF(0.33) && m_backSpacePress > SecondsF(0.06)))
			{
				m_chars.push_back(U'\b');
				m_backSpacePress.restart();
			}
		}
	}
	
	void CTextInput::pushChar(const uint32 ch)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		
		m_internalChars.push_back(static_cast<char16_t>(ch));
	}
	
	const String& CTextInput::getChars() const
	{
		return m_chars;
	}
	
	const String& CTextInput::getEditingText() const
	{
		return m_markedText;
	}
	
	void CTextInput::enableIME(bool)
	{
		
	}
	
	std::pair<int32, int32> CTextInput::getCursorIndex() const
	{
		// [Siv3D ToDo]
		return{ 0, 0};
	}
	
	const Array<String>& CTextInput::getCandidates() const
	{
		static const Array<String> dummy;
		return dummy;
	}
	
	void CTextInput::OnCharacterInput(GLFWwindow*, const uint32 codePoint)
	{
		Siv3DEngine::Get<ISiv3DTextInput>()->pushChar(codePoint);
	}
	
	void CTextInput::onHaveMarkedText(const char* text)
	{
		std::lock_guard<std::mutex> lock(m_mutexMarkedText);
		
		m_haveMarkedText = (text != nullptr);
		
		if (m_haveMarkedText)
		{
			m_internalMarkedText = Unicode::FromUTF8(text);
		}
		else
		{
			m_internalMarkedText.clear();
		}
	}
}
