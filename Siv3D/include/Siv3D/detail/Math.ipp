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

# define SIV3D_MATH_FUNCTION_X(FUNC)							\
inline Float2 FUNC(const Float2 v) noexcept						\
{																\
	return{ FUNC(v.x), FUNC(v.y) };								\
}																\
inline Float3 FUNC(const Float3 v) noexcept						\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z) };					\
}																\
inline Float4 FUNC(const Float4 v) noexcept						\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z), FUNC(v.w) };		\
}																\
inline Vec2 FUNC(const Vec2 v) noexcept							\
{																\
	return{ FUNC(v.x), FUNC(v.y) };								\
}																\
inline Vec3 FUNC(const Vec3 v) noexcept							\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z) };					\
}																\
inline Vec4 FUNC(const Vec4 v) noexcept							\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z), FUNC(v.w) };		\
}

# define SIV3D_MATH_FUNCTION_CONSTEXPR_X(FUNC)					\
inline constexpr Float2 FUNC(const Float2 v) noexcept			\
{																\
	return{ FUNC(v.x), FUNC(v.y) };								\
}																\
inline constexpr Float3 FUNC(const Float3 v) noexcept			\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z) };					\
}																\
inline constexpr Float4 FUNC(const Float4 v) noexcept			\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z), FUNC(v.w) };		\
}																\
inline constexpr Vec2 FUNC(const Vec2 v) noexcept				\
{																\
	return{ FUNC(v.x), FUNC(v.y) };								\
}																\
inline constexpr Vec3 FUNC(const Vec3 v) noexcept				\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z) };					\
}																\
inline constexpr Vec4 FUNC(const Vec4 v) noexcept				\
{																\
	return{ FUNC(v.x), FUNC(v.y), FUNC(v.z), FUNC(v.w) };		\
}

# define SIV3D_MATH_FUNCTION_XY(FUNC)													\
inline Float2 FUNC(const Float2 v1, const Float2 v2) noexcept							\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y) };										\
}																						\
inline Float3 FUNC(const Float3 v1, const Float3 v2) noexcept							\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z) };						\
}																						\
inline Float4 FUNC(const Float4 v1, const Float4 v2) noexcept							\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z), FUNC(v1.w, v2.w) };	\
}																						\
inline Vec2 FUNC(const Vec2 v1, const Vec2 v2) noexcept									\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y) };										\
}																						\
inline Vec3 FUNC(const Vec3 v1, const Vec3 v2) noexcept									\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z) };						\
}																						\
inline Vec4 FUNC(const Vec4 v1, const Vec4 v2) noexcept									\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z), FUNC(v1.w, v2.w) };	\
}

# define SIV3D_MATH_FUNCTION_CONSTEXPR_XY(FUNC)											\
inline constexpr Float2 FUNC(const Float2 v1, const Float2 v2) noexcept					\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y) };										\
}																						\
inline constexpr Float3 FUNC(const Float3 v1, const Float3 v2) noexcept					\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z) };						\
}																						\
inline constexpr Float4 FUNC(const Float4 v1, const Float4 v2) noexcept					\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z), FUNC(v1.w, v2.w) };	\
}																						\
inline constexpr Vec2 FUNC(const Vec2 v1, const Vec2 v2) noexcept						\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y) };										\
}																						\
inline constexpr Vec3 FUNC(const Vec3 v1, const Vec3 v2) noexcept						\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z) };						\
}																						\
inline constexpr Vec4 FUNC(const Vec4 v1, const Vec4 v2) noexcept						\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z), FUNC(v1.w, v2.w) };	\
}

