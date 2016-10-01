//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cfloat>
# include <emmintrin.h>
# include "PointVector.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	namespace Math
	{
		namespace detail
		{
			constexpr double cRadians = Math::TwoPi / 360.0;
			constexpr double cDegrees = 360.0 / Math::TwoPi;
			constexpr __m128d cV0{ 0.0, 0.0 };
			constexpr __m128d cV0_5{ 0.5, 0.5 };
			constexpr __m128d cV1{ 1.0, 1.0 };
			constexpr __m128d cV3{ 3.0, 3.0 };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline float Fmod(float x, float y)
		{
			return std::fmod(x, y);
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline double Fmod(double x, double y)
		{
			return std::fmod(x, y);
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline Float2 Fmod(const Float2& v1, const Float2& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline Vec2 Fmod(const Vec2& v1, const Vec2& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline Float3 Fmod(const Float3& v1, const Float3& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline Vec3 Fmod(const Vec3& v1, const Vec3& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline Float4 Fmod(const Float4& v1, const Float4& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z), Fmod(v1.w, v2.w) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline Vec4 Fmod(const Vec4& v1, const Vec4& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z), Fmod(v1.w, v2.w) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		template <class T, class U, class R = CommonVector_t<T, U>>
		inline R Fmod(T x, U y)
		{
			return Fmod(static_cast<R>(x), static_cast<R>(y));
		}
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline float Fraction(float x)
		{
			return (x - std::floor(x));
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline double Fraction(double x)
		{
			return (x - std::floor(x));
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline double Fraction(Type x)
		{
			return Fraction(static_cast<double>(x));
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline constexpr Point Fraction(const Point&)
		{
			return{ 0, 0 };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline Float2 Fraction(const Float2& v)
		{
			return{ Fraction(v.x), Fraction(v.y) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline Vec2 Fraction(const Vec2& v)
		{
			return{ Fraction(v.x), Fraction(v.y) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline Float3 Fraction(const Float3& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline Vec3 Fraction(const Vec3& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline Float4 Fraction(const Float4& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z), Fraction(v.w) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline Vec4 Fraction(const Vec4& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z), Fraction(v.w) };
		}
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//




		///// <summary>
		///// 剰余を計算します。
		///// </summary>
		//inline float Fmod(float x, float y)
		//{
		//	return std::fmod(x, y);
		//}

		///// <summary>
		///// 剰余を計算します。
		///// </summary>
		//inline double Fmod(double x, double y)
		//{
		//	return std::fmod(x, y);
		//}

		///// <summary>
		///// 剰余を計算します。
		///// </summary>
		//inline Float2 Fmod(const Float2& v1, const Float2& v2)
		//{
		//	return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		//}

		///// <summary>
		///// 剰余を計算します。
		///// </summary>
		//inline Vec2 Fmod(const Vec2& v1, const Vec2& v2)
		//{
		//	return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		//}
	}
}
