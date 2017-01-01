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
# include <functional>
# include <cmath>
# include "MathConstants.hpp"
# include "Lerp.hpp"

namespace s3d
{
	/// <summary>
	/// イージング
	/// </summary>
	/// <remarks>
	/// イージング関数を提供します。
	/// </remarks>
	namespace Easing
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

		inline constexpr double Linear(const double t)
		{
			return t;
		}

		inline double Sine(const double t)
		{
			return 1.0 - std::cos(t * Math::HalfPi);
		}

		inline constexpr double Quad(const double t)
		{
			return t * t;
		}

		inline constexpr double Cubic(const double t)
		{
			return t * t * t;
		}

		inline constexpr double Quart(const double t)
		{
			return (t * t) * (t * t);
		}

		inline constexpr double Quint(const double t)
		{
			return (t * t) * (t * t) * t;
		}

		inline double Expo(const double t)
		{
			return t == 0.0 ? 0.0 : std::exp2(10.0 * (t - 1.0));
		}

		inline double Circ(const double t)
		{
			return 1.0 - std::sqrt(1.0 - t * t);
		}

		inline constexpr double Back(const double t)
		{
			return t * t * (2.70158 * t - 1.70158);
		}

		inline double Elastic(const double t)
		{
			return detail::ElasticAP(t, 1.0, 0.3);
		}

		inline S3D_CONSTEXPR_CPP14 double Bounce(double t)
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

	inline constexpr double EaseIn(double f(double), const double t)
	{
		return f(t);
	}

	inline constexpr double EaseOut(double f(double), const double t)
	{
		return 1.0 - f(1.0 - t);
	}

	inline constexpr double EaseInOut(double f(double), const double t)
	{
		return (t < 0.5) ? f(2.0 * t) * 0.5 : 0.5 + EaseOut(f, 2.0 * t - 1.0) * 0.5;
	}

	template <class Type>
	inline constexpr Type EaseIn(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, f(t));
	}

	template <class Type>
	inline constexpr Type EaseOut(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, EaseOut(f, t));
	}

	template <class Type>
	inline constexpr Type EaseInOut(double f(double), const Type& start, const Type& end, const double t)
	{
		return Math::Lerp(start, end, EaseInOut(f, t));
	}
}
