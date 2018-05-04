//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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

		double m_inDuration = 0.0;

		double m_outDuration = 0.0;

		double m_value = 0.0;

	public:

		explicit constexpr Transition(const Duration& inDuration = SecondsF(0.2), const Duration& outDuration = SecondsF(0.1), double initialValue = 0.0) noexcept
			: m_inDuration(static_cast<double>(inDuration.count()))
			, m_outDuration(static_cast<double>(outDuration.count()))
			, m_value(initialValue) {}

		void update(const bool in, const double deltaSec = System::DeltaTime())
		{
			if (in)
			{
				if (m_inDuration <= 0.0)
				{
					m_value = 1.0;
					return;
				}

				m_value = std::min(m_value + (deltaSec / m_inDuration), 1.0);
			}
			else
			{
				if (m_outDuration <= 0.0)
				{
					m_value = 0.0;
					return;
				}

				m_value = std::max(m_value - (deltaSec / m_outDuration), 0.0);
			}
		}

		[[nodiscard]] constexpr double value() const noexcept
		{
			return m_value;
		}

		[[nodiscard]] constexpr double easeIn(double easingFunction(double) = Easing::Quart) const
		{
			return EaseIn(easingFunction, m_value);
		}

		[[nodiscard]] constexpr double easeOut(double easingFunction(double) = Easing::Quart) const
		{
			return EaseOut(easingFunction, m_value);
		}

		[[nodiscard]] constexpr double easeInOut(double easingFunction(double) = Easing::Quart) const
		{
			return EaseInOut(easingFunction, m_value);
		}
	};
}
