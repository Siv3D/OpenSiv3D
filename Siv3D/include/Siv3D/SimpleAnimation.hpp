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

# pragma once
# include "Common.hpp"
# include "Stopwatch.hpp"
# include "Easing.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class SimpleAnimation
	{
	public:

		struct KeyFrame
		{
			SecondsF time;

			double value;
		};

		SIV3D_NODISCARD_CXX20
		SimpleAnimation() = default;

		SIV3D_NODISCARD_CXX20
		explicit SimpleAnimation(ISteadyClock* pSteadyClock);

		SimpleAnimation& set(StringView name, const KeyFrame& a, const KeyFrame& b, double func(double) = Easing::Linear);

		SimpleAnimation& setLoop(const SecondsF& loopEnd);

		SimpleAnimation& setLoop(const SecondsF& loopBegin, const SecondsF& loopEnd);

		[[nodiscard]]
		double operator [](StringView name) const;

		void start();

		void pause();

		void resume();

		void restart();

		double posSec() const;

		[[nodiscard]]
		double lengthSec() const noexcept;

		[[nodiscard]]
		bool isDone() const;

		[[nodiscard]]
		size_t loopCount() const;

	private:

		struct Animation
		{
			KeyFrame a;
			KeyFrame b;
			double(*func)(double) = nullptr;
		};

		Stopwatch m_stopwatch;

		std::pair<double, double> m_loopTiming = { 0.0, 0.0 };

		HashTable<String, Array<Animation>> m_animations;

		double m_animationDurationSec = 0.0;

		[[nodiscard]]
		static double GetValue(const Array<Animation>& animations, double timeSec);
	};
}
