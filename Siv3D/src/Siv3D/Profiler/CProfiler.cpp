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
# include <Siv3D/Window.hpp>
# include <Siv3D/MessageBox.hpp>
# include <Siv3D/Scene.hpp>
# include "CProfiler.hpp"

namespace s3d
{
	CProfiler::CProfiler()
	{

	}

	CProfiler::~CProfiler()
	{
		LOG_TRACE(U"CProfiler::~CProfiler()");
	}

	void CProfiler::init()
	{
		LOG_TRACE(U"CProfiler::init()");

		m_fpsStopwatch.start();

		LOG_INFO(U"ℹ️ CProfiler initialized");
	}

	bool CProfiler::beginFrame()
	{
		//
		// FPS
		//
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

		//
		// Stats
		//
		m_previousStatistics = m_currentStatistics;
		m_currentStatistics = Statistics();

		//
		// Asset creation
		//
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

	String CProfiler::getSimpleStatistics() const
	{
		const Size backBufferSize = Window::ClientSize();
		const Size sceneSize = Scene::Size();
		return U"{} FPS | W {}x{} | S {}x{}"_fmt(
			m_currentFPS,
			backBufferSize.x, backBufferSize.y,
			sceneSize.x, sceneSize.y);
	}

	void CProfiler::setAssetCreationWarningEnabled(const bool enabled)
	{
		m_assetCreationWarningEnabled = enabled;
	}

	void CProfiler::reportDrawcalls(const size_t drawcalls, const size_t triangles)
	{
		m_currentStatistics.drawcalls += drawcalls;

		m_currentStatistics.triangles += triangles;
	}

	Statistics CProfiler::getStatistics() const noexcept
	{
		return m_previousStatistics;
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
