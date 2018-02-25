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
		[[nodiscard]] inline double Sine0_1(const MicrosecondsF& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			const double p = static_cast<double>(period.count() / 1'000'000.0);

			const double x = std::fmod(t, p) / (p * (1.0 / Math::TwoPi));

			return std::sin(x) * 0.5 + 0.5;
		}

		[[nodiscard]] inline double Square0_1(const MicrosecondsF& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			const double p = static_cast<double>(period.count() / 1'000'000.0);

			return std::fmod(t, p) < (p * 0.5);
		}

		[[nodiscard]] inline double Tringle0_1(const MicrosecondsF& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			const double p = static_cast<double>(period.count() / 1'000'000.0);

			const double x = std::fmod(t, p) / (p * 0.5);

			return x <= 1.0 ? x : 2.0 - x;
		}

		[[nodiscard]] inline double Sawtooth0_1(const MicrosecondsF& period, double t = Time::GetMicrosec() / 1'000'000.0)
		{
			const double p = static_cast<double>(period.count() / 1'000'000.0);

			return std::fmod(t, p) / p;
		}
	}
}
