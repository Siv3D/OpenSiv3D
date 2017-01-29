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

namespace s3d
{
	namespace Math
	{
		/// <summary>
		/// π
		/// </summary>
		constexpr double Pi = 3.14159265358979323846;

		/// <summary>
		/// π (float)
		/// </summary>
		constexpr float PiF = 3.14159265358979323846f;

		/// <summary>
		/// 2π
		/// </summary>
		constexpr double TwoPi = Pi * 2.0;

		/// <summary>
		/// 2π (float)
		/// </summary>
		constexpr float TwoPiF = PiF * 2.0f;

		/// <summary>
		/// (1/2)π
		/// </summary>
		constexpr double HalfPi = Pi / 2.0;

		/// <summary>
		/// (1/2)π (float)
		/// </summary>
		constexpr float HalfPiF = PiF / 2.0f;

		/// <summary>
		/// (1/3)π
		/// </summary>
		constexpr double OneThirdPi = Pi / 3.0;

		/// <summary>
		/// (1/3)π (float)
		/// </summary>
		constexpr float OneThirdPiF = PiF / 3.0f;

		/// <summary>
		/// (1/4)π
		/// </summary>
		constexpr double QuarterPi = Pi / 4.0;

		/// <summary>
		/// (1/4)π (float)
		/// </summary>
		constexpr float QuarterPiF = PiF / 4.0f;

		/// <summary>
		/// Quiet NaN
		/// </summary>
		constexpr double QNaN = std::numeric_limits<double>::quiet_NaN();

		/// <summary>
		/// Signaling NaN
		/// </summary>
		constexpr double NaN = std::numeric_limits<double>::signaling_NaN();

		/// <summary>
		/// +Inf
		/// </summary>
		constexpr double Inf = std::numeric_limits<double>::infinity();
	}

	inline namespace literals
	{
		inline namespace math_literals
		{
			constexpr double operator ""_pi(long double x)
			{
				return static_cast<double>(x * Math::Pi);
			}

			constexpr double operator ""_pi(unsigned long long x)
			{
				return static_cast<double>(x * Math::Pi);
			}
		}

		inline namespace angle_literals
		{
			constexpr double operator ""_deg(long double deg)
			{
				return static_cast<double>(deg * Math::Pi / 180);
			}

			constexpr double operator ""_deg(unsigned long long deg)
			{
				return static_cast<double>(deg * Math::Pi / 180);
			}
		}
	}
}
