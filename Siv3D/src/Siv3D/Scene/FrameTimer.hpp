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
# include <Siv3D/Common.hpp>
# include <Siv3D/Scene.hpp>

namespace s3d
{
	class FrameTimer
	{
	private:

		double m_timeSec = 0.0;

		double m_deltaTimeSec = 0.0;

		double m_maxDeltaTimeSec = Scene::DefaultMaxDeltaTime;

		uint64 m_previousFrameTimeNanosec = 0;

	public:

		void update();

		[[nodiscard]]
		double getTimeSec() const noexcept;

		[[nodiscard]]
		double getDeltaTimeSec() const noexcept;

		[[nodiscard]]
		double getMaxDeltaTimeSec() const noexcept;

		void setMaxDeltaTimeSec(double timeSec) noexcept;
	};
}
