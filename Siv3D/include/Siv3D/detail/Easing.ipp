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
				s = p * Math::InvTwoPi * std::asin(1.0 / a);
			}

			t -= 1.0;

			return -(a * std::exp2(10.0 * t) * std::sin((t - s) * Math::TwoPi / p));
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
			return (1.0 - std::cos(t * Math::HalfPi));
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

	inline constexpr double EaseIn(double f(double), const double t) noexcept
	{
		return f(t);
	}

	template <class Type>
	inline constexpr auto EaseIn(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, f(t));
	}


	inline constexpr double EaseOut(double f(double), const double t) noexcept
	{
		return (1.0 - f(1.0 - t));
	}

	template <class Type>
	inline constexpr auto EaseOut(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, EaseOut(f, t));
	}


	inline constexpr double EaseInOut(double f(double), const double t) noexcept
	{
		return ((t < 0.5) ? (f(2.0 * t) * 0.5) : (0.5 + EaseOut(f, 2.0 * t - 1.0) * 0.5));
	}

	template <class Type>
	inline constexpr auto EaseInOut(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, EaseInOut(f, t));
	}


	inline constexpr double EaseInLinear(const double t) noexcept
	{
		return Easing::Linear(t);
	}

	inline constexpr double EaseOutLinear(const double t) noexcept
	{
		return EaseOut(Easing::Linear, t);
	}

	inline constexpr double EaseInOutLinear(const double t) noexcept
	{
		return EaseInOut(Easing::Linear, t);
	}


	inline double EaseInSine(const double t) noexcept
	{
		return Easing::Sine(t);
	}

	inline double EaseOutSine(const double t) noexcept
	{
		return EaseOut(Easing::Sine, t);
	}

	inline double EaseInOutSine(const double t) noexcept
	{
		return EaseInOut(Easing::Sine, t);
	}


	inline constexpr double EaseInQuad(const double t) noexcept
	{
		return Easing::Quad(t);
	}

	inline constexpr double EaseOutQuad(const double t) noexcept
	{
		return EaseOut(Easing::Quad, t);
	}

	inline constexpr double EaseInOutQuad(const double t) noexcept
	{
		return EaseInOut(Easing::Quad, t);
	}


	inline constexpr double EaseInCubic(const double t) noexcept
	{
		return Easing::Cubic(t);
	}

	inline constexpr double EaseOutCubic(const double t) noexcept
	{
		return EaseOut(Easing::Cubic, t);
	}

	inline constexpr double EaseInOutCubic(const double t) noexcept
	{
		return EaseInOut(Easing::Cubic, t);
	}


	inline constexpr double EaseInQuart(const double t) noexcept
	{
		return Easing::Quart(t);
	}

	inline constexpr double EaseOutQuart(const double t) noexcept
	{
		return EaseOut(Easing::Quart, t);
	}

	inline constexpr double EaseInOutQuart(const double t) noexcept
	{
		return EaseInOut(Easing::Quart, t);
	}


	inline constexpr double EaseInQuint(const double t) noexcept
	{
		return Easing::Quint(t);
	}

	inline constexpr double EaseOutQuint(const double t) noexcept
	{
		return EaseOut(Easing::Quint, t);
	}

	inline constexpr double EaseInOutQuint(const double t) noexcept
	{
		return EaseInOut(Easing::Quint, t);
	}


	inline double EaseInExpo(const double t) noexcept
	{
		return Easing::Expo(t);
	}

	inline double EaseOutExpo(const double t) noexcept
	{
		return EaseOut(Easing::Expo, t);
	}

	inline double EaseInOutExpo(const double t) noexcept
	{
		return EaseInOut(Easing::Expo, t);
	}


	inline double EaseInCirc(const double t) noexcept
	{
		return Easing::Circ(t);
	}

	inline double EaseOutCirc(const double t) noexcept
	{
		return EaseOut(Easing::Circ, t);
	}

	inline double EaseInOutCirc(const double t) noexcept
	{
		return EaseInOut(Easing::Circ, t);
	}


	inline constexpr double EaseInBack(const double t) noexcept
	{
		return Easing::Back(t);
	}

	inline constexpr double EaseOutBack(const double t) noexcept
	{
		return EaseOut(Easing::Back, t);
	}

	inline constexpr double EaseInOutBack(const double t) noexcept
	{
		return EaseInOut(Easing::Back, t);
	}


	inline double EaseInElastic(const double t) noexcept
	{
		return Easing::Elastic(t);
	}

	inline double EaseOutElastic(const double t) noexcept
	{
		return EaseOut(Easing::Elastic, t);
	}

	inline double EaseInOutElastic(const double t) noexcept
	{
		return EaseInOut(Easing::Elastic, t);
	}


	inline constexpr double EaseInBounce(const double t) noexcept
	{
		return Easing::Bounce(t);
	}

	inline constexpr double EaseOutBounce(const double t) noexcept
	{
		return EaseOut(Easing::Bounce, t);
	}

	inline constexpr double EaseInOutBounce(const double t) noexcept
	{
		return EaseInOut(Easing::Bounce, t);
	}
}
