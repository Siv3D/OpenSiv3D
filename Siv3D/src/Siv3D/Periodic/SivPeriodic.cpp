﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Periodic.hpp>

namespace s3d
{
	namespace Periodic
	{
		double Sine0_1(const double periodSec, const double t) noexcept
		{
			const double x = (std::fmod(t, periodSec) / (periodSec * Math::InvTwoPi));

			return (std::sin(x) * 0.5 + 0.5);
		}

		double Sine0_1(const Duration& period, const double t) noexcept
		{
			return Sine0_1(period.count(), t);
		}

		double Square0_1(const double periodSec, const double t) noexcept
		{
			return (std::fmod(t, periodSec) < (periodSec * 0.5)) ? 1.0 : 0.0;
		}

		double Square0_1(const Duration& period, const double t) noexcept
		{
			return Square0_1(period.count(), t);
		}

		double Triangle0_1(const double periodSec, const double t) noexcept
		{
			const double x = (std::fmod(t, periodSec) / (periodSec * 0.5));

			if (x <= 1.0)
			{
				return x;
			}
			else
			{
				return (2.0 - x);
			}
		}

		double Triangle0_1(const Duration& period, const double t) noexcept
		{
			return Triangle0_1(period.count(), t);
		}

		double Sawtooth0_1(const double periodSec, const double t) noexcept
		{
			return std::fmod(t, periodSec) / periodSec;
		}

		double Sawtooth0_1(const Duration& period, const double t) noexcept
		{
			return Sawtooth0_1(period.count(), t);
		}

		double Jump0_1(const double periodSec, const double t) noexcept
		{
			double x = (std::fmod(t, periodSec) / (periodSec * 0.5));

			if (1.0 < x)
			{
				x = (2.0 - x);
			}

			return (2 * x - (x * x));
		}

		double Jump0_1(const Duration& period, const double t) noexcept
		{
			return Jump0_1(period.count(), t);
		}


		double Sine1_1(const double periodSec, const double t) noexcept
		{
			const double x = (std::fmod(t, periodSec) / (periodSec * Math::InvTwoPi));

			return std::sin(x);
		}

		double Sine1_1(const Duration& period, const double t) noexcept
		{
			return Sine1_1(period.count(), t);
		}

		double Square1_1(const double periodSec, const double t) noexcept
		{
			return (std::fmod(t, periodSec) < (periodSec * 0.5)) ? 1.0 : -1.0;
		}

		double Square1_1(const Duration& period, const double t) noexcept
		{
			return Square1_1(period.count(), t);
		}

		double Triangle1_1(const double periodSec, const double t) noexcept
		{
			const double x = (std::fmod(t, periodSec) / (periodSec * 0.5));

			if (x <= 1.0)
			{
				return (2.0 * x - 1.0);
			}
			else
			{
				return (3.0 - 2.0 * x);
			}
		}

		double Triangle1_1(const Duration& period, const double t) noexcept
		{
			return Triangle1_1(period.count(), t);
		}

		double Sawtooth1_1(const double periodSec, const double t) noexcept
		{
			return ((std::fmod(t, periodSec) / periodSec) * 2.0 - 1.0);
		}

		double Sawtooth1_1(const Duration& period, const double t) noexcept
		{
			return Sawtooth1_1(period.count(), t);
		}

		double Jump1_1(const double periodSec, const double t) noexcept
		{
			double x = (std::fmod(t, periodSec) / (periodSec * 0.5));

			if (1.0 < x)
			{
				x = (2.0 - x);
			}

			return ((2 * x - (x * x)) * 2.0 - 1.0);
		}

		double Jump1_1(const Duration& period, const double t) noexcept
		{
			return Jump1_1(period.count(), t);
		}
	}
}
