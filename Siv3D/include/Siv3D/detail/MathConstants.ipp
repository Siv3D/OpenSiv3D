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
	inline namespace Literals
	{
		inline namespace MathLiterals
		{
			inline constexpr double operator ""_pi(const long double x) noexcept
			{
				return static_cast<double>(x * Math::Pi_v<long double>);
			}

			inline constexpr double operator ""_pi(const unsigned long long x) noexcept
			{
				return static_cast<double>(x * Math::Pi_v<long double>);
			}

			inline constexpr float operator ""_piF(const long double x) noexcept
			{
				return static_cast<float>(x * Math::Pi_v<long double>);
			}

			inline constexpr float operator ""_piF(const unsigned long long x) noexcept
			{
				return static_cast<float>(x * Math::Pi_v<long double>);
			}


			inline constexpr double operator ""_tau(const long double x) noexcept
			{
				return static_cast<double>(x * Math::Tau_v<long double>);
			}

			inline constexpr double operator ""_tau(const unsigned long long x) noexcept
			{
				return static_cast<double>(x * Math::Tau_v<long double>);
			}

			inline constexpr float operator ""_tauF(const long double x) noexcept
			{
				return static_cast<float>(x * Math::Tau_v<long double>);
			}

			inline constexpr float operator ""_tauF(const unsigned long long x) noexcept
			{
				return static_cast<float>(x * Math::Tau_v<long double>);
			}


			inline constexpr double operator ""_deg(const long double deg) noexcept
			{
				return static_cast<double>(deg * Math::Pi_v<long double> / 180);
			}

			inline constexpr double operator ""_deg(const unsigned long long deg) noexcept
			{
				return static_cast<double>(deg * Math::Pi_v<long double> / 180);
			}

			inline constexpr float operator ""_degF(const long double deg) noexcept
			{
				return static_cast<float>(deg * Math::Pi_v<long double> / 180);
			}

			inline constexpr float operator ""_degF(const unsigned long long deg) noexcept
			{
				return static_cast<float>(deg * Math::Pi_v<long double> / 180);
			}
		}
	}
}
