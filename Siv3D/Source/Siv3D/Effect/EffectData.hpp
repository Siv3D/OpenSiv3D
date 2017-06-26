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
# include <Siv3D/Array.hpp>

namespace s3d
{
	class EffectData
	{
	private:

		static constexpr double MaxEffectLengthSec = 10.0;

		Array<std::pair<std::unique_ptr<IEffect>, double>> m_effects;

		uint64 m_previousTimeUs = 0;

		double m_speed = 1.0;

		bool m_initialized = false;

		bool m_paused = false;

	public:

		struct Null {};

		EffectData() = default;

		EffectData(Null);

		bool isInitialized() const noexcept
		{
			return m_initialized;
		}

		void add(std::unique_ptr<IEffect>&& effect);

		size_t num_effects() const;

		void pause();

		bool isPaused() const noexcept
		{
			return m_paused;
		}

		void resume();

		void setSpeed(double speed);

		double getSpeed() const noexcept
		{
			return m_speed;
		}

		void update();

		void clear();
	};
}
