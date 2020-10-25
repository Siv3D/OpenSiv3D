//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

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

namespace s3d
{
	namespace detail
	{
		inline double ElasticAP(double t, double a, const double p) noexcept
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
				s = p * Math::Constants::InvTwoPi * std::asin(1.0 / a);
			}

			t -= 1.0;

			return -(a * std::exp2(10.0 * t) * std::sin((t - s) * Math::Constants::TwoPi / p));
		}
	}

	namespace Easing
	{
		inline constexpr double Linear(const double t) noexcept
		{
			return t;
		}

		inline double Sine(const double t) noexcept
		{
			return (1.0 - std::cos(t * Math::Constants::HalfPi));
		}

		inline constexpr double Quad(const double t) noexcept
		{
			return (t * t);
		}

		inline constexpr double Cubic(const double t) noexcept
		{
			return (t * t * t);
		}

		inline constexpr double Quart(const double t) noexcept
		{
			return (t * t) * (t * t);
		}

		inline constexpr double Quint(const double t) noexcept
		{
			return (t * t) * (t * t) * t;
		}

		inline double Expo(const double t) noexcept
		{
			if (t == 0.0)
			{
				return 0.0;
			}
			else
			{
				return std::exp2(10.0 * (t - 1.0));
			}
		}

		inline double Circ(const double t) noexcept
		{
			return (1.0 - std::sqrt(1.0 - t * t));
		}

		inline constexpr double Back(const double t) noexcept
		{
			return t * t * (2.70158 * t - 1.70158);
		}

		inline double Elastic(const double t) noexcept
		{
			return detail::ElasticAP(t, 1.0, 0.3);
		}

		inline constexpr double Bounce(double t) noexcept
		{
			t = (1.0 - t);

			if (t < (1 / 2.75))
			{
				return (1.0 - (7.5625 * t * t));
			}
			else if (t < (2 / 2.75))
			{
				t -= 1.5 / 2.75;
				return (1.0 - (7.5625 * t * t + 0.75));
			}
			else if (t < (2.5 / 2.75))
			{
				t -= 2.25 / 2.75;
				return (1.0 - (7.5625 * t * t + 0.9375));
			}
			else
			{
				t -= (2.625 / 2.75);
				return (1.0 - (7.5625 * t * t + 0.984375));
			}
		}
	}
}
