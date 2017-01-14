//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Logger.hpp>
# include "CLogger.hpp"
# include "LogHeaderFotter.hpp"

# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>

namespace s3d
{
	namespace detail
	{
		const static String logLevelStr[] =
		{
			L"[error]",
			L"[fail]",
			L"[warning]",
			L"[script]",
			L"",
			L"[info]",
			L"[debug]",
		};

		static void OutputDebug(const LogDescription desc, const String& str)
		{
			String output;
			output.reserve(logLevelStr[static_cast<size_t>(desc)].length() + str.length() + 1);
			output.append(logLevelStr[static_cast<size_t>(desc)]);
			output.append(str);
			output.push_back(L'\n');

			::OutputDebugStringW(output.c_str());
		}
	}
}

# elif defined(SIV3D_TARGET_MACOS)

# include <iostream>
# include <Siv3D/CharacterSet.hpp>

namespace s3d
{
	namespace detail
	{
		const static std::string logLevelStr[] =
		{
			"[error]",
			"[fail]",
			"[warning]",
			"[script]",
			"",
			"[info]",
			"[debug]",
		};

		static void OutputDebug(const LogDescription desc, const String& str)
		{
			if (desc != LogDescription::App)
			{
				std::cout << logLevelStr[static_cast<size_t>(desc)];
			}

			std::cout << CharacterSet::ToUTF8(str) << '\n';
		}
	}
}

# endif

namespace s3d
{
	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
		m_initialized = false;

		m_writer.writeUTF8(footer);

		m_writer.close();
	}

	bool CLogger::init()
	{
		const String fileName = FileSystem::BaseName(FileSystem::ModulePath()).xml_escaped();
		const std::string filenameUTF8 = CharacterSet::ToUTF8(fileName);

		m_writer.open(fileName + L"_log.html", CharacterEncoding::UTF8_BOM);
		m_writer.writeUTF8(headerA);
		m_writer.writeUTF8(filenameUTF8);
		m_writer.writeUTF8(headerB);
		m_writer.writeUTF8(filenameUTF8);
		m_writer.writeUTF8(headerC);

		//write(LogDescription::App, L"App Message");
		//write(LogDescription::Debug, L"Debug Message");
		//write(LogDescription::Error , L"Error Message");
		//write(LogDescription::Fail, L"Fail Message");
		//write(LogDescription::Info, L"Info Message");
		//write(LogDescription::Script, L"Script Message");
		//write(LogDescription::Warning, L"Warning Message");

		m_initialized = true;

		return true;
	}

	void CLogger::write(const LogDescription desc, const String& str)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		detail::OutputDebug(desc, str);

		m_writer.writeUTF8(logLevel[static_cast<size_t>(desc)]);

		m_writer.write(str.xml_escaped());

		m_writer.writeUTF8(divEnd);
	}
}
