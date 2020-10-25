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

namespace s3d
{
	inline namespace Literals
	{
		inline namespace MathLiterals
		{
			inline constexpr double operator ""_pi(const long double x)
			{
				return static_cast<double>(x * Math::Pi);
			}

			inline constexpr double operator ""_pi(const unsigned long long x)
			{
				return static_cast<double>(x * Math::Pi);
			}

			inline constexpr double operator ""_deg(const long double deg)
			{
				return static_cast<double>(deg * Math::Pi / 180);
			}

			inline constexpr double operator ""_deg(const unsigned long long deg)
			{
				return static_cast<double>(deg * Math::Pi / 180);
			}
		}
	}
}
