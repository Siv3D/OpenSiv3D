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
# include <cmath>
# include "Common.hpp"
# include "PointVector.hpp"

namespace s3d
{
	namespace Math
	{
		//////////////////////////////////////////////////
		//
		//	Fmod
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Fmod(float x, float y) noexcept;

		[[nodiscard]]
		inline double Fmod(double x, double y) noexcept;

		[[nodiscard]]
		inline Float2 Fmod(Float2 v1, Float2 v2) noexcept;

		[[nodiscard]]
		inline Float3 Fmod(Float3 v1, Float3 v2) noexcept;

		[[nodiscard]]
		inline Float4 Fmod(Float4 v1, Float4 v2) noexcept;

		[[nodiscard]]
		inline Vec2 Fmod(Vec2 v1, Vec2 v2) noexcept;

		[[nodiscard]]
		inline Vec3 Fmod(Vec3 v1, Vec3 v2) noexcept;

		[[nodiscard]]
		inline Vec4 Fmod(Vec4 v1, Vec4 v2) noexcept;

		template <class T1, class T2, class R = CommonVector_t<T1, T2>>
		[[nodiscard]]
		inline R Fmod(T1 x, T2 y) noexcept;

		//////////////////////////////////////////////////
		//
		//	Fraction
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Fraction(float x) noexcept;

		[[nodiscard]]
		inline double Fraction(double x) noexcept;

