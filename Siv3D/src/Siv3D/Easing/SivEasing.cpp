//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Easing.hpp>

namespace s3d
{
	namespace detail
	{
		double ElasticAP(double t, double a, const double p) noexcept
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
}
