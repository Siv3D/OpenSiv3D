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
# include "Fwd.hpp"
# include "Duration.hpp"
# include "Time.hpp"
# include "Math.hpp"

namespace s3d
{
	namespace Periodic
	{
		[[nodiscard]] inline double Sine0_1(double periodSec, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			const double x = std::fmod(t, periodSec) / (periodSec * (1.0 / Math::TwoPi));

			return std::sin(x) * 0.5 + 0.5;
		}

		[[nodiscard]] inline double Sine0_1(const Duration& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			return Sine0_1(period.count(), t);
		}

		[[nodiscard]] inline double Square0_1(double periodSec, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			return std::fmod(t, periodSec) < (periodSec * 0.5);
		}

		[[nodiscard]] inline double Square0_1(const Duration& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			return Square0_1(period.count(), t);
		}

		[[nodiscard]] inline double Tringle0_1(double periodSec, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			const double x = std::fmod(t, periodSec) / (periodSec * 0.5);

			return x <= 1.0 ? x : 2.0 - x;
		}

		[[nodiscard]] inline double Tringle0_1(const Duration& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			return Tringle0_1(period.count(), t);
		}

		[[nodiscard]] inline double Sawtooth0_1(double periodSec, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			return std::fmod(t, periodSec) / periodSec;
		}

		[[nodiscard]] inline double Sawtooth0_1(const Duration& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			return Sawtooth0_1(period.count(), t);
		}
	}
}
