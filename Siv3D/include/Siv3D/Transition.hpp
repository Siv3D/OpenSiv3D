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
# include "Duration.hpp"
# include "Easing.hpp"
# include "Scene.hpp"

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

		void update(bool in, double deltaSec = Scene::DeltaTime());

		[[nodiscard]] constexpr double value() const noexcept
		{
			return m_value;
		}

		[[nodiscard]] constexpr bool isZero() const noexcept
		{
			return (m_value == 0.0);
		}

		[[nodiscard]] constexpr bool isOne() const noexcept
		{
			return (m_value == 1.0);
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
