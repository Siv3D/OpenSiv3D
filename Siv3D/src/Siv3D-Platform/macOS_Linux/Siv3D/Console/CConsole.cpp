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

# include <ios>
# include "CConsole.hpp"

namespace s3d
{
	CConsole::CConsole()
	{
		std::ios_base::sync_with_stdio(false);
	}

	CConsole::~CConsole()
	{
		// do nothing
	}

	void CConsole::open()
	{
		// do nothing
	}

	void CConsole::close()
	{
		// do nothing
	}

	void CConsole::setSystemDefaultCodePage()
	{
		// do nothing
	}

	void CConsole::setUTF8CodePage()
	{
		// do nothing
	}
}
