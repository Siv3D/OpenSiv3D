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
# include <cfloat>
# include <emmintrin.h>
# include "PointVector.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr __m128d cV0{ 0.0, 0.0 };
		constexpr __m128d cV0_5{ 0.5, 0.5 };
		constexpr __m128d cV1{ 1.0, 1.0 };
		constexpr __m128d cV3{ 3.0, 3.0 };
	}

	namespace Math
	{
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
		inline Float3 Fmod(const Float3& v1, const Float3& v2)
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
		inline Vec2 Fmod(const Vec2& v1, const Vec2& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
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
		inline Float3 Fraction(const Float3& v)
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
		inline Vec2 Fraction(const Vec2& v)
		{
			return{ Fraction(v.x), Fraction(v.y) };
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
		inline Vec4 Fraction(const Vec4& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z), Fraction(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline float Frexp(float x, float& exp)
		{
			int32 e;
			const auto t = std::frexp(x, &e);
			exp = static_cast<float>(e);
			return t;
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline double Frexp(double x, double& exp)
		{
			int32 e;
			const auto t = std::frexp(x, &e);
			exp = e;
			return t;
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>* = nullptr>
		inline double Frexp(T x, U& exp)
		{
			int32 e;
			const auto t = std::frexp(static_cast<double>(x), &e);
			exp = static_cast<double>(e);
			return t;
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline Float2 Frexp(const Float2& x, Float2& exp)
		{
			int32 ex, ey;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			exp.set(static_cast<float>(ex), static_cast<float>(ey));
			return{ tx, ty };
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline Float3 Frexp(const Float3& x, Float3& exp)
		{
			int32 ex, ey, ez;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			exp.set(static_cast<float>(ex), static_cast<float>(ey), static_cast<float>(ez));
			return{ tx, ty, tz };
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline Float4 Frexp(const Float4& x, Float4& exp)
		{
			int32 ex, ey, ez, ew;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			const auto tw = std::frexp(x.w, &ew);
			exp.set(static_cast<float>(ex), static_cast<float>(ey), static_cast<float>(ez), static_cast<float>(ew));
			return{ tx, ty, tz, tw };
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline Vec2 Frexp(const Vec2& x, Vec2& exp)
		{
			int32 ex, ey;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			exp.set(ex, ey);
			return{ tx, ty };
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline Vec3 Frexp(const Vec3& x, Vec3& exp)
		{
			int32 ex, ey, ez;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			exp.set(ex, ey, ez);
			return{ tx, ty, tz };
		}

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		inline Vec4 Frexp(const Vec4& x, Vec4& exp)
		{
			int32 ex, ey, ez, ew;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			const auto tw = std::frexp(x.w, &ew);
			exp.set(ex, ey, ez, ew);
			return{ tx, ty, tz, tw };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline float Ldexp(float x, float exp)
		{
			return x * std::pow(2.0f, exp);
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline double Ldexp(double x, double exp)
		{
			return x * std::pow(2.0, exp);
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline Float2 Ldexp(const Float2& x, const Float2& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline Float3 Ldexp(const Float3& x, const Float3& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline Float4 Ldexp(const Float4& x, const Float4& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z), Ldexp(x.w, exp.w) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline Vec2 Ldexp(const Vec2& x, const Vec2& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline Vec3 Ldexp(const Vec3& x, const Vec3& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline Vec4 Ldexp(const Vec4& x, const Vec4& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z), Ldexp(x.w, exp.w) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		template <class T, class U, class R = CommonVector_t<T, U>>
		inline R Ldexp(T x, U y)
		{
			return Ldexp(static_cast<R>(x), static_cast<R>(y));
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline float Log(float x)
		{
			return std::log(x);
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline double Log(double x)
		{
			return std::log(x);
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline double Log(Type x)
		{
			return Log(static_cast<double>(x));
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline Vec2 Log(const Point& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline Float2 Log(const Float2& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline Float3 Log(const Float3& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline Float4 Log(const Float4& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z), Log(v.w) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline Vec2 Log(const Vec2& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline Vec3 Log(const Vec3& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline Vec4 Log(const Vec4& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z), Log(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline float Log2(float x)
		{
			return std::log2(x);
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline double Log2(double x)
		{
			return std::log2(x);
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline double Log2(Type x)
		{
			return Log2(static_cast<double>(x));
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline Vec2 Log2(const Point& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline Float2 Log2(const Float2& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline Float3 Log2(const Float3& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline Float4 Log2(const Float4& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z), Log2(v.w) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline Vec2 Log2(const Vec2& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline Vec3 Log2(const Vec3& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline Vec4 Log2(const Vec4& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z), Log2(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline float Log10(float x)
		{
			return std::log10(x);
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline double Log10(double x)
		{
			return std::log10(x);
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline double Log10(Type x)
		{
			return Log10(static_cast<double>(x));
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline Vec2 Log10(const Point& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline Float2 Log10(const Float2& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline Float3 Log10(const Float3& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline Float4 Log10(const Float4& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z), Log10(v.w) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline Vec2 Log10(const Vec2& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline Vec3 Log10(const Vec3& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline Vec4 Log10(const Vec4& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z), Log10(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline float Modf(float x, float& i)
		{
			return std::modf(x, &i);
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline double Modf(double x, double& i)
		{
			return std::modf(x, &i);
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline double Modf(Type x, double& i)
		{
			return Modf(static_cast<double>(x), i);
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline Float2 Modf(const Float2& x, Float2& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y) };
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline Float3 Modf(const Float3& x, Float3& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z) };
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline Float4 Modf(const Float4& x, Float4& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z), Modf(x.w, i.w) };
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline Vec2 Modf(const Vec2& x, Vec2& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y) };
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline Vec3 Modf(const Vec3& x, Vec3& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z) };
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline Vec4 Modf(const Vec4& x, Vec4& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z), Modf(x.w, i.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>* = nullptr>
		inline auto Pow(T x, U y)
		{
			return std::pow(x, y);
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic<U>::value>* = nullptr>
		inline Vector2D<T> Pow(const Vector2D<T>& x, U y)
		{
			return{ Pow(x.x, y), Pow(x.y, y) };
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic<U>::value>* = nullptr>
		inline Vector3D<T> Pow(const Vector3D<T>& x, U y)
		{
			return{ Pow(x.x, y), Pow(x.y, y), Pow(x.z, y) };
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic<U>::value>* = nullptr>
		inline Vector4D<T> Pow(const Vector4D<T>& x, U y)
		{
			return{ Pow(x.x, y), Pow(x.y, y), Pow(x.z, y), Pow(x.w, y) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr float Sign(float x) noexcept
		{
			return x < 0.0f ? -1.0f : x > 0.0f ? 1.0f : 0.0f;
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr double Sign(double x) noexcept
		{
			return x < 0.0 ? -1.0 : x > 0.0 ? 1.0 : 0.0;
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline constexpr double Sign(Type x) noexcept
		{
			return Sign(static_cast<double>(x));
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr Vec2 Sign(const Point& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr Float2 Sign(const Float2& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr Float3 Sign(const Float3& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr Float4 Sign(const Float4& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr Vec2 Sign(const Vec2& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr Vec3 Sign(const Vec3& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr Vec4 Sign(const Vec4& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr float Radians(float x) noexcept
		{
			return x * (PiF / 180.0f);
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr double Radians(double x) noexcept
		{
			return x * (Pi / 180.0);
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline constexpr double Radians(Type x) noexcept
		{
			return Radians(static_cast<double>(x));
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr Vec2 Radians(const Point& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr Float2 Radians(const Float2& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr Float3 Radians(const Float3& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr Float4 Radians(const Float4& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z), Radians(v.w) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr Vec2 Radians(const Vec2& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr Vec3 Radians(const Vec3& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr Vec4 Radians(const Vec4& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z), Radians(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr float Degrees(float x) noexcept
		{
			return x * (180.0f / PiF);
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr double Degrees(double x) noexcept
		{
			return x * (180.0 / Pi);
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline constexpr double Degrees(Type x) noexcept
		{
			return Degrees(static_cast<double>(x));
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr Vec2 Degrees(const Point& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr Float2 Degrees(const Float2& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr Float3 Degrees(const Float3& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr Float4 Degrees(const Float4& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z), Degrees(v.w) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr Vec2 Degrees(const Vec2& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr Vec3 Degrees(const Vec3& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr Vec4 Degrees(const Vec4& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z), Degrees(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr float Abs(float x) noexcept
		{
			return x >= 0.0f ? x : -x;
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr double Abs(double x) noexcept
		{
			return x >= 0.0 ? x : -x;
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_signed<Type>::value>* = nullptr>
		inline constexpr Type Abs(Type x) noexcept
		{
			return x >= Type(0) ? x : -x;
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr Vec2 Abs(const Point& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr Float2 Abs(const Float2& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr Float3 Abs(const Float3& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr Float4 Abs(const Float4& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr Vec2 Abs(const Vec2& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr Vec3 Abs(const Vec3& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		inline constexpr Vec4 Abs(const Vec4& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		inline constexpr float Square(float x) noexcept
		{
			return x * x;
		}

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		inline constexpr double Square(double x) noexcept
		{
			return x * x;
		}

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline constexpr double Square(Type x) noexcept
		{
			return Square(static_cast<double>(x));
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline float Exp(float x)
		{
			return std::exp(x);
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline double Exp(double x)
		{
			return std::exp(x);
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline double Exp(Type x)
		{
			return Exp(static_cast<double>(x));
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline Vec2 Exp(const Point& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline Float2 Exp(const Float2& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline Float3 Exp(const Float3& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline Float4 Exp(const Float4& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z), Exp(v.w) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline Vec2 Exp(const Vec2& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline Vec3 Exp(const Vec3& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline Vec4 Exp(const Vec4& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z), Exp(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline float Exp2(float x)
		{
			return std::exp2(x);
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline double Exp2(double x)
		{
			return std::exp2(x);
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
		inline double Exp2(Type x)
		{
			return Exp2(static_cast<double>(x));
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline Vec2 Exp2(const Point& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline Float2 Exp2(const Float2& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline Float3 Exp2(const Float3& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline Float4 Exp2(const Float4& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z), Exp2(v.w) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline Vec2 Exp2(const Vec2& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline Vec3 Exp2(const Vec3& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline Vec4 Exp2(const Vec4& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z), Exp2(v.w) };
		}

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//





		// Rsqrt
		// Sqrt
		// Ceil
		// Floor
		// Clamp
		// Saturate
		// Acos
		// Asin
		// Atan
		// Atan2
		// Cos
		// Cosh
		// Sin
		// Sinh
		// Tan
		// Tanh
		// Normalize

		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline constexpr float Smoothstep(float min, float max, float x) noexcept
		{
			if (x <= min)
			{
				return 0.0f;
			}
			else if (max <= x)
			{
				return 1.0f;
			}

			x = (x - min) / (max - min);

			return x * x * (3.0f - 2.0f * x);
		}

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline constexpr double Smoothstep(double min, double max, double x) noexcept
		{
			if (x <= min)
			{
				return 0.0;
			}
			else if (max <= x)
			{
				return 1.0;
			}

			x = (x - min) / (max - min);

			return x * x * (3.0 - 2.0 * x);
		}

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline constexpr float Smoothstep(float x) noexcept
		{
			if (x <= 0.0f)
			{
				return 0.0f;
			}
			else if (1.0f <= x)
			{
				return 1.0f;
			}

			return x * x * (3.0f - 2.0f * x);
		}

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline constexpr double Smoothstep(double x) noexcept
		{
			if (x <= 0.0)
			{
				return 0.0;
			}
			else if (1.0 <= x)
			{
				return 1.0;
			}

			return x * x * (3.0 - 2.0 * x);
		}
	}
}
