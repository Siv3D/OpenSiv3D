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

# pragma once
# include "IProfiler.hpp"
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	class CProfiler : public ISiv3DProfiler
	{
	private:

		int32 m_fpsCount = 0;

		int32 m_currentFPS = 1;

		Stopwatch m_fpsStopwatch;

	public:

		CProfiler();

		~CProfiler() override;

		bool init() override;

		void beginFrame() override;

		void endFrame() override;

		int32 getFPS() const override;
	};
}
