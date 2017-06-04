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

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <imm.h>
# include "../Siv3DEngine.hpp"
# include "CTextInput_Windows.hpp"

# include <Siv3D/Logger.hpp>

namespace s3d
{
	CTextInput_Windows::CTextInput_Windows()
	{

	}

	CTextInput_Windows::~CTextInput_Windows()
	{
		::ImmReleaseContext(m_hWnd, m_hImc);
	}

	bool CTextInput_Windows::init()
	{
		m_hWnd = Siv3DEngine::GetWindow()->getHandle();

		m_hImc = ::ImmGetContext(m_hWnd);

		return true;
	}

	void CTextInput_Windows::update()
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			m_chars = m_internalChars.toUTF32();

			m_internalChars.clear();
		}

		wchar_t result[512] = {};
		
		if (const int32 size = ::ImmGetCompositionStringW(m_hImc, GCS_COMPSTR, result, 512))
		{
			m_markedText = result;
		}
		else
		{
			m_markedText.clear();
		}	
	}

	void CTextInput_Windows::pushChar(const char32_t ch)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_internalChars.push_back(static_cast<wchar>(ch));
	}

	const std::u32string& CTextInput_Windows::getChars() const
	{
		return m_chars;
	}
	
	const String& CTextInput_Windows::getMarkedText() const
	{
		return m_markedText;
	}
}

# endif
