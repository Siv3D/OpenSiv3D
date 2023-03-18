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

# pragma once
# include <array>
# include "IAssetMonitor.hpp"

namespace s3d
{
	class CAssetMonitor final : public ISiv3DAssetMonitor
	{
	public:

		bool update() override;

		void setWarningEnabled(bool enabled) override;

		void created() override;

		void released() override;

	private:

		static constexpr size_t MonitoringFrameCount = 30;

		bool m_assetCreationWarningEnabled = true;

		std::array<uint32, MonitoringFrameCount> m_assetCreationCount{};

		std::array<uint32, MonitoringFrameCount> m_assetReleaseCount{};
	};
}
