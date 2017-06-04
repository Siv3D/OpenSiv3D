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

# include "CTextInput_macOS.hpp"

namespace s3d
{
	CTextInput_macOS::CTextInput_macOS()
	{

	}

	CTextInput_macOS::~CTextInput_macOS()
	{

	}

	bool CTextInput_macOS::init()
	{

		return true;
	}

	void CTextInput_macOS::update()
	{

	}

	void CTextInput_macOS::pushChar(const char32_t ch)
	{

	}

	const std::u32string& CTextInput_macOS::getChars() const
	{
		return m_chars;
	}
}

# endif
