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

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineOptions.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include "CConsole.hpp"

namespace s3d
{
	CConsole::CConsole()
		: m_defaultCodePage(::GetConsoleOutputCP())
	{
		// do nothing
	}

	CConsole::~CConsole()
	{
		LOG_SCOPED_TRACE(U"CConsole::~CConsole()");

		close();
	}

	void CConsole::open()
	{
		if (m_isOpen)
		{
			return;
		}

		LOG_SCOPED_TRACE(U"CConsole::open()");

		::AllocConsole();
		::freopen_s(&m_fpOut, "CONOUT$", "w", stdout);
		::freopen_s(&m_fpIn,  "CONIN$",  "r", stdin);
		::freopen_s(&m_fpErr, "CONOUT$", "w", stderr);

		std::ios_base::sync_with_stdio(false);

		m_isOpen = true;
	}

	void CConsole::close()
	{
		if (not m_isOpen)
		{
			return;
		}

		if (m_fpErr)
		{
			::fclose(m_fpErr);
			m_fpErr = nullptr;
		}

		if (m_fpIn)
		{
			::fclose(m_fpIn);
			m_fpIn = nullptr;
		}

		if (m_fpOut)
		{
			::fclose(m_fpOut);
			m_fpOut = nullptr;
		}

		::FreeConsole();
	}

	void CConsole::setSystemDefaultCodePage()
	{
		::SetConsoleOutputCP(m_defaultCodePage);
	}

	void CConsole::setUTF8CodePage()
	{
		::SetConsoleOutputCP(CP_UTF8);
	}
}