# define SIV3D_MATH_FUNCTION_XYREF(FUNC)												\
inline Float2 FUNC(const Float2 v1, Float2& v2) noexcept								\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y) };										\
}																						\
inline Float3 FUNC(const Float3 v1, Float3& v2) noexcept								\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z) };						\
}																						\
inline Float4 FUNC(const Float4 v1, Float4& v2) noexcept								\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z), FUNC(v1.w, v2.w) };	\
}																						\
inline Vec2 FUNC(const Vec2 v1, Vec2& v2) noexcept										\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y) };										\
}																						\
inline Vec3 FUNC(const Vec3 v1, Vec3& v2) noexcept										\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z) };						\
}																						\
inline Vec4 FUNC(const Vec4 v1, Vec4& v2) noexcept										\
{																						\
	return{ FUNC(v1.x, v2.x), FUNC(v1.y, v2.y), FUNC(v1.z, v2.z), FUNC(v1.w, v2.w) };	\
}

namespace s3d
{
	namespace Math
	{
		//////////////////////////////////////////////////
		//
		//	Fmod
		//
		//////////////////////////////////////////////////

		inline float Fmod(const float x, const float y) noexcept
		{
			return std::fmod(x, y);
		}

		inline double Fmod(const double x, const double y) noexcept
		{
			return std::fmod(x, y);
		}

		template <class T1, class T2, class R>
		inline R Fmod(const T1 x, const T2 y) noexcept
		{
			return std::fmod(static_cast<R>(x), static_cast<R>(y));
		}

		SIV3D_MATH_FUNCTION_XY(Fmod)

		//////////////////////////////////////////////////
		//
		//	Fraction
		//
		//////////////////////////////////////////////////

		inline float Fraction(const float x) noexcept
		{
			return (x - std::floor(x));
		}

		inline double Fraction(const double x) noexcept
		{
			return (x - std::floor(x));
		}

		SIV3D_MATH_FUNCTION_X(Fraction)

		//////////////////////////////////////////////////
		//
		//	Frexp
		//
		//////////////////////////////////////////////////

		inline float Frexp(const float x, float& exp) noexcept
		{
			int32 e;
			const auto t = std::frexp(x, &e);
			exp = static_cast<float>(e);
			return t;
		}

		inline double Frexp(const double x, double& exp) noexcept
		{
			int32 e;
			const auto t = std::frexp(x, &e);
			exp = e;
			return t;
		}

		SIV3D_MATH_FUNCTION_XYREF(Frexp)

		//////////////////////////////////////////////////
		//
		//	Ldexp
		//
		//////////////////////////////////////////////////

		inline float Ldexp(const float x, const float exp) noexcept
		{
			return (x * std::pow(2.0f, exp));
		}

		inline double Ldexp(const double x, const double exp) noexcept
		{
			return (x * std::pow(2.0, exp));
		}

		SIV3D_MATH_FUNCTION_XY(Ldexp)

		//////////////////////////////////////////////////
		//
		//	Log
		//
		//////////////////////////////////////////////////

		inline float Log(const float x) noexcept
		{
			return std::log(x);
		}

