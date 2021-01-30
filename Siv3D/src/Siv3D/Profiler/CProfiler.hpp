//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IProfiler.hpp"

namespace s3d
{
	class CProfiler final : public ISiv3DProfiler
	{
	private:

		//
		// FPS
		//
		int32 m_fpsCount = 0;

		int32 m_currentFPS = 1;

		int64 m_fpsTimestampMillisec = 0;

	public:

		void init() override;

		void beginFrame() override;

		void endFrame() override;

		int32 getFPS() const noexcept override;

		String getSimpleStatistics() const override;
	};
}
