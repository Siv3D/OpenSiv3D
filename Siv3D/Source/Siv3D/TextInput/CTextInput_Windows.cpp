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

# include "CTextInput_Windows.hpp"

namespace s3d
{
	CTextInput_Windows::CTextInput_Windows()
	{

	}

	CTextInput_Windows::~CTextInput_Windows()
	{

	}

	bool CTextInput_Windows::init()
	{

		return true;
	}

	void CTextInput_Windows::update()
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		m_chars = m_internalChars.toUTF32();

		m_internalChars.clear();
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
}

# endif
