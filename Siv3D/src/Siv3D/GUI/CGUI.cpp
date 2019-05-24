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

# include <Siv3D/EngineLog.hpp>
# include "CGUI.hpp"

namespace s3d
{
	CGUI::CGUI()
	{

	}

	CGUI::~CGUI()
	{
		LOG_TRACE(U"CGUI::~CGUI()");
	}

	void CGUI::init()
	{
		LOG_TRACE(U"CGUI::init()");

		m_defaultGUIFont = std::make_unique<Font>(20, Typeface::Medium);

		LOG_INFO(U"ℹ️ CGUI initialized");
	}

	const Font& CGUI::getDefaultGUIFont()
	{
		return *m_defaultGUIFont;
	}
}
