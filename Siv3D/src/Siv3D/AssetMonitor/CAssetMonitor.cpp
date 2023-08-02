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

# include <algorithm>
# include <Siv3D/Troubleshooting/Troubleshooting.hpp>
# include "CAssetMonitor.hpp"

namespace s3d
{
	bool CAssetMonitor::update()
	{
		if (m_assetCreationWarningEnabled
			&& std::all_of(m_assetCreationCount.begin(), m_assetCreationCount.end(), [](int32 n) { return (0 < n); })
			&& std::all_of(m_assetReleaseCount.begin(), m_assetReleaseCount.end(), [](int32 n) { return (0 < n); }))
		{
			Troubleshooting::Show(Troubleshooting::Warning::InefficientAssetCreation);
			return false;
		}

		std::rotate(m_assetCreationCount.rbegin(), (m_assetCreationCount.rbegin() + 1), m_assetCreationCount.rend());
		std::rotate(m_assetReleaseCount.rbegin(), (m_assetReleaseCount.rbegin() + 1), m_assetReleaseCount.rend());
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
