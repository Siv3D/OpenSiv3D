﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

//
// TERMS OF USE - EASING EQUATIONS
//
// Open source under the BSD License. 
//
// Copyright (c) 2001 Robert Penner
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above
//   copyright notice, this list of conditions and the following disclaimer
//   in the documentation and/or other materials provided with the
//   distribution.
// * Neither the name of the author nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

# pragma once
# include <functional>
# include <cmath>
# include "MathConstants.hpp"
# include "Lerp.hpp"

namespace s3d
{
	namespace detail
	{
		inline double ElasticAP(double t, double a, const double p)
		{
			if (t == 0)
			{
				return 0.0;
			}
			else if (t == 1)
			{
				return 1.0;
			}

			double s;

			if (a < 1.0)
			{
				a = 1.0;

				s = p / 4.0f;
			}
			else
			{
				s = p / Math::TwoPi * std::asin(1.0 / a);
			}

			t -= 1.0;

			return -(a * std::exp2(10.0 * t) * std::sin((t - s) * Math::TwoPi / p));
		}
	}

	/// <summary>
	/// イージング
	/// </summary>
	/// <remarks>
	/// イージング関数を提供します。
	/// </remarks>
	namespace Easing
	{
		[[nodiscard]] inline constexpr double Linear(const double t)
		{
			return t;
		}

		[[nodiscard]] inline double Sine(const double t)
		{
			return 1.0 - std::cos(t * Math::HalfPi);
		}

		[[nodiscard]] inline constexpr double Quad(const double t)
		{
			return t * t;
		}

		[[nodiscard]] inline constexpr double Cubic(const double t)
		{
			return t * t * t;
		}

		[[nodiscard]] inline constexpr double Quart(const double t)
		{
			return (t * t) * (t * t);
		}

		[[nodiscard]] inline constexpr double Quint(const double t)
		{
			return (t * t) * (t * t) * t;
		}

		[[nodiscard]] inline double Expo(const double t)
		{
			return t == 0.0 ? 0.0 : std::exp2(10.0 * (t - 1.0));
		}

		[[nodiscard]] inline double Circ(const double t)
		{
			return 1.0 - std::sqrt(1.0 - t * t);
		}

		[[nodiscard]] inline constexpr double Back(const double t)
		{
			return t * t * (2.70158 * t - 1.70158);
		}

		[[nodiscard]] inline double Elastic(const double t)
		{
			return detail::ElasticAP(t, 1.0, 0.3);
		}

		[[nodiscard]] inline constexpr double Bounce(double t)
		{
			t = 1.0 - t;

			if (t < 1 / 2.75)
			{
				return  1.0 - (7.5625 * t * t);
			}
			else if (t < 2 / 2.75)
			{
				t -= 1.5 / 2.75;

				return  1.0 - (7.5625 * t * t + 0.75);
			}
			else if (t < 2.5 / 2.75)
			{
				t -= 2.25 / 2.75;

				return  1.0 - (7.5625 * t * t + 0.9375);
			}
			else
			{
				t -= 2.625 / 2.75;

				return  1.0 - (7.5625 * t * t + 0.984375);
			}
		}
	}

	[[nodiscard]] inline constexpr double EaseIn(double f(double), const double t)
	{
		return f(t);
	}

	[[nodiscard]] inline constexpr double EaseOut(double f(double), const double t)
	{
		return 1.0 - f(1.0 - t);
	}

	[[nodiscard]] inline constexpr double EaseInOut(double f(double), const double t)
	{
		return (t < 0.5) ? f(2.0 * t) * 0.5 : 0.5 + EaseOut(f, 2.0 * t - 1.0) * 0.5;
	}

	template <class Type>
	[[nodiscard]] inline constexpr Type EaseIn(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, f(t));
	}

	template <class Type>
	[[nodiscard]] inline constexpr Type EaseOut(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, EaseOut(f, t));
	}

	template <class Type>
	[[nodiscard]] inline constexpr Type EaseInOut(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, EaseInOut(f, t));
	}
}
