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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "../Siv3DEngine.hpp"
# include "CTextInput_macOS.hpp"
# include <Siv3D/Keyboard.hpp>

# include <Siv3D/Logger.hpp>
# include <Siv3D/System.hpp>

# if defined(SIV3D_TARGET_MACOS)

extern "C"
{
	using namespace s3d;
	
	CTextInput_macOS* pTextInput = nullptr;
		
	void s3d_OnHaveMarkedText(const char* text)
	{
		pTextInput->onHaveMarkedText(text);
	}
}

# endif

namespace s3d
{
	CTextInput_macOS::CTextInput_macOS()
	{
	# if defined(SIV3D_TARGET_MACOS)
		
		pTextInput = this;
		
	# endif
	}

	CTextInput_macOS::~CTextInput_macOS()
	{
	# if defined(SIV3D_TARGET_MACOS)
		
		pTextInput = nullptr;

	# endif
	}

	bool CTextInput_macOS::init()
	{
		const WindowHandle glfwWindow = Siv3DEngine::GetWindow()->getHandle();
		
		::glfwSetCharCallback(glfwWindow, OnCharacterInput);

		return true;
	}

	void CTextInput_macOS::update()
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

	void CTextInput_macOS::pushChar(const uint32 ch)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		
		m_internalChars.push_back(static_cast<char16_t>(ch));
	}

	const String& CTextInput_macOS::getChars() const
	{
		return m_chars;
	}
	
	const String& CTextInput_macOS::getMarkedText() const
	{
		return m_markedText;
	}
	
	void CTextInput_macOS::OnCharacterInput(WindowHandle, const uint32 codePoint)
	{
		Siv3DEngine::GetTextInput()->pushChar(codePoint);
	}
	
	void CTextInput_macOS::onHaveMarkedText(const char* text)
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

# endif