		inline double Log(const double x) noexcept
		{
			return std::log(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Log(const Arithmetic x) noexcept
		{
			return std::log(x);
		}

		SIV3D_MATH_FUNCTION_X(Log)

		//////////////////////////////////////////////////
		//
		//	Log2
		//
		//////////////////////////////////////////////////

		inline float Log2(const float x) noexcept
		{
			return std::log2(x);
		}

		inline double Log2(const double x) noexcept
		{
			return std::log2(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Log2(const Arithmetic x) noexcept
		{
			return std::log2(x);
		}

		SIV3D_MATH_FUNCTION_X(Log2)

		//////////////////////////////////////////////////
		//
		//	Log10
		//
		//////////////////////////////////////////////////

		inline float Log10(const float x) noexcept
		{
			return std::log10(x);
		}

		inline double Log10(const double x) noexcept
		{
			return std::log10(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Log10(const Arithmetic x) noexcept
		{
			return std::log10(x);
		}

		SIV3D_MATH_FUNCTION_X(Log10)

		//////////////////////////////////////////////////
		//
		//	Modf
		//
		//////////////////////////////////////////////////

		inline float Modf(float x, float& i) noexcept
		{
			return std::modf(x, &i);
		}

		inline double Modf(double x, double& i) noexcept
		{
			return std::modf(x, &i);
		}

		SIV3D_MATH_FUNCTION_XYREF(Modf)

		//////////////////////////////////////////////////
		//
		//	Pow
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T1>, std::is_arithmetic<T2>>>*>
		inline auto Pow(const T1 x, const T2 y) noexcept
		{
			return std::pow(x, y);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline Float2 Pow(const Float2 x, const Arithmetic y) noexcept
		{
			return{ std::pow(x.x, y), std::pow(x.y, y) };
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline Float3 Pow(const Float3 x, const Arithmetic y) noexcept
		{
			return{ std::pow(x.x, y), std::pow(x.y, y), std::pow(x.z, y) };
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline Float4 Pow(const Float4 x, const Arithmetic y) noexcept
		{
			return{ std::pow(x.x, y), std::pow(x.y, y), std::pow(x.z, y), std::pow(x.w, y) };
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline Vec2 Pow(const Vec2 x, const Arithmetic y) noexcept
		{
			return{ std::pow(x.x, y), std::pow(x.y, y) };
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline Vec3 Pow(const Vec3 x, const Arithmetic y) noexcept
		{
			return{ std::pow(x.x, y), std::pow(x.y, y), std::pow(x.z, y) };
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline Vec4 Pow(const Vec4 x, const Arithmetic y) noexcept
		{
			return{ std::pow(x.x, y), std::pow(x.y, y), std::pow(x.z, y), std::pow(x.w, y) };
		}

		//////////////////////////////////////////////////
		//
		//	Sign
		//
		//////////////////////////////////////////////////

		SIV3D_CONCEPT_ARITHMETIC_
		inline constexpr int32 Sign(const Arithmetic x) noexcept
		{
			if (x < 0)
			{
				return -1;
			}
			else if (0 < x)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(Sign)

		//////////////////////////////////////////////////
		//
		//	ToRadians
		//
		//////////////////////////////////////////////////

		inline constexpr float ToRadians(const float x) noexcept
		{
			return (x * (PiF / 180.0f));
		}

		inline constexpr double ToRadians(const double x) noexcept
		{
			return (x * (Pi / 180.0));
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline constexpr double ToRadians(const Arithmetic x) noexcept
		{
			return (x * (Pi / 180.0));
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(ToRadians)

		//////////////////////////////////////////////////
		//
		//	ToDegrees
		//
		//////////////////////////////////////////////////

		inline constexpr float ToDegrees(const float x) noexcept
		{
			return (x * (180.0f / PiF));
		}

		inline constexpr double ToDegrees(const double x) noexcept
		{
			return (x * (180.0 / Pi));
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline constexpr double ToDegrees(const Arithmetic x) noexcept
		{
			return (x * (180.0 / Pi));
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(ToDegrees)

		//////////////////////////////////////////////////
		//
		//	Abs
		//
		//////////////////////////////////////////////////

		inline constexpr float Abs(const float x) noexcept
		{
			if (x < 0)
			{
				return -x;
			}
			else
			{
				return x;
			}
		}

		inline constexpr double Abs(const double x) noexcept
		{
			if (x < 0)
			{
				return -x;
			}
			else
			{
				return x;
			}
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline constexpr Arithmetic Abs(const Arithmetic x) noexcept
		{
			if (x < 0)
			{
				return -x;
			}
			else
			{
				return x;
			}
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(Abs)

		//////////////////////////////////////////////////
		//
		//	AbsDiff
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T1>, std::is_arithmetic<T2>>>*>
		inline constexpr auto AbsDiff(const T1 x, const T2 y) noexcept
		{
			if constexpr (std::conjunction_v<std::is_integral<T1>, std::is_integral<T2>>)
			{
				using U = std::make_unsigned_t<std::common_type_t<T1, T2>>;
				return (x > y) ? (static_cast<U>(x) - static_cast<U>(y))
					: (static_cast<U>(y) - static_cast<U>(x));
			}
			else
			{
				return Abs(x - y);
			}
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_XY(AbsDiff)

		//////////////////////////////////////////////////
		//
		//	Square
		//
		//////////////////////////////////////////////////

		inline constexpr float Square(const float x) noexcept
		{
			return (x * x);
		}

		inline constexpr double Square(const double x) noexcept
		{
			return (x * x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline constexpr Arithmetic Square(const Arithmetic x) noexcept
		{
			return (x * x);
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(Square)

		//////////////////////////////////////////////////
		//
		//	Exp
		//
		//////////////////////////////////////////////////

		inline float Exp(const float x) noexcept
		{
			return std::exp(x);
		}

		inline double Exp(const double x) noexcept
		{
			return std::exp(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Exp(const Arithmetic x) noexcept
		{
			return std::exp(x);
		}

		SIV3D_MATH_FUNCTION_X(Exp)

		//////////////////////////////////////////////////
		//
		//	Exp2
		//
		//////////////////////////////////////////////////

		inline float Exp2(const float x) noexcept
		{
			return std::exp2(x);
		}

		inline double Exp2(const double x) noexcept
		{
			return std::exp2(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Exp2(const Arithmetic x) noexcept
		{
			return std::exp2(x);
		}

		SIV3D_MATH_FUNCTION_X(Exp2)

		//////////////////////////////////////////////////
		//
		//	Rsqrt
		//
		//////////////////////////////////////////////////

		inline float Rsqrt(const float x) noexcept
		{
			return (1.0f / std::sqrt(x));
		}

		inline double Rsqrt(const double x) noexcept
		{
			return (1.0 / std::sqrt(x));
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Rsqrt(const Arithmetic x) noexcept
		{
			return (1.0 / std::sqrt(x));
		}

		SIV3D_MATH_FUNCTION_X(Rsqrt)

		//////////////////////////////////////////////////
		//
		//	Sqrt
		//
		//////////////////////////////////////////////////

		inline float Sqrt(const float x) noexcept
		{
			return std::sqrt(x);
		}

		inline double Sqrt(const double x) noexcept
		{
			return std::sqrt(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Sqrt(const Arithmetic x) noexcept
		{
			return std::sqrt(x);
		}

		SIV3D_MATH_FUNCTION_X(Sqrt)

		//////////////////////////////////////////////////
		//
		//	Ceil
		//
		//////////////////////////////////////////////////

		inline float Ceil(const float x) noexcept
		{
			return std::ceil(x);
		}

		inline double Ceil(const double x) noexcept
		{
			return std::ceil(x);
		}

		SIV3D_MATH_FUNCTION_X(Ceil)

		//////////////////////////////////////////////////
		//
		//	Floor
		//
		//////////////////////////////////////////////////

		inline float Floor(const float x) noexcept
		{
			return std::floor(x);
		}

		inline double Floor(const double x) noexcept
		{
			return std::floor(x);
		}

		SIV3D_MATH_FUNCTION_X(Floor)

		//////////////////////////////////////////////////
		//
		//	Round
		//
		//////////////////////////////////////////////////

		inline float Round(const float x) noexcept
		{
			return std::round(x);
		}

		inline double Round(const double x) noexcept
		{
			return std::round(x);
		}

		SIV3D_MATH_FUNCTION_X(Round)

		//////////////////////////////////////////////////
		//
		//	Clamp
		//
		//////////////////////////////////////////////////

		inline constexpr float Clamp(const float x, const float min, const float max) noexcept
		{
			if (max < x)
			{
				return max;
			}

			if (x < min)
			{
				return min;
			}

			return x;
		}

		inline constexpr double Clamp(const double x, const double min, const double max) noexcept
		{
			if (max < x)
			{
				return max;
			}

			if (x < min)
			{
				return min;
			}

			return x;
		}

		inline constexpr Point Clamp(const Point v, const int32 min, const int32 max) noexcept
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max) };
		}

		inline constexpr Float2 Clamp(const Float2 v, const float min, const float max) noexcept
		{
			return{ Clamp(v.x, min, max), Clamp(v.y, min, max) };
		}

		inline constexpr Float3 Clamp(const Float3 v, const float min, const float max) noexcept
		{
			return{ Clamp(v.x, min, max), Clamp(v.y, min, max), Clamp(v.z, min, max) };
		}

		inline constexpr Float4 Clamp(const Float4 v, const float min, const float max) noexcept
		{
			return{ Clamp(v.x, min, max), Clamp(v.y, min, max), Clamp(v.z, min, max), Clamp(v.w, min, max) };
		}

		inline constexpr Vec2 Clamp(const Vec2 v, const double min, const double max) noexcept
		{
			return{ Clamp(v.x, min, max), Clamp(v.y, min, max) };
		}

		inline constexpr Vec3 Clamp(const Vec3 v, const double min, const double max) noexcept
		{
			return{ Clamp(v.x, min, max), Clamp(v.y, min, max), Clamp(v.z, min, max) };
		}

		inline constexpr Vec4 Clamp(const Vec4 v, const double min, const double max) noexcept
		{
			return{ Clamp(v.x, min, max), Clamp(v.y, min, max), Clamp(v.z, min, max), Clamp(v.w, min, max) };
		}

		//////////////////////////////////////////////////
		//
		//	Saturate
		//
		//////////////////////////////////////////////////

		inline constexpr float Saturate(const float x) noexcept
		{
			return Clamp(x, 0.0f, 1.0f);
		}

		inline constexpr double Saturate(const double x) noexcept
		{
			return Clamp(x, 0.0, 1.0);
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(Saturate)

		//////////////////////////////////////////////////
		//
		//	Acos
		//
		//////////////////////////////////////////////////

		inline float Acos(const float x) noexcept
		{
			return std::acos(x);
		}

		inline double Acos(const double x) noexcept
		{
			return std::acos(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Acos(const Arithmetic x) noexcept
		{
			return std::acos(x);
		}

		SIV3D_MATH_FUNCTION_X(Acos)

		//////////////////////////////////////////////////
		//
		//	Asin
		//
		//////////////////////////////////////////////////

		inline float Asin(const float x) noexcept
		{
			return std::asin(x);
		}

		inline double Asin(const double x) noexcept
		{
			return std::asin(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Asin(const Arithmetic x) noexcept
		{
			return std::asin(x);
		}

		SIV3D_MATH_FUNCTION_X(Asin)

		//////////////////////////////////////////////////
		//
		//	Atan
		//
		//////////////////////////////////////////////////

		inline float Atan(const float x) noexcept
		{
			return std::atan(x);
		}

		inline double Atan(const double x) noexcept
		{
			return std::atan(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Atan(const Arithmetic x) noexcept
		{
			return std::atan(x);
		}

		SIV3D_MATH_FUNCTION_X(Atan)

		//////////////////////////////////////////////////
		//
		//	Atan2
		//
		//////////////////////////////////////////////////

		inline float Atan2(const float y, const float x) noexcept
		{
			return std::atan2(y, x);
		}

		inline double Atan2(const double y, const double x) noexcept
		{
			return std::atan2(y, x);
		}

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T1>, std::is_arithmetic<T2>>>*>
		inline auto Atan2(const T1 y, const T2 x) noexcept
		{
			return std::atan2(y, x);
		}

		SIV3D_MATH_FUNCTION_XY(Atan2)

		//////////////////////////////////////////////////
		//
		//	Cos
		//
		//////////////////////////////////////////////////

		inline float Cos(const float x) noexcept
		{
			return std::cos(x);
		}

		inline double Cos(const double x) noexcept
		{
			return std::cos(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Cos(const Arithmetic x) noexcept
		{
			return std::cos(x);
		}

		SIV3D_MATH_FUNCTION_X(Cos)

		//////////////////////////////////////////////////
		//
		//	Cosh
		//
		//////////////////////////////////////////////////

		inline float Cosh(const float x) noexcept
		{
			return std::cosh(x);
		}

		inline double Cosh(const double x) noexcept
		{
			return std::cosh(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Cosh(const Arithmetic x) noexcept
		{
			return std::cosh(x);
		}

		SIV3D_MATH_FUNCTION_X(Cosh)

		//////////////////////////////////////////////////
		//
		//	Sin
		//
		//////////////////////////////////////////////////

		inline float Sin(const float x) noexcept
		{
			return std::sin(x);
		}

		inline double Sin(const double x) noexcept
		{
			return std::sin(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Sin(const Arithmetic x) noexcept
		{
			return std::sin(x);
		}

		SIV3D_MATH_FUNCTION_X(Sin)

		//////////////////////////////////////////////////
		//
		//	Sinh
		//
		//////////////////////////////////////////////////

		inline float Sinh(const float x) noexcept
		{
			return std::sinh(x);
		}

		inline double Sinh(const double x) noexcept
		{
			return std::sinh(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Sinh(const Arithmetic x) noexcept
		{
			return std::sinh(x);
		}

		SIV3D_MATH_FUNCTION_X(Sinh)

		//////////////////////////////////////////////////
		//
		//	Tan
		//
		//////////////////////////////////////////////////

		inline float Tan(const float x) noexcept
		{
			return std::tan(x);
		}

		inline double Tan(const double x) noexcept
		{
			return std::tan(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Tan(const Arithmetic x) noexcept
		{
			return std::tan(x);
		}

		SIV3D_MATH_FUNCTION_X(Tan)

		//////////////////////////////////////////////////
		//
		//	Tanh
		//
		//////////////////////////////////////////////////

		inline float Tanh(const float x) noexcept
		{
			return std::tanh(x);
		}

		inline double Tanh(const double x) noexcept
		{
			return std::tanh(x);
		}

		SIV3D_CONCEPT_ARITHMETIC_
		inline double Tanh(const Arithmetic x) noexcept
		{
			return std::tanh(x);
		}

		SIV3D_MATH_FUNCTION_X(Tanh)

		//////////////////////////////////////////////////
		//
		//	Dot
		//
		//////////////////////////////////////////////////

		inline constexpr float Dot(const Float2 v1, const Float2 v2) noexcept
		{
			return v1.dot(v2);
		}

		inline constexpr double Dot(const Float2 v1, const Vec2 v2) noexcept
		{
			return Vec2{ v1 }.dot(v2);
		}

		inline constexpr double Dot(const Vec2 v1, const Float2 v2) noexcept
		{
			return v1.dot(Vec2{ v2 });
		}

		inline constexpr double Dot(const Vec2 v1, const Vec2 v2) noexcept
		{
			return v1.dot(v2);
		}

		inline constexpr float Dot(const Float3 v1, const Float3 v2) noexcept
		{
			return v1.dot(v2);
		}

		inline constexpr double Dot(const Float3 v1, const Vec3 v2) noexcept
		{
			return Vec3{ v1 }.dot(v2);
		}

		inline constexpr double Dot(const Vec3 v1, const Float3 v2) noexcept
		{
			return v1.dot(Vec3{ v2 });
		}

		inline constexpr double Dot(const Vec3 v1, const Vec3 v2) noexcept
		{
			return v1.dot(v2);
		}

		inline constexpr float Dot(const Float4 v1, const Float4 v2) noexcept
		{
			return v1.dot(v2);
		}

		inline constexpr double Dot(const Float4 v1, const Vec4 v2) noexcept
		{
			return Vec4{ v1 }.dot(v2);
		}

		inline constexpr double Dot(const Vec4 v1, const Float4 v2) noexcept
		{
			return v1.dot(Vec4{ v2 });
		}

		inline constexpr double Dot(const Vec4 v1, const Vec4 v2) noexcept
		{
			return v1.dot(v2);
		}

		//////////////////////////////////////////////////
		//
		//	Cross
		//
		//////////////////////////////////////////////////

		inline constexpr float Cross(const Float2 v1, const Float2 v2) noexcept
		{
			return v1.cross(v2);
		}

		inline constexpr double Cross(const Float2 v1, const Vec2 v2) noexcept
		{
			return Vec2{ v1 }.cross(v2);
		}

		inline constexpr double Cross(const Vec2 v1, const Float2 v2) noexcept
		{
			return v1.cross(Vec2{ v2 });
		}

		inline constexpr double Cross(const Vec2 v1, const Vec2 v2) noexcept
		{
			return v1.cross(v2);
		}

		inline constexpr Float3 Cross(const Float3 v1, const Float3 v2) noexcept
		{
			return v1.cross(v2);
		}

		inline constexpr Vec3 Cross(const Float3 v1, const Vec3 v2) noexcept
		{
			return Vec3{ v1 }.cross(v2);
		}

		inline constexpr Vec3 Cross(const Vec3 v1, const Float3 v2) noexcept
		{
			return v1.cross(Vec3{ v2 });
		}

		inline constexpr Vec3 Cross(const Vec3 v1, const Vec3 v2) noexcept
		{
			return v1.cross(v2);
		}

		//////////////////////////////////////////////////
		//
		//	Normalize
		//
		//////////////////////////////////////////////////

		inline constexpr float Normalize(const float x) noexcept
		{
			if (x == 0.0f)
			{
				return 0.0f;
			}

			return 1.0f;
		}

		inline constexpr double Normalize(const double x) noexcept
		{
			if (x == 0.0)
			{
				return 0.0;
			}

			return 1.0;
		}

		inline Vec2 Normalize(const Point v) noexcept
		{
			return Vec2{ v }.normalized();
		}

		inline Float2 Normalize(const Float2 v) noexcept
		{
			return v.normalized();
		}

		inline Float3 Normalize(const Float3 v) noexcept
		{
			return v.normalized();
		}

		inline Float4 Normalize(const Float4 v) noexcept
		{
			return v.normalized();
		}

		inline Vec2 Normalize(const Vec2 v) noexcept
		{
			return v.normalized();
		}

		inline Vec3 Normalize(const Vec3 v) noexcept
		{
			return v.normalized();
		}

		inline Vec4 Normalize(const Vec4 v) noexcept
		{
			return v.normalized();
		}

		//////////////////////////////////////////////////
		//
		//	Smoothstep
		//
		//////////////////////////////////////////////////

		inline constexpr float Smoothstep(const float min, const float max, float x) noexcept
		{
			if (x <= min)
			{
				return 0.0f;
			}
			else if (max <= x)
			{
				return 1.0f;
			}

			x = ((x - min) / (max - min));

			return (x * x * (3.0f - 2.0f * x));
		}

		inline constexpr double Smoothstep(const double min, const double max, double x) noexcept
		{
			if (x <= min)
			{
				return 0.0;
			}
			else if (max <= x)
			{
				return 1.0;
			}

			x = ((x - min) / (max - min));

			return (x * x * (3.0 - 2.0 * x));
		}

		inline constexpr float Smoothstep(const float x) noexcept
		{
			if (x <= 0.0f)
			{
				return 0.0f;
			}
			else if (1.0f <= x)
			{
				return 1.0f;
			}

			return (x * x * (3.0f - 2.0f * x));
		}

		inline constexpr double Smoothstep(const double x) noexcept
		{
			if (x <= 0.0)
			{
				return 0.0;
			}
			else if (1.0 <= x)
			{
				return 1.0;
			}

			return (x * x * (3.0 - 2.0 * x));
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(Smoothstep)

		//////////////////////////////////////////////////
		//
		//	GCD
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_integral<T1>, std::is_integral<T2>>>*>
		inline constexpr auto GCD(const T1 x, const T2 y) noexcept
		{
			return std::gcd(x, y);
		}

		//////////////////////////////////////////////////
		//
		//	LCM
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_integral<T1>, std::is_integral<T2>>>*>
		inline constexpr auto LCM(const T1 x, const T2 y) noexcept
		{
			return std::lcm(x, y);
		}
	}
}

# undef SIV3D_MATH_FUNCTION_X
# undef SIV3D_MATH_FUNCTION_CONSTEXPR_X
# undef SIV3D_MATH_FUNCTION_XY
# undef SIV3D_MATH_FUNCTION_CONSTEXPR_XY
# undef SIV3D_MATH_FUNCTION_XYREF
