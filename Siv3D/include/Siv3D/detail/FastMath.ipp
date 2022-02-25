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
	namespace FastMath
	{
		inline constexpr std::pair<float, float> SinCos(const float angleRadians) noexcept
		{
			float quotient = (Math::InvTwoPiF * angleRadians);

			if (angleRadians >= 0.0f)
			{
				quotient = static_cast<float>(static_cast<int32>(quotient + 0.5f));
			}
			else
			{
				quotient = static_cast<float>(static_cast<int32>(quotient - 0.5f));
			}

			float y = (angleRadians - (Math::TwoPiF * quotient));
			float sign = 1.0f;

			if (y > Math::HalfPiF)
			{
				y = (Math::PiF - y);
				sign = -1.0f;
			}
			else if (y < -Math::HalfPiF)
			{
				y = (-Math::PiF - y);
				sign = -1.0f;
			}

			const float y2 = (y * y);
			const float sin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
			const float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
			const float cos = (sign * p);

			return{ sin, cos };
		}

		inline constexpr std::pair<float, float> SinCos(const double angleRadians) noexcept
		{
			double quotient = (Math::InvTwoPi * angleRadians);

			if (angleRadians >= 0.0)
			{
				quotient = static_cast<double>(static_cast<int32>(quotient + 0.5));
			}
			else
			{
				quotient = static_cast<double>(static_cast<int32>(quotient - 0.5));
			}

			float y = static_cast<float>(angleRadians - (Math::TwoPi * quotient));
			float sign = 1.0f;

			if (y > Math::HalfPiF)
			{
				y = (Math::PiF - y);
				sign = -1.0f;
			}
			else if (y < -Math::HalfPiF)
			{
				y = (-Math::PiF - y);
				sign = -1.0f;
			}

			const float y2 = (y * y);
			const float sin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
			const float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
			const float cos = (sign * p);

			return{ sin, cos };
		}

	# if __cpp_lib_bit_cast

		inline constexpr float InvSqrt(float x) noexcept
		{
			const float xhalf = (x * 0.5f);
			int32 i = std::bit_cast<int32>(x);
			i = 0x5f375a86 - (i >> 1);
			x = std::bit_cast<float>(i);
			x = x * (1.5f - (xhalf * x * x));
			return x;
		}

		inline constexpr double InvSqrt(double x) noexcept
		{
			const double xhalf = (x * 0.5);
			int64 i = std::bit_cast<int64>(x);
			i = 0x5fe6eb50c7b537a9 - (i >> 1);
			x = std::bit_cast<double>(i);
			x = x * (1.5 - (xhalf * x * x));
			return x;
		}

		inline constexpr double InvSqrtQuality(double x) noexcept
		{
			const double xhalf = (x * 0.5);
			int64 i = std::bit_cast<int64>(x);
			i = 0x5fe6eb50c7b537a9 - (i >> 1);
			x = std::bit_cast<double>(i);
			x = x * (1.5 - (xhalf * x * x));
			x = x * (1.5 - (xhalf * x * x));
			return x;
		}

		inline constexpr float Sqrt(const float x) noexcept
		{
			return (x * InvSqrt(x));
		}

		inline constexpr double Sqrt(const double x) noexcept
		{
			return (x * InvSqrt(x));
		}

	# else

		inline float InvSqrt(float x) noexcept
		{
			const float xhalf = (x * 0.5f);
			int32 i = *(int32*)(&x);
			i = 0x5f375a86 - (i >> 1);
			x = *(float*)(&i);
			x = x * (1.5f - (xhalf * x * x));
			return x;
		}

		inline double InvSqrt(double x) noexcept
		{
			const double xhalf = (x * 0.5);
			int64 i = *(int64*)(&x);
			i = 0x5fe6eb50c7b537a9 - (i >> 1);
			x = *(double*)(&i);
			x = x * (1.5 - (xhalf * x * x));
			return x;
		}

		inline double InvSqrtQuality(double x) noexcept
		{
			const double xhalf = (x * 0.5);
			int64 i = *(int64*)(&x);
			i = 0x5fe6eb50c7b537a9 - (i >> 1);
			x = *(double*)(&i);
			x = x * (1.5 - (xhalf * x * x));
			x = x * (1.5 - (xhalf * x * x));
			return x;
		}

		inline float Sqrt(const float x) noexcept
		{
			return (x * InvSqrt(x));
		}

		inline double Sqrt(const double x) noexcept
		{
			return (x * InvSqrt(x));
		}

	# endif
	}
}
