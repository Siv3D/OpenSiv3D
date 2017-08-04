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
# include "Duration.hpp"
# include "Easing.hpp"
# include "System.hpp"

namespace s3d
{
	class Transition
	{
	private:

		double m_inDurationMillisec = 0.0;

		double m_outDurationMillisec = 0.0;

		double m_value = 0.0;

	public:

		explicit constexpr Transition(const MillisecondsF& inDuration = MillisecondsF(0.2), const MillisecondsF& outDuration = MillisecondsF(0.1), double initialValue = 0.0) noexcept
			: m_inDurationMillisec(static_cast<double>(inDuration.count()))
			, m_outDurationMillisec(static_cast<double>(outDuration.count()))
			, m_value(initialValue) {}

		void update(bool in, double deltaSec = System::DeltaTime())
		{
			const double deltaMillisec = deltaSec * 1000.0;

			if (in)
			{
				if (m_inDurationMillisec <= 0.0)
				{
					m_value = 1.0;
					return;
				}

				m_value = std::min(m_value + (deltaMillisec / m_inDurationMillisec), 1.0);
			}
			else
			{
				if (m_outDurationMillisec <= 0.0)
				{
					m_value = 0.0;
					return;
				}

				m_value = std::max(m_value - (deltaMillisec / m_outDurationMillisec), 0.0);
			}
		}

		constexpr double value() const noexcept
		{
			return m_value;
		}

		double easeIn(double easingFunction(double) = Easing::Quart) const
		{
			return EaseIn(easingFunction, m_value);
		}

		double easeOut(double easingFunction(double) = Easing::Quart) const
		{
			return EaseOut(easingFunction, m_value);
		}

		double easeInOut(double easingFunction(double) = Easing::Quart) const
		{
			return EaseInOut(easingFunction, m_value);
		}
	};
}