		[[nodiscard]]
		inline Float2 Fraction(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Fraction(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Fraction(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Fraction(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Fraction(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Fraction(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Frexp
		//
		//////////////////////////////////////////////////

		inline float Frexp(float x, float& exp) noexcept;

		inline double Frexp(double x, double& exp) noexcept;

		inline Float2 Frexp(Float2 x, Float2& exp) noexcept;

		inline Float3 Frexp(Float3 x, Float3& exp) noexcept;

		inline Float4 Frexp(Float4 x, Float4& exp) noexcept;

		inline Vec2 Frexp(Vec2 x, Vec2& exp) noexcept;

		inline Vec3 Frexp(Vec3 x, Vec3& exp) noexcept;

		inline Vec4 Frexp(Vec4 x, Vec4& exp) noexcept;

		//////////////////////////////////////////////////
		//
		//	Ldexp
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Ldexp(float x, float y) noexcept;

		[[nodiscard]]
		inline double Ldexp(double x, double y) noexcept;

		[[nodiscard]]
		inline Float2 Ldexp(Float2 v1, Float2 v2) noexcept;

		[[nodiscard]]
		inline Float3 Ldexp(Float3 v1, Float3 v2) noexcept;

		[[nodiscard]]
		inline Float4 Ldexp(Float4 v1, Float4 v2) noexcept;

		[[nodiscard]]
		inline Vec2 Ldexp(Vec2 v1, Vec2 v2) noexcept;

		[[nodiscard]]
		inline Vec3 Ldexp(Vec3 v1, Vec3 v2) noexcept;

		[[nodiscard]]
		inline Vec4 Ldexp(Vec4 v1, Vec4 v2) noexcept;

		//////////////////////////////////////////////////
		//
		//	Log
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Log(float x) noexcept;

		[[nodiscard]]
		inline double Log(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Log(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Log(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Log(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Log(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Log(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Log(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Log(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Log2
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Log2(float x) noexcept;

		[[nodiscard]]
		inline double Log2(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Log2(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Log2(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Log2(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Log2(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Log2(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Log2(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Log2(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Log10
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Log10(float x) noexcept;

		[[nodiscard]]
		inline double Log10(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Log10(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Log10(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Log10(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Log10(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Log10(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Log10(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Log10(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Modf
		//
		//////////////////////////////////////////////////

		inline float Modf(float x, float& exp) noexcept;

		inline double Modf(double x, double& exp) noexcept;

		inline Float2 Modf(Float2 x, Float2& exp) noexcept;

		inline Float3 Modf(Float3 x, Float3& exp) noexcept;

		inline Float4 Modf(Float4 x, Float4& exp) noexcept;

		inline Vec2 Modf(Vec2 x, Vec2& exp) noexcept;

		inline Vec3 Modf(Vec3 x, Vec3& exp) noexcept;

		inline Vec4 Modf(Vec4 x, Vec4& exp) noexcept;

		//////////////////////////////////////////////////
		//
		//	Pow
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T1>, std::is_arithmetic<T2>>>* = nullptr>
		[[nodiscard]]
		inline auto Pow(T1 x, T2 y) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline Float2 Pow(Float2 x, Arithmetic y) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline Float3 Pow(Float3 x, Arithmetic y) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline Float4 Pow(Float4 x, Arithmetic y) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline Vec2 Pow(Vec2 x, Arithmetic y) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline Vec3 Pow(Vec3 x, Arithmetic y) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline Vec4 Pow(Vec4 x, Arithmetic y) noexcept;

		//////////////////////////////////////////////////
		//
		//	Sign
		//
		//////////////////////////////////////////////////

		SIV3D_CONCEPT_ARITHMETIC
		inline constexpr int32 Sign(Arithmetic x) noexcept;

		[[nodiscard]]
		inline constexpr Float2 Sign(Float2 v) noexcept;

		[[nodiscard]]
		inline constexpr Float3 Sign(Float3 v) noexcept;

		[[nodiscard]]
		inline constexpr Float4 Sign(Float4 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 Sign(Vec2 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Sign(Vec3 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 Sign(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	ToRadians
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float ToRadians(float x) noexcept;

		[[nodiscard]]
		inline constexpr double ToRadians(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline constexpr double ToRadians(Arithmetic x) noexcept;

		[[nodiscard]]
		inline constexpr Float2 ToRadians(Float2 v) noexcept;

		[[nodiscard]]
		inline constexpr Float3 ToRadians(Float3 v) noexcept;

		[[nodiscard]]
		inline constexpr Float4 ToRadians(Float4 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 ToRadians(Vec2 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 ToRadians(Vec3 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 ToRadians(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	ToDegrees
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float ToDegrees(float x) noexcept;

		[[nodiscard]]
		inline constexpr double ToDegrees(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline constexpr double ToDegrees(Arithmetic x) noexcept;

		[[nodiscard]]
		inline constexpr Float2 ToDegrees(Float2 v) noexcept;

		[[nodiscard]]
		inline constexpr Float3 ToDegrees(Float3 v) noexcept;

		[[nodiscard]]
		inline constexpr Float4 ToDegrees(Float4 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 ToDegrees(Vec2 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 ToDegrees(Vec3 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 ToDegrees(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Abs
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Abs(float x) noexcept;

		[[nodiscard]]
		inline constexpr double Abs(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline constexpr Arithmetic Abs(Arithmetic x) noexcept;

		[[nodiscard]]
		inline constexpr Float2 Abs(Float2 v) noexcept;

		[[nodiscard]]
		inline constexpr Float3 Abs(Float3 v) noexcept;

		[[nodiscard]]
		inline constexpr Float4 Abs(Float4 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 Abs(Vec2 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Abs(Vec3 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 Abs(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	AbsDiff
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T1>, std::is_arithmetic<T2>>>* = nullptr>
		[[nodiscard]]
		inline constexpr auto AbsDiff(T1 x, T2 y) noexcept;

		[[nodiscard]]
		inline constexpr Float2 AbsDiff(Float2 v1, Float2 v2) noexcept;

		[[nodiscard]]
		inline constexpr Float3 AbsDiff(Float3 v1, Float3 v2) noexcept;

		[[nodiscard]]
		inline constexpr Float4 AbsDiff(Float4 v1, Float4 v2) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 AbsDiff(Vec2 v1, Vec2 v2) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 AbsDiff(Vec3 v1, Vec3 v2) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 AbsDiff(Vec4 v1, Vec4 v2) noexcept;

		//////////////////////////////////////////////////
		//
		//	Square
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Square(float x) noexcept;

		[[nodiscard]]
		inline constexpr double Square(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline constexpr Arithmetic Square(Arithmetic x) noexcept;

		[[nodiscard]]
		inline constexpr Float2 Square(Float2 v) noexcept;

		[[nodiscard]]
		inline constexpr Float3 Square(Float3 v) noexcept;

		[[nodiscard]]
		inline constexpr Float4 Square(Float4 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 Square(Vec2 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Square(Vec3 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 Square(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Exp
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Exp(float x) noexcept;

		[[nodiscard]]
		inline double Exp(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Exp(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Exp(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Exp(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Exp(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Exp(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Exp(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Exp(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Exp2
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Exp2(float x) noexcept;

		[[nodiscard]]
		inline double Exp2(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Exp2(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Exp2(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Exp2(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Exp2(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Exp2(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Exp2(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Exp2(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Rsqrt
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Rsqrt(float x) noexcept;

		[[nodiscard]]
		inline double Rsqrt(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Rsqrt(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Rsqrt(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Rsqrt(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Rsqrt(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Rsqrt(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Rsqrt(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Rsqrt(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Sqrt
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Sqrt(float x) noexcept;

		[[nodiscard]]
		inline double Sqrt(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Sqrt(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Sqrt(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Sqrt(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Sqrt(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Sqrt(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Sqrt(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Sqrt(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Ceil
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Ceil(float x) noexcept;

		[[nodiscard]]
		inline double Ceil(double x) noexcept;

		[[nodiscard]]
		inline Float2 Ceil(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Ceil(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Ceil(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Ceil(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Ceil(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Ceil(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Floor
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Floor(float x) noexcept;

		[[nodiscard]]
		inline double Floor(double x) noexcept;

		[[nodiscard]]
		inline Float2 Floor(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Floor(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Floor(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Floor(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Floor(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Floor(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Round
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Round(float x) noexcept;

		[[nodiscard]]
		inline double Round(double x) noexcept;

		[[nodiscard]]
		inline Float2 Round(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Round(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Round(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Round(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Round(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Round(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Clamp
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Clamp(float x, float min, float max) noexcept;

		[[nodiscard]]
		inline constexpr double Clamp(double x, double min, double max) noexcept;

		[[nodiscard]]
		inline constexpr Point Clamp(Point v, int32 min, int32 max) noexcept;

		[[nodiscard]]
		inline constexpr Float2 Clamp(Float2 v, float min, float max) noexcept;

		[[nodiscard]]
		inline constexpr Float3 Clamp(Float3 v, float min, float max) noexcept;

		[[nodiscard]]
		inline constexpr Float4 Clamp(Float4 v, float min, float max) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 Clamp(Vec2 v, double min, double max) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Clamp(Vec3 v, double min, double max) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 Clamp(Vec4 v, double min, double max) noexcept;

		//////////////////////////////////////////////////
		//
		//	Saturate
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Saturate(float x) noexcept;

		[[nodiscard]]
		inline constexpr double Saturate(double x) noexcept;

		[[nodiscard]]
		inline constexpr Float2 Saturate(Float2 v) noexcept;

		[[nodiscard]]
		inline constexpr Float3 Saturate(Float3 v) noexcept;

		[[nodiscard]]
		inline constexpr Float4 Saturate(Float4 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 Saturate(Vec2 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Saturate(Vec3 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 Saturate(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Acos
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Acos(float x) noexcept;

		[[nodiscard]]
		inline double Acos(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Acos(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Acos(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Acos(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Acos(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Acos(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Acos(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Acos(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Asin
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Asin(float x) noexcept;

		[[nodiscard]]
		inline double Asin(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Asin(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Asin(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Asin(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Asin(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Asin(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Asin(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Asin(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Atan
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Atan(float x) noexcept;

		[[nodiscard]]
		inline double Atan(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Atan(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Atan(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Atan(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Atan(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Atan(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Atan(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Atan(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Atan2
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Atan2(float y, float x) noexcept;

		[[nodiscard]]
		inline double Atan2(double y, double x) noexcept;

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_arithmetic<T1>, std::is_arithmetic<T2>>>* = nullptr>
		[[nodiscard]]
		inline auto Atan2(T1 y, T2 x) noexcept;

		[[nodiscard]]
		inline Float2 Atan2(Float2 y, Float2 x) noexcept;

		[[nodiscard]]
		inline Float3 Atan2(Float3 y, Float3 x) noexcept;

		[[nodiscard]]
		inline Float4 Atan2(Float4 y, Float4 x) noexcept;

		[[nodiscard]]
		inline Vec2 Atan2(Vec2 y, Vec2 x) noexcept;

		[[nodiscard]]
		inline Vec3 Atan2(Vec3 y, Vec3 x) noexcept;

		[[nodiscard]]
		inline Vec4 Atan2(Vec4 y, Vec4 x) noexcept;

		//////////////////////////////////////////////////
		//
		//	Cos
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Cos(float x) noexcept;

		[[nodiscard]]
		inline double Cos(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Cos(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Cos(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Cos(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Cos(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Cos(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Cos(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Cos(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Cosh
		//
		//////////////////////////////////////////////////
		
		[[nodiscard]]
		inline float Cosh(float x) noexcept;

		[[nodiscard]]
		inline double Cosh(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Cosh(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Cosh(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Cosh(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Cosh(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Cosh(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Cosh(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Cosh(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Sin
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Sin(float x) noexcept;

		[[nodiscard]]
		inline double Sin(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Sin(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Sin(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Sin(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Sin(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Sin(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Sin(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Sin(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Sinh
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Sinh(float x) noexcept;

		[[nodiscard]]
		inline double Sinh(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Sinh(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Sinh(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Sinh(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Sinh(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Sinh(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Sinh(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Sinh(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Tan
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Tan(float x) noexcept;

		[[nodiscard]]
		inline double Tan(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Tan(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Tan(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Tan(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Tan(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Tan(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Tan(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Tan(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Tanh
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline float Tanh(float x) noexcept;

		[[nodiscard]]
		inline double Tanh(double x) noexcept;

		SIV3D_CONCEPT_ARITHMETIC
		[[nodiscard]]
		inline double Tanh(Arithmetic x) noexcept;

		[[nodiscard]]
		inline Float2 Tanh(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Tanh(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Tanh(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Tanh(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Tanh(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Tanh(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Dot
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Dot(Float2 v1, Float2 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Float2 v1, Vec2 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Vec2 v1, Float2 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Vec2 v1, Vec2 v2) noexcept;

		[[nodiscard]]
		inline constexpr float Dot(Float3 v1, Float3 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Vec3 v1, Float3 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Float3 v1, Vec3 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Vec3 v1, Vec3 v2) noexcept;

		[[nodiscard]]
		inline constexpr float Dot(Float4 v1, Float4 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Vec4 v1, Float4 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Float4 v1, Vec4 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Dot(Vec4 v1, Vec4 v2) noexcept;

		//////////////////////////////////////////////////
		//
		//	Cross
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Cross(Float2 v1, Float2 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Cross(Float2 v1, Vec2 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Cross(Vec2 v1, Float2 v2) noexcept;

		[[nodiscard]]
		inline constexpr double Cross(Vec2 v1, Vec2 v2) noexcept;

		[[nodiscard]]
		inline constexpr Float3 Cross(Float3 v1, Float3 v2) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Cross(Float3 v1, Vec3 v2) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Cross(Vec3 v1, Float3 v2) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Cross(Vec3 v1, Vec3 v2) noexcept;

		//////////////////////////////////////////////////
		//
		//	Normalize
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Normalize(float x) noexcept;

		[[nodiscard]]
		inline constexpr double Normalize(double x) noexcept;

		[[nodiscard]]
		inline Vec2 Normalize(Point v) noexcept;

		[[nodiscard]]
		inline Float2 Normalize(Float2 v) noexcept;

		[[nodiscard]]
		inline Float3 Normalize(Float3 v) noexcept;

		[[nodiscard]]
		inline Float4 Normalize(Float4 v) noexcept;

		[[nodiscard]]
		inline Vec2 Normalize(Vec2 v) noexcept;

		[[nodiscard]]
		inline Vec3 Normalize(Vec3 v) noexcept;

		[[nodiscard]]
		inline Vec4 Normalize(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	Smoothstep
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		inline constexpr float Smoothstep(float min, float max, float x) noexcept;

		[[nodiscard]]
		inline constexpr double Smoothstep(double min, double max, double x) noexcept;

		[[nodiscard]]
		inline constexpr float Smoothstep(float x) noexcept;

		[[nodiscard]]
		inline constexpr double Smoothstep(double x) noexcept;

		[[nodiscard]]
		inline constexpr Float2 Smoothstep(Float2 v) noexcept;

		[[nodiscard]]
		inline constexpr Float3 Smoothstep(Float3 v) noexcept;

		[[nodiscard]]
		inline constexpr Float4 Smoothstep(Float4 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec2 Smoothstep(Vec2 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec3 Smoothstep(Vec3 v) noexcept;

		[[nodiscard]]
		inline constexpr Vec4 Smoothstep(Vec4 v) noexcept;

		//////////////////////////////////////////////////
		//
		//	GCD
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_integral<T1>, std::is_integral<T2>>>* = nullptr>
		[[nodiscard]]
		inline constexpr auto GCD(T1 x, T2 y) noexcept;

		//////////////////////////////////////////////////
		//
		//	LCM
		//
		//////////////////////////////////////////////////

		template <class T1, class T2, std::enable_if_t<std::conjunction_v<std::is_integral<T1>, std::is_integral<T2>>>* = nullptr>
		[[nodiscard]]
		inline constexpr auto LCM(T1 x, T2 y) noexcept;
	}
}

# include "detail/Math.ipp"
# include "detail/Math_Functors.ipp"
