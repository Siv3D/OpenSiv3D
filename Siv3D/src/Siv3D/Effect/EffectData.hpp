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
# include <memory>
# include <list>
# include <Siv3D/Common.hpp>
# include <Siv3D/IEffect.hpp>

namespace s3d
{
	class EffectData
	{
	public:

		struct Null {};

		EffectData() = default;

		EffectData(Null, double maxLifeTimeSec = 10.0);

		[[nodiscard]]
		bool isInitialized() const noexcept;

		void add(std::unique_ptr<IEffect>&& effect);

		size_t num_effects() const noexcept;

		void pause() noexcept;

		bool isPaused() const noexcept;

		void resume() noexcept;

		void setSpeed(double speed) noexcept;

		double getSpeed() const noexcept;

		void setMaxLifeTime(double maxLifeTimeSec) noexcept;

		double getMaxLifeTime() const noexcept;

		void setCurrectDeltaTimeUs(uint64 currentDeltaUs) noexcept;

		void update();

		void clear();

	private:

		std::list<std::pair<std::unique_ptr<IEffect>, double>> m_effects;

		double m_maxLifeTimeSec = 10.0;

		double m_lastDeltaSec = 0.0;

		double m_speed = 1.0;

		bool m_paused = false;

		bool m_initialized = false;
	};
}
