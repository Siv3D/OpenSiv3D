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

# include <Siv3D/Windows.hpp>
# include "CConsole.hpp"

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
		if (m_initialized)
		{
			return;
		}

		::AllocConsole();

		::freopen_s(&m_out, "CONOUT$", "w", stdout);

		::freopen_s(&m_in, "CONIN$", "r", stdin);

		m_initialized = true;
	}

	void CConsole::close()
	{
		if (!m_initialized)
		{
			return;
		}

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
	}
}
