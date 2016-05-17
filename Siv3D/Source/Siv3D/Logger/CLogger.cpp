//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Logger.hpp>
# include "CLogger.hpp"
# include "LogHeaderFotter.hpp"

namespace s3d
{
	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
		m_initialized = false;

		m_writer.write(footer);

		m_writer.close();
	}

	bool CLogger::init()
	{
		const String fileName = FileSystem::BaseName(FileSystem::ModulePath()).xml_escaped();
	
		m_writer.open(fileName + L"_log.html", TextEncoding::UTF8);
		m_writer.write(headerA);
		m_writer.write(fileName);
		m_writer.write(headerB);
		m_writer.write(fileName);
		m_writer.write(headerC);

		write(LogDescription::App, L"App Message");
		write(LogDescription::Debug, L"Debug Message");
		write(LogDescription::Error , L"Error Message");
		write(LogDescription::Fail, L"Fail Message");
		write(LogDescription::Info, L"Info Message");
		write(LogDescription::Script, L"Script Message");
		write(LogDescription::Warning, L"Warning Message");

		return true;
	}

	void CLogger::write(const LogDescription desc, const String& str)
	{
		m_writer.write(logLevel[static_cast<size_t>(desc)]);

		m_writer.write(str.xml_escaped());

		m_writer.write(pEnd);
	}
}
