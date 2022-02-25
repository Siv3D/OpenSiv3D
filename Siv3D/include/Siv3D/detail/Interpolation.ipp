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
	namespace Math
	{
		template <class T, class U, class V>
		inline constexpr auto Lerp(const T& v1, const U& v2, V f) noexcept
		{
			if constexpr (detail::HasLerp_v<T>)
			{
				return v1.lerp(v2, f);
			}
			else
			{
				return (v1 + (v2 - v1) * f);
			}
		}

		inline constexpr double InvLerp(double a, double b, double value) noexcept
		{
			return (value - a) / (b - a);
		}

		template <class T, class U>
		inline constexpr auto Map(const double value, const double a, const double b, const T& v1, const U& v2) noexcept
		{
			return Lerp(v1, v2, InvLerp(a, b, value));
		}

		template <class T, class U, class V>
		inline auto LerpAngle(const T from, const U to, const V t) noexcept
		{
			const auto diff = std::fmod(to - from, Math::TwoPi_v<CommonFloat_t<T, U>>);
			return (from + (std::fmod(2 * diff, Math::TwoPi_v<CommonFloat_t<T, U>>) - diff) * t);
		}

		inline double Eerp(const double a, const double b, const double t) noexcept
		{
			assert(a != 0.0);
			assert(0.0 <= (b / a));
			return (a * std::pow((b / a), t));
		}
	}
}
