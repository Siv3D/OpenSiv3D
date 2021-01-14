//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

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
}																						\
template <class T, class U, class R>													\
inline R FUNC(const T x, const U y) noexcept											\
{																						\
	return FUNC(static_cast<R>(x), static_cast<R>(y));									\
}

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

# define SIV3D_MATH_FUNCTION_CX(FUNC)							\
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

namespace s3d
{
	namespace Math
	{
		inline float Fmod(const float x, const float y) noexcept
		{
			return std::fmod(x, y);
		}

		inline double Fmod(const double x, const double y) noexcept
		{
			return std::fmod(x, y);
		}

		SIV3D_MATH_FUNCTION_XY(Fmod)


		inline float Fraction(const float x) noexcept
		{
			return (x - std::floor(x));
		}

		inline double Fraction(const double x) noexcept
		{
			return (x - std::floor(x));
		}

		SIV3D_MATH_FUNCTION_X(Fraction)



		inline float Exp(const float x) noexcept
		{
			return std::exp(x);
		}

		inline double Exp(const double x) noexcept
		{
			return std::exp(x);
		}

		SIV3D_MATH_FUNCTION_X(Exp)




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

		SIV3D_MATH_FUNCTION_CX(Square)











		inline constexpr float Saturate(const float x) noexcept
		{
			return Clamp(x, 0.0f, 1.0f);
		}

		inline constexpr double Saturate(const double x) noexcept
		{
			return Clamp(x, 0.0, 1.0);
		}

		SIV3D_MATH_FUNCTION_CONSTEXPR_X(Saturate)
	}
}

# undef SIV3D_MATH_FUNCTION_XYA
