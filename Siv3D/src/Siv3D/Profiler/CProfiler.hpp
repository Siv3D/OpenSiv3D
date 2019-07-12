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

# pragma once
# include <Siv3D/Profiler.hpp>
# include <Siv3D/Stopwatch.hpp>
# include "IProfiler.hpp"

namespace s3d
{
	class CProfiler : public ISiv3DProfiler
	{
	private:

		//
		// FPS
		//
		int32 m_fpsCount = 0;

		int32 m_currentFPS = 1;

		Stopwatch m_fpsStopwatch;

		//
		//	Stats
		//
		Statistics m_currentStatistics;

		Statistics m_previousStatistics;

		//
		// Asset creation
		//
		static constexpr int32 ReportFrameCount = 30;

		bool m_assetCreationWarningEnabled = true;

		std::array<int32, ReportFrameCount> m_assetCreationCount{};

		std::array<int32, ReportFrameCount> m_assetReleaseCount{};

	public:

		CProfiler();

		~CProfiler() override;

		void init() override;

		bool beginFrame() override;

		void endFrame() override;

		//
		// FPS
		//
		int32 getFPS() const override;

		String getSimpleStatistics() const override;

		//
		// Stats
		//
		void reportDrawcalls(size_t drawcalls, size_t triangles) override;

		Statistics getStatistics() const noexcept override;

		//
		// Asset creation
		//
		void setAssetCreationWarningEnabled(bool enabled) override;

		void reportAssetCreation() override;

		void reportAssetRelease() override;
	};
}
