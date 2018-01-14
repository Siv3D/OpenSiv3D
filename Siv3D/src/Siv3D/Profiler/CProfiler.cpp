//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CProfiler.hpp"
# include <Siv3D/Logger.hpp>
# include <Siv3D/MessageBox.hpp>

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

		LOG_INFO(U"ℹ️ Profiler initialized");

		return true;
	}

	bool CProfiler::beginFrame()
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

		if (m_assetCreationWarningEnabled
			&& std::all_of(m_assetCreationCount.begin(), m_assetCreationCount.end(), [](int32 n) { return n > 0; })
			&& std::all_of(m_assetReleaseCount.begin(), m_assetReleaseCount.end(), [](int32 n) { return n > 0; }))
		{
			LOG_ERROR(U"🔥 Assets have been created and released every frame. Set Profiler::EnableAssetCreationWarning(false) to suppress this assertion.");

			System::ShowMessageBox(U"Asset creation report", U"🔥 Assets have been created and released every frame. Set Profiler::EnableAssetCreationWarning(false) to suppress this assertion.", MessageBoxStyle::Error);

			return false;
		}

		std::rotate(m_assetCreationCount.rbegin(), m_assetCreationCount.rbegin() + 1, m_assetCreationCount.rend());

		std::rotate(m_assetReleaseCount.rbegin(), m_assetReleaseCount.rbegin() + 1, m_assetReleaseCount.rend());

		m_assetCreationCount[0] = m_assetReleaseCount[0] = 0;

		return true;
	}

	void CProfiler::endFrame()
	{

	}

	int32 CProfiler::getFPS() const
	{
		return m_currentFPS;
	}


	void CProfiler::setAssetCreationWarningEnabled(const bool enabled)
	{
		m_assetCreationWarningEnabled = enabled;
	}

	void CProfiler::reportAssetCreation()
	{
		++m_assetCreationCount[0];
	}

	void CProfiler::reportAssetRelease()
	{
		++m_assetReleaseCount[0];
	}
}
