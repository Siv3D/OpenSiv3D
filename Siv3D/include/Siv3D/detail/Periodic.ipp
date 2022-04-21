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

namespace s3d
{
	namespace Periodic
	{
		inline double Sine0_1(const double periodSec, const double t) noexcept
		{
			const double x = (std::fmod(t, periodSec) / (periodSec * Math::InvTwoPi));

			return (std::sin(x) * 0.5 + 0.5);
		}

		inline double Sine0_1(const Duration& period, const double t) noexcept
		{
			return Sine0_1(period.count(), t);
		}

		inline double Square0_1(const double periodSec, const double t) noexcept
		{
			return (std::fmod(t, periodSec) < (periodSec * 0.5)) ? 1.0 : 0.0;
		}

		inline double Square0_1(const Duration& period, const double t) noexcept
		{
			return Square0_1(period.count(), t);
		}

		inline double Triangle0_1(const double periodSec, const double t) noexcept
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

		inline double Triangle0_1(const Duration& period, const double t) noexcept
		{
			return Triangle0_1(period.count(), t);
		}

		inline double Sawtooth0_1(const double periodSec, const double t) noexcept
		{
			return std::fmod(t, periodSec) / periodSec;
		}

		inline double Sawtooth0_1(const Duration& period, const double t) noexcept
		{
			return Sawtooth0_1(period.count(), t);
		}

		inline double Jump0_1(const double periodSec, const double t) noexcept
		{
			double x = (std::fmod(t, periodSec) / (periodSec * 0.5));

			if (1.0 < x)
			{
				x = (2.0 - x);
			}

			return (2 * x - (x * x));
		}

		inline double Jump0_1(const Duration& period, const double t) noexcept
		{
			return Jump0_1(period.count(), t);
		}


		inline double Sine1_1(const double periodSec, const double t) noexcept
		{
			const double x = (std::fmod(t, periodSec) / (periodSec * Math::InvTwoPi));

			return std::sin(x);
		}

		inline double Sine1_1(const Duration& period, const double t) noexcept
		{
			return Sine1_1(period.count(), t);
		}

		inline double Square1_1(const double periodSec, const double t) noexcept
		{
			return (std::fmod(t, periodSec) < (periodSec * 0.5)) ? 1.0 : -1.0;
		}

		inline double Square1_1(const Duration& period, const double t) noexcept
		{
			return Square1_1(period.count(), t);
		}

		inline double Triangle1_1(const double periodSec, const double t) noexcept
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

		inline double Triangle1_1(const Duration& period, const double t) noexcept
		{
			return Triangle1_1(period.count(), t);
		}

		inline double Sawtooth1_1(const double periodSec, const double t) noexcept
		{
			return ((std::fmod(t, periodSec) / periodSec) * 2.0 - 1.0);
		}

		inline double Sawtooth1_1(const Duration& period, const double t) noexcept
		{
			return Sawtooth1_1(period.count(), t);
		}

		inline double Jump1_1(const double periodSec, const double t) noexcept
		{
			double x = (std::fmod(t, periodSec) / (periodSec * 0.5));

			if (1.0 < x)
			{
				x = (2.0 - x);
			}

			return ((2 * x - (x * x)) * 2.0 - 1.0);
		}

		inline double Jump1_1(const Duration& period, const double t) noexcept
		{
			return Jump1_1(period.count(), t);
		}
	}
}
