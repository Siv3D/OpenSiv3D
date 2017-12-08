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
		constexpr double Pi = 3.1415926535897932385;

		/// <summary>
		/// π (float)
		/// </summary>
		constexpr float PiF = 3.1415926535897932385f;

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

		/// <summary>
		/// Golden Ratio | 黄金比
		/// </summary>
		constexpr double GoldenRatio = 1.6180339887498948482;
		
		/// <summary>
		/// Euler's number | 自然対数の底
		/// </summary>
		constexpr double E = 2.7182818284590452354;
	}

	namespace Literals
	{
		constexpr double operator ""_pi(long double x)
		{
			return static_cast<double>(x * Math::Pi);
		}

		constexpr double operator ""_pi(unsigned long long x)
		{
			return static_cast<double>(x * Math::Pi);
		}

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

