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

# include "Siv3DEngine.hpp"
# include "Logger/ILogger.hpp"
# include "Console/IConsole.hpp"

namespace s3d
{
	Siv3DEngine* Siv3DEngine::pEngine = nullptr;

	Siv3DEngine::Siv3DEngine()
	{
		pEngine = this;
	}

	Siv3DEngine::~Siv3DEngine()
	{
		m_console.release();
		m_logger.release();

		pEngine = nullptr;
	}
}
