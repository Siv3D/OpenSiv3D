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

# include "CProfiler.hpp"

namespace s3d
{
	CProfiler::CProfiler()
	{

	}

	CProfiler::~CProfiler()
	{

	}

	bool CProfiler::init()
	{
		m_fpsStopwatch.start();

		return true;
	}

	void CProfiler::beginFrame()
	{
		if (m_fpsStopwatch.msF() < 1000.0)
		{
			++m_fpsCount;
		}
		else
		{
			m_currentFPS = m_fpsCount;

			m_fpsCount = 1;

			m_fpsStopwatch.restart();
		}
	}

	void CProfiler::endFrame()
	{

	}

	int32 CProfiler::getFPS() const
	{
		return m_currentFPS;
	}
}