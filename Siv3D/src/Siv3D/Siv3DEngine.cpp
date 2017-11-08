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

# include "Siv3DEngine.hpp"
# include "LicenseManager/ILicenseManager.hpp"
# include "Logger/ILogger.hpp"
# include "Console/IConsole.hpp"

namespace s3d
{
	Siv3DEngine::Siv3DEngine()
	{
		pEngine = this;
	}

	Siv3DEngine::~Siv3DEngine()
	{
		m_console.release();
		m_logger.release();
		m_licenseManager.release();

		pEngine = nullptr;
	}
}
