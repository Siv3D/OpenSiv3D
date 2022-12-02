//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/MessageBox.hpp>
# include "CAssetMonitor.hpp"

namespace s3d
{
	bool CAssetMonitor::update()
	{
		if (m_assetCreationWarningEnabled
			&& std::all_of(m_assetCreationCount.begin(), m_assetCreationCount.end(), [](int32 n) { return n > 0; })
			&& std::all_of(m_assetReleaseCount.begin(), m_assetReleaseCount.end(), [](int32 n) { return n > 0; }))
		{
			LOG_ERROR(U"🔥 Assets have been created and released every frame. Set Profiler::EnableAssetCreationWarning(false) to suppress this assertion.");
			System::MessageBoxOK(U"Asset creation report", U"🔥 Assets (Textures, Fonts or Audio) have been created and released every frame. Set Profiler::EnableAssetCreationWarning(false) to suppress this assertion.", MessageBoxStyle::Error);
			return false;
		}

		std::rotate(m_assetCreationCount.rbegin(), m_assetCreationCount.rbegin() + 1, m_assetCreationCount.rend());
		std::rotate(m_assetReleaseCount.rbegin(), m_assetReleaseCount.rbegin() + 1, m_assetReleaseCount.rend());
		m_assetCreationCount[0] = m_assetReleaseCount[0] = 0;

		return true;
	}

	void CAssetMonitor::setWarningEnabled(const bool enabled)
	{
		m_assetCreationWarningEnabled = enabled;
	}

	void CAssetMonitor::created()
	{
		++m_assetCreationCount[0];
	}

	void CAssetMonitor::released()
	{
		++m_assetReleaseCount[0];
	}
}
