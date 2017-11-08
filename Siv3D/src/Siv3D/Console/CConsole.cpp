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

# include "CConsole.hpp"
# include <Siv3D/Windows.hpp>

namespace s3d
{
	CConsole::CConsole()
	{

	}

	CConsole::~CConsole()
	{
		close();
	}

	void CConsole::open()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		if (!m_out)
		{
			::AllocConsole();

			::freopen_s(&m_out, "CONOUT$", "w", stdout);

			::freopen_s(&m_in, "CONIN$", "r", stdin);
		}

	# endif
	}

	void CConsole::close()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		if (m_out)
		{
			::fclose(m_out);

			m_out = nullptr;
		}

		if (m_in)
		{
			::fclose(m_in);

			m_in = nullptr;
		}

		::FreeConsole();

	# endif
	}
}
