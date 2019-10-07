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
# include "Fwd.hpp"
# include "Duration.hpp"
# include "Scene.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	namespace Periodic
	{
		[[nodiscard]] inline double Sine0_1(double periodSec, double t = Scene::Time())
		{
			const double x = std::fmod(t, periodSec) / (periodSec * (1.0 / Math::TwoPi));

			return std::sin(x) * 0.5 + 0.5;
		}

		[[nodiscard]] inline double Sine0_1(const Duration& period, double t = Scene::Time())
		{
			return Sine0_1(period.count(), t);
		}

		[[nodiscard]] inline double Square0_1(double periodSec, double t = Scene::Time())
		{
			return (std::fmod(t, periodSec) < (periodSec * 0.5)) ? 1.0 : 0.0;
		}

		[[nodiscard]] inline double Square0_1(const Duration& period, double t = Scene::Time())
		{
			return Square0_1(period.count(), t);
		}

		[[nodiscard]] inline double Triangle0_1(double periodSec, double t = Scene::Time())
		{
			const double x = std::fmod(t, periodSec) / (periodSec * 0.5);

			return x <= 1.0 ? x : 2.0 - x;
		}

		[[nodiscard]] inline double Triangle0_1(const Duration& period, double t = Scene::Time())
		{
			return Triangle0_1(period.count(), t);
		}

		[[nodiscard]] inline double Sawtooth0_1(double periodSec, double t = Scene::Time())
		{
			return std::fmod(t, periodSec) / periodSec;
		}

		[[nodiscard]] inline double Sawtooth0_1(const Duration& period, double t = Scene::Time())
		{
			return Sawtooth0_1(period.count(), t);
		}

		[[nodiscard]] inline double Jump0_1(double periodSec, double t = Scene::Time())
		{
			double x = std::fmod(t, periodSec) / (periodSec * 0.5);

			if (1.0 < x)
			{
				x = 2.0 - x;
			}

			return 2 * x - (x * x);
		}

		[[nodiscard]] inline double Jump0_1(const Duration& period, double t = Scene::Time())
		{
			return Jump0_1(period.count(), t);
		}
	}
}
