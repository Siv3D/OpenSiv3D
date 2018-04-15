//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cfloat>
# include <emmintrin.h>
# include "Utility.hpp"
# include "BigFloat.hpp"
# include "PointVector.hpp"
# include "MathConstants.hpp"

namespace s3d
{
//////////////////////////////////////////////////
//
//	Fmod
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline float Fmod(float x, float y)
		{
			return std::fmod(x, y);
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline double Fmod(double x, double y)
		{
			return std::fmod(x, y);
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Fmod(const Float2& v1, const Float2& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Fmod(const Float3& v1, const Float3& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Fmod(const Float4& v1, const Float4& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z), Fmod(v1.w, v2.w) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Fmod(const Vec2& v1, const Vec2& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Fmod(const Vec3& v1, const Vec3& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Fmod(const Vec4& v1, const Vec4& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z), Fmod(v1.w, v2.w) };
		}

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		template <class T, class U, class R = CommonVector_t<T, U>>
		[[nodiscard]] inline R Fmod(T x, U y)
		{
			return Fmod(static_cast<R>(x), static_cast<R>(y));
		}
	}

	namespace detail
	{
		template <class TypeY>
		struct FmodX_impl
		{
			const TypeY& y;

			constexpr FmodX_impl(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			[[nodiscard]] constexpr auto operator()(const TypeX& x) const
			{
				return Math::Fmod(x, y);
			}
		};

		template <class TypeX>
		struct FmodY_impl
		{
			const TypeX& x;

			constexpr FmodY_impl(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			[[nodiscard]] constexpr auto operator()(const TypeY& y) const
			{
				return Math::Fmod(x, y);
			}
		};

		struct Fmod_impl
		{
			template <class TypeX, class TypeY>
			constexpr auto operator() (const TypeX& x, const TypeY& y) const
			{
				return Math::Fmod(x, y);
			}
		};
	}

	[[nodiscard]] inline constexpr auto Fmod() noexcept
	{
		return detail::Fmod_impl();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Fmod(const TypeX& x) noexcept
	{
		return detail::FmodY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Fmod(const TypeX& x, const TypeY& y) noexcept
	{
		return detail::Fmod_impl()(x, y);
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Fmod(PlaceHolder_t, const TypeY& y) noexcept
	{
		return detail::FmodX_impl<TypeY>(y);
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Fmod(const TypeX& x, PlaceHolder_t) noexcept
	{
		return detail::FmodY_impl<TypeX>(x);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Fmod(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Fmod_impl();
	}

//////////////////////////////////////////////////
//
//	Fraction
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline float Fraction(float x)
		{
			return (x - std::floor(x));
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline double Fraction(double x)
		{
			return (x - std::floor(x));
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Fraction(Type x)
		{
			return Fraction(static_cast<double>(x));
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Point Fraction(const Point&)
		{
			return{ 0, 0 };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline Float2 Fraction(const Float2& v)
		{
			return{ Fraction(v.x), Fraction(v.y) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline Float3 Fraction(const Float3& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline Float4 Fraction(const Float4& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z), Fraction(v.w) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Fraction(const Vec2& v)
		{
			return{ Fraction(v.x), Fraction(v.y) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline Vec3 Fraction(const Vec3& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z) };
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] inline Vec4 Fraction(const Vec4& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z), Fraction(v.w) };
		}
	}

	namespace detail
	{
		struct Fraction_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Fraction(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Fraction_impl();
			}
		};
	}

	constexpr auto Fraction = detail::Fraction_impl();

//////////////////////////////////////////////////
//
//	Frexp
//
//////////////////////////////////////////////////

	namespace Math
	{
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
		template <class T, class U, std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>>* = nullptr>
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
	}

//////////////////////////////////////////////////
//
//	Ldexp
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline float Ldexp(float x, float exp)
		{
			return x * std::pow(2.0f, exp);
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline double Ldexp(double x, double exp)
		{
			return x * std::pow(2.0, exp);
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Ldexp(const Float2& x, const Float2& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Ldexp(const Float3& x, const Float3& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Ldexp(const Float4& x, const Float4& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z), Ldexp(x.w, exp.w) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Ldexp(const Vec2& x, const Vec2& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Ldexp(const Vec3& x, const Vec3& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Ldexp(const Vec4& x, const Vec4& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z), Ldexp(x.w, exp.w) };
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		template <class T, class U, class R = CommonVector_t<T, U>>
		[[nodiscard]] inline R Ldexp(T x, U y)
		{
			return Ldexp(static_cast<R>(x), static_cast<R>(y));
		}
	}

//////////////////////////////////////////////////
//
//	Log
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline float Log(float x)
		{
			return std::log(x);
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline double Log(double x)
		{
			return std::log(x);
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Log(Type x)
		{
			return Log(static_cast<double>(x));
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Log(const Point& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Log(const Float2& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Log(const Float3& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Log(const Float4& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z), Log(v.w) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Log(const Vec2& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Log(const Vec3& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z) };
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Log(const Vec4& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z), Log(v.w) };
		}
	}

	namespace detail
	{
		struct Log_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Log(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Log_impl();
			}
		};
	}

	constexpr auto Log = detail::Log_impl();

//////////////////////////////////////////////////
//
//	Log2
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline float Log2(float x)
		{
			return std::log2(x);
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline double Log2(double x)
		{
			return std::log2(x);
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Log2(Type x)
		{
			return Log2(static_cast<double>(x));
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Log2(const Point& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Log2(const Float2& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Log2(const Float3& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Log2(const Float4& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z), Log2(v.w) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Log2(const Vec2& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Log2(const Vec3& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z) };
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Log2(const Vec4& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z), Log2(v.w) };
		}
	}

	namespace detail
	{
		struct Log2_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Log2(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Log2_impl();
			}
		};
	}

	constexpr auto Log2 = detail::Log2_impl();

//////////////////////////////////////////////////
//
//	Log10
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline float Log10(float x)
		{
			return std::log10(x);
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline double Log10(double x)
		{
			return std::log10(x);
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Log10(Type x)
		{
			return Log10(static_cast<double>(x));
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Log10(const Point& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Log10(const Float2& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Log10(const Float3& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Log10(const Float4& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z), Log10(v.w) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Log10(const Vec2& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Log10(const Vec3& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z) };
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Log10(const Vec4& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z), Log10(v.w) };
		}
	}

	namespace detail
	{
		struct Log10_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Log10(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Log10_impl();
			}
		};
	}

	constexpr auto Log10 = detail::Log10_impl();

//////////////////////////////////////////////////
//
//	Modf
//
//////////////////////////////////////////////////

	namespace Math
	{
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
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
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
	}

//////////////////////////////////////////////////
//
//	Pow
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>>* = nullptr>
		[[nodiscard]] inline auto Pow(T x, U y)
		{
			return std::pow(x, y);
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic_v<U>>* = nullptr>
		[[nodiscard]] inline Vector2D<T> Pow(const Vector2D<T>& x, U y)
		{
			return{ Pow(x.x, y), Pow(x.y, y) };
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic_v<U>>* = nullptr>
		[[nodiscard]] inline Vector3D<T> Pow(const Vector3D<T>& x, U y)
		{
			return{ Pow(x.x, y), Pow(x.y, y), Pow(x.z, y) };
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class T, class U, std::enable_if_t<std::is_arithmetic_v<U>>* = nullptr>
		[[nodiscard]] inline Vector4D<T> Pow(const Vector4D<T>& x, U y)
		{
			return{ Pow(x.x, y), Pow(x.y, y), Pow(x.z, y), Pow(x.w, y) };
		}
	}

	namespace detail
	{
		template <class TypeY>
		struct PowX_impl
		{
			const TypeY& y;

			constexpr PowX_impl(const TypeY& _y) noexcept
				: y(_y) {}

			template <class TypeX>
			[[nodiscard]] constexpr auto operator()(const TypeX& x) const
			{
				return Math::Pow(x, y);
			}
		};

		template <class TypeX>
		struct PowY_impl
		{
			const TypeX& x;

			constexpr PowY_impl(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			[[nodiscard]] constexpr auto operator()(const TypeY& y) const
			{
				return Math::Pow(x, y);
			}
		};

		struct Pow_impl
		{
			template <class TypeX, class TypeY>
			constexpr auto operator() (const TypeX& x, const TypeY& y) const
			{
				return Math::Pow(x, y);
			}
		};
	}

	[[nodiscard]] inline constexpr auto Pow() noexcept
	{
		return detail::Pow_impl();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Pow(const TypeX& x) noexcept
	{
		return detail::PowY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Pow(const TypeX& x, const TypeY& y) noexcept
	{
		return detail::Pow_impl()(x, y);
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Pow(PlaceHolder_t, const TypeY& y) noexcept
	{
		return detail::PowX_impl<TypeY>(y);
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Pow(const TypeX& x, PlaceHolder_t) noexcept
	{
		return detail::PowY_impl<TypeX>(x);
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Pow(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Pow_impl();
	}

//////////////////////////////////////////////////
//
//	Sign
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr float Sign(float x) noexcept
		{
			return x < 0.0f ? -1.0f : x > 0.0f ? 1.0f : 0.0f;
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr double Sign(double x) noexcept
		{
			return x < 0.0 ? -1.0 : x > 0.0 ? 1.0 : 0.0;
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr double Sign(Type x) noexcept
		{
			return Sign(static_cast<double>(x));
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Sign(const Point& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float2 Sign(const Float2& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float3 Sign(const Float3& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float4 Sign(const Float4& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Sign(const Vec2& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec3 Sign(const Vec3& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z) };
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec4 Sign(const Vec4& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w) };
		}
	}

	namespace detail
	{
		struct Sign_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Sign(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Sign_impl();
			}
		};
	}

	constexpr auto Sign = detail::Sign_impl();

//////////////////////////////////////////////////
//
//	Radians
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr float Radians(float x) noexcept
		{
			return x * (PiF / 180.0f);
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr double Radians(double x) noexcept
		{
			return x * (Pi / 180.0);
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr double Radians(Type x) noexcept
		{
			return Radians(static_cast<double>(x));
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Radians(const Point& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Float2 Radians(const Float2& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Float3 Radians(const Float3& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Float4 Radians(const Float4& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z), Radians(v.w) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Radians(const Vec2& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec3 Radians(const Vec3& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z) };
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec4 Radians(const Vec4& v) noexcept
		{
			return{ Radians(v.x), Radians(v.y), Radians(v.z), Radians(v.w) };
		}
	}

	namespace detail
	{
		struct Radians_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Radians(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Radians_impl();
			}
		};
	}

	constexpr auto Radians = detail::Radians_impl();

//////////////////////////////////////////////////
//
//	Degrees
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr float Degrees(float x) noexcept
		{
			return x * (180.0f / PiF);
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr double Degrees(double x) noexcept
		{
			return x * (180.0 / Pi);
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr double Degrees(Type x) noexcept
		{
			return Degrees(static_cast<double>(x));
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Degrees(const Point& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Float2 Degrees(const Float2& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Float3 Degrees(const Float3& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Float4 Degrees(const Float4& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z), Degrees(v.w) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Degrees(const Vec2& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec3 Degrees(const Vec3& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z) };
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec4 Degrees(const Vec4& v) noexcept
		{
			return{ Degrees(v.x), Degrees(v.y), Degrees(v.z), Degrees(v.w) };
		}
	}

	namespace detail
	{
		struct Degrees_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Degrees(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Degrees_impl();
			}
		};
	}

	constexpr auto Degrees = detail::Degrees_impl();

//////////////////////////////////////////////////
//
//	Abs
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr float Abs(float x) noexcept
		{
			return x >= 0.0f ? x : -x;
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr double Abs(double x) noexcept
		{
			return x >= 0.0 ? x : -x;
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_signed_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr Type Abs(Type x) noexcept
		{
			return x >= Type(0) ? x : -x;
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Point Abs(const Point& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float2 Abs(const Float2& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float3 Abs(const Float3& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float4 Abs(const Float4& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Abs(const Vec2& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec3 Abs(const Vec3& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z) };
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec4 Abs(const Vec4& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w) };
		}
	}

	namespace detail
	{
		struct Abs_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Abs(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Abs_impl();
			}
		};
	}

	constexpr auto Abs = detail::Abs_impl();

//////////////////////////////////////////////////
//
//	Fmod
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_integral_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr auto AbsDiff(const Type& x, const Type& y) noexcept
		{
			using U = std::make_unsigned_t<Type>;
			return (x > y) ? (static_cast<U>(x) - static_cast<U>(y))
				: (static_cast<U>(y) - static_cast<U>(x));
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_floating_point_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr auto AbsDiff(const Type& x, const Type& y) noexcept
		{
			return std::abs(x - y);
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr Float2 AbsDiff(const Float2& v1, const Float2& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y) };
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr Float3 AbsDiff(const Float3& v1, const Float3& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z) };
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr Float4 AbsDiff(const Float4& v1, const Float4& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z), AbsDiff(v1.w, v2.w) };
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 AbsDiff(const Vec2& v1, const Vec2& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y) };
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec3 AbsDiff(const Vec3& v1, const Vec3& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z) };
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec4 AbsDiff(const Vec4& v1, const Vec4& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z), AbsDiff(v1.w, v2.w) };
		}

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		template <class T, class U, class R = CommonVector_t<T, U>>
		[[nodiscard]] inline constexpr R AbsDiff(T x, U y)
		{
			return AbsDiff(static_cast<R>(x), static_cast<R>(y));
		}
	}

	namespace detail
	{
		template <class Type>
		struct AbsDiffX_impl
		{
			const Type& y;

			constexpr AbsDiffX_impl(const Type& _y) noexcept
				: y(_y) {}

			[[nodiscard]] constexpr auto operator()(const Type& x) const
			{
				return Math::AbsDiff(x, y);
			}
		};

		template <class Type>
		struct AbsDiffY_impl
		{
			const Type& x;

			constexpr AbsDiffY_impl(const Type& _x) noexcept
				: x(_x) {}

			[[nodiscard]] constexpr auto operator()(const Type& y) const
			{
				return Math::AbsDiff(x, y);
			}
		};

		struct AbsDiff_impl
		{
			template <class Type>
			constexpr auto operator() (const Type& x, const Type& y) const
			{
				return Math::AbsDiff(x, y);
			}
		};
	}

	[[nodiscard]] inline constexpr auto AbsDiff() noexcept
	{
		return detail::AbsDiff_impl();
	}

	template <class Type>
	[[nodiscard]] inline constexpr auto AbsDiff(const Type& x) noexcept
	{
		return detail::AbsDiffY_impl<Type>(x);
	}

	template <class Type>
	[[nodiscard]] inline constexpr auto AbsDiff(const Type& x, const Type& y) noexcept
	{
		return detail::AbsDiff_impl()(x, y);
	}

	template <class Type>
	[[nodiscard]] inline constexpr auto AbsDiff(PlaceHolder_t, const Type& y) noexcept
	{
		return detail::AbsDiffX_impl<Type>(y);
	}

	template <class Type>
	[[nodiscard]] inline constexpr auto AbsDiff(const Type& x, PlaceHolder_t) noexcept
	{
		return detail::AbsDiffY_impl<Type>(x);
	}

	[[nodiscard]] inline constexpr auto AbsDiff(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::AbsDiff_impl();
	}

//////////////////////////////////////////////////
//
//	Square
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 平方を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr float Square(float x) noexcept
		{
			return x * x;
		}

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		[[nodiscard]] inline constexpr double Square(double x) noexcept
		{
			return x * x;
		}

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr Type Square(Type x) noexcept
		{
			return x * x;
		}
	}

	namespace detail
	{
		struct Square_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Square(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Square_impl();
			}
		};
	}

	constexpr auto Square = detail::Square_impl();

//////////////////////////////////////////////////
//
//	Exp
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline float Exp(float x)
		{
			return std::exp(x);
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline double Exp(double x)
		{
			return std::exp(x);
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Exp(Type x)
		{
			return Exp(static_cast<double>(x));
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Exp(const Point& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Exp(const Float2& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Exp(const Float3& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Exp(const Float4& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z), Exp(v.w) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Exp(const Vec2& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Exp(const Vec3& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z) };
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Exp(const Vec4& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z), Exp(v.w) };
		}
	}

	namespace detail
	{
		struct Exp_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Exp(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Exp_impl();
			}
		};
	}

	constexpr auto Exp = detail::Exp_impl();

//////////////////////////////////////////////////
//
//	Exp2
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline float Exp2(float x)
		{
			return std::exp2(x);
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline double Exp2(double x)
		{
			return std::exp2(x);
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Exp2(Type x)
		{
			return Exp2(static_cast<double>(x));
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Exp2(const Point& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Exp2(const Float2& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Exp2(const Float3& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Exp2(const Float4& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z), Exp2(v.w) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Exp2(const Vec2& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Exp2(const Vec3& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z) };
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Exp2(const Vec4& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z), Exp2(v.w) };
		}
	}

	namespace detail
	{
		struct Exp2_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Exp2(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Exp2_impl();
			}
		};
	}

	constexpr auto Exp2 = detail::Exp2_impl();

//////////////////////////////////////////////////
//
//	Rsqrt
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline float Rsqrt(float x)
		{
			return 1.0f / std::sqrt(x);
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline double Rsqrt(double x)
		{
			return 1.0 / std::sqrt(x);
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Rsqrt(Type x)
		{
			return Rsqrt(static_cast<double>(x));
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Rsqrt(const Point& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y) };
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Rsqrt(const Float2& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y) };
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Rsqrt(const Float3& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z) };
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Rsqrt(const Float4& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z), Rsqrt(v.w) };
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Rsqrt(const Vec2& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y) };
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Rsqrt(const Vec3& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z) };
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Rsqrt(const Vec4& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z), Rsqrt(v.w) };
		}
	}

	namespace detail
	{
		struct Rsqrt_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Rsqrt(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Rsqrt_impl();
			}
		};
	}

	constexpr auto Rsqrt = detail::Rsqrt_impl();

//////////////////////////////////////////////////
//
//	Sqrt
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline float Sqrt(float x)
		{
			return std::sqrt(x);
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline double Sqrt(double x)
		{
			return std::sqrt(x);
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Sqrt(Type x)
		{
			return Sqrt(static_cast<double>(x));
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Sqrt(const Point& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y) };
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Sqrt(const Float2& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y) };
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Sqrt(const Float3& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z) };
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Sqrt(const Float4& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z), Sqrt(v.w) };
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Sqrt(const Vec2& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y) };
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Sqrt(const Vec3& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z) };
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Sqrt(const Vec4& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z), Sqrt(v.w) };
		}
	}

	namespace detail
	{
		struct Sqrt_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Sqrt(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Sqrt_impl();
			}
		};
	}

	constexpr auto Sqrt = detail::Sqrt_impl();

//////////////////////////////////////////////////
//
//	Ceil
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline float Ceil(float x)
		{
			return std::ceil(x);
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline double Ceil(double x)
		{
			return std::ceil(x);
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Ceil(Type x)
		{
			return Ceil(static_cast<double>(x));
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Ceil(const Point& v)
		{
			return{ Ceil(v.x), Ceil(v.y) };
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline Float2 Ceil(const Float2& v)
		{
			return{ Ceil(v.x), Ceil(v.y) };
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline Float3 Ceil(const Float3& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z) };
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline Float4 Ceil(const Float4& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z), Ceil(v.w) };
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Ceil(const Vec2& v)
		{
			return{ Ceil(v.x), Ceil(v.y) };
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec3 Ceil(const Vec3& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z) };
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec4 Ceil(const Vec4& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z), Ceil(v.w) };
		}
	}

	namespace detail
	{
		struct Ceil_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Ceil(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Ceil_impl();
			}
		};
	}

	constexpr auto Ceil = detail::Ceil_impl();

//////////////////////////////////////////////////
//
//	Floor
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline float Floor(float x)
		{
			return std::floor(x);
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline double Floor(double x)
		{
			return std::floor(x);
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Floor(Type x)
		{
			return Floor(static_cast<double>(x));
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Floor(const Point& v)
		{
			return{ Floor(v.x), Floor(v.y) };
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline Float2 Floor(const Float2& v)
		{
			return{ Floor(v.x), Floor(v.y) };
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline Float3 Floor(const Float3& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z) };
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline Float4 Floor(const Float4& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z), Floor(v.w) };
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Floor(const Vec2& v)
		{
			return{ Floor(v.x), Floor(v.y) };
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec3 Floor(const Vec3& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z) };
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] inline Vec4 Floor(const Vec4& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z), Floor(v.w) };
		}
	}

	namespace detail
	{
		struct Floor_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Floor(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Floor_impl();
			}
		};
	}

	constexpr auto Floor = detail::Floor_impl();

//////////////////////////////////////////////////
//
//	Round
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline float Round(float x)
		{
			return std::round(x);
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline double Round(double x)
		{
			return std::round(x);
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Round(Type x)
		{
			return Round(static_cast<double>(x));
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Round(const Point& v)
		{
			return{ Round(v.x), Round(v.y) };
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline Float2 Round(const Float2& v)
		{
			return{ Round(v.x), Round(v.y) };
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline Float3 Round(const Float3& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z) };
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline Float4 Round(const Float4& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z), Round(v.w) };
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Round(const Vec2& v)
		{
			return{ Round(v.x), Round(v.y) };
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline Vec3 Round(const Vec3& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z) };
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] inline Vec4 Round(const Vec4& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z), Round(v.w) };
		}
	}

	namespace detail
	{
		struct Round_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Round(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Round_impl();
			}
		};
	}

	constexpr auto Round = detail::Round_impl();

//////////////////////////////////////////////////
//
//	Clamp
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Point Clamp(const Point& v, int32 min, int32 max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max) };
		}

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float2 Clamp(const Float2& v, float min, float max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max) };
		}

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float3 Clamp(const Float3& v, float min, float max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max) };
		}

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float4 Clamp(const Float4& v, float min, float max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max), s3d::Clamp(v.w, min, max) };
		}

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Clamp(const Vec2& v, double min, double max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max) };
		}

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec3 Clamp(const Vec3& v, double min, double max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max) };
		}

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec4 Clamp(const Vec4& v, double min, double max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max), s3d::Clamp(v.w, min, max) };
		}
	}

//////////////////////////////////////////////////
//
//	Saturate
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr float Saturate(float x)
		{
			return s3d::Clamp(x, 0.0f, 1.0f);
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr double Saturate(double x)
		{
			return s3d::Clamp(x, 0.0, 1.0);
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr double Saturate(Type x)
		{
			return Saturate(static_cast<double>(x));
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Saturate(const Point& v)
		{
			return{ Saturate(v.x), Saturate(v.y) };
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float2 Saturate(const Float2& v)
		{
			return{ Saturate(v.x), Saturate(v.y) };
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float3 Saturate(const Float3& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z) };
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Float4 Saturate(const Float4& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z), Saturate(v.w) };
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec2 Saturate(const Vec2& v)
		{
			return{ Saturate(v.x), Saturate(v.y) };
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec3 Saturate(const Vec3& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z) };
		}

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] inline constexpr Vec4 Saturate(const Vec4& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z), Saturate(v.w) };
		}
	}

	namespace detail
	{
		struct Saturate_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Saturate(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Saturate_impl();
			}
		};
	}

	constexpr auto Saturate = detail::Saturate_impl();

//////////////////////////////////////////////////
//
//	Acos
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline float Acos(float x)
		{
			return std::acos(x);
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline double Acos(double x)
		{
			return std::acos(x);
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Acos(Type x)
		{
			return Acos(static_cast<double>(x));
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Acos(const Point& v)
		{
			return{ Acos(v.x), Acos(v.y) };
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Acos(const Float2& v)
		{
			return{ Acos(v.x), Acos(v.y) };
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Acos(const Float3& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z) };
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Acos(const Float4& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z), Acos(v.w) };
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Acos(const Vec2& v)
		{
			return{ Acos(v.x), Acos(v.y) };
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Acos(const Vec3& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z) };
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Acos(const Vec4& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z), Acos(v.w) };
		}
	}

	namespace detail
	{
		struct Acos_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Acos(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Acos_impl();
			}
		};
	}

	constexpr auto Acos = detail::Acos_impl();

//////////////////////////////////////////////////
//
//	Asin
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline float Asin(float x)
		{
			return std::asin(x);
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline double Asin(double x)
		{
			return std::asin(x);
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Asin(Type x)
		{
			return Asin(static_cast<double>(x));
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Asin(const Point& v)
		{
			return{ Asin(v.x), Asin(v.y) };
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Asin(const Float2& v)
		{
			return{ Asin(v.x), Asin(v.y) };
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Asin(const Float3& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z) };
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Asin(const Float4& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z), Asin(v.w) };
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Asin(const Vec2& v)
		{
			return{ Asin(v.x), Asin(v.y) };
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Asin(const Vec3& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z) };
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Asin(const Vec4& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z), Asin(v.w) };
		}
	}

	namespace detail
	{
		struct Asin_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Asin(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Asin_impl();
			}
		};
	}

	constexpr auto Asin = detail::Asin_impl();

//////////////////////////////////////////////////
//
//	Atan
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline float Atan(float x)
		{
			return std::atan(x);
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline double Atan(double x)
		{
			return std::atan(x);
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Atan(Type x)
		{
			return Atan(static_cast<double>(x));
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Atan(const Point& v)
		{
			return{ Atan(v.x), Atan(v.y) };
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Atan(const Float2& v)
		{
			return{ Atan(v.x), Atan(v.y) };
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Atan(const Float3& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z) };
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Atan(const Float4& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z), Atan(v.w) };
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Atan(const Vec2& v)
		{
			return{ Atan(v.x), Atan(v.y) };
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Atan(const Vec3& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z) };
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Atan(const Vec4& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z), Atan(v.w) };
		}
	}

	namespace detail
	{
		struct Atan_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Atan(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Atan_impl();
			}
		};
	}

	constexpr auto Atan = detail::Atan_impl();

//////////////////////////////////////////////////
//
//	Atan2
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// y/x のアークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline float Atan2(float y, float x)
		{
			return std::atan2(y, x);
		}

		/// <summary>
		/// y/x のアークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline double Atan2(double y, double x)
		{
			return std::atan2(y, x);
		}

		/// <summary>
		/// y/x のアークタンジェントを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Atan2(Type y, Type x)
		{
			return Atan2(static_cast<double>(y), static_cast<double>(x));
		}
	}

//////////////////////////////////////////////////
//
//	Cos
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline float Cos(float x)
		{
			return std::cos(x);
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline double Cos(double x)
		{
			return std::cos(x);
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Cos(Type x)
		{
			return Cos(static_cast<double>(x));
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Cos(const Point& v)
		{
			return{ Cos(v.x), Cos(v.y) };
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Cos(const Float2& v)
		{
			return{ Cos(v.x), Cos(v.y) };
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Cos(const Float3& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z) };
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Cos(const Float4& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z), Cos(v.w) };
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Cos(const Vec2& v)
		{
			return{ Cos(v.x), Cos(v.y) };
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Cos(const Vec3& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z) };
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Cos(const Vec4& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z), Cos(v.w) };
		}
	}

	namespace detail
	{
		struct Cos_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Cos(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Cos_impl();
			}
		};
	}

	constexpr auto Cos = detail::Cos_impl();

//////////////////////////////////////////////////
//
//	Cosh
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline float Cosh(float x)
		{
			return std::cosh(x);
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline double Cosh(double x)
		{
			return std::cosh(x);
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Cosh(Type x)
		{
			return Cosh(static_cast<double>(x));
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Cosh(const Point& v)
		{
			return{ Cosh(v.x), Cosh(v.y) };
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Cosh(const Float2& v)
		{
			return{ Cosh(v.x), Cosh(v.y) };
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Cosh(const Float3& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z) };
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Cosh(const Float4& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z), Cosh(v.w) };
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Cosh(const Vec2& v)
		{
			return{ Cosh(v.x), Cosh(v.y) };
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Cosh(const Vec3& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z) };
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Cosh(const Vec4& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z), Cosh(v.w) };
		}
	}

	namespace detail
	{
		struct Cosh_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Cosh(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Cosh_impl();
			}
		};
	}

	constexpr auto Cosh = detail::Cosh_impl();

//////////////////////////////////////////////////
//
//	Sin
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline float Sin(float x)
		{
			return std::sin(x);
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline double Sin(double x)
		{
			return std::sin(x);
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Sin(Type x)
		{
			return Sin(static_cast<double>(x));
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Sin(const Point& v)
		{
			return{ Sin(v.x), Sin(v.y) };
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Sin(const Float2& v)
		{
			return{ Sin(v.x), Sin(v.y) };
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Sin(const Float3& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z) };
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Sin(const Float4& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z), Sin(v.w) };
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Sin(const Vec2& v)
		{
			return{ Sin(v.x), Sin(v.y) };
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Sin(const Vec3& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z) };
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Sin(const Vec4& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z), Sin(v.w) };
		}
	}

	namespace detail
	{
		struct Sin_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Sin(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Sin_impl();
			}
		};
	}

	constexpr auto Sin = detail::Sin_impl();

//////////////////////////////////////////////////
//
//	Sinh
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline float Sinh(float x)
		{
			return std::sinh(x);
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline double Sinh(double x)
		{
			return std::sinh(x);
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Sinh(Type x)
		{
			return Sinh(static_cast<double>(x));
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Sinh(const Point& v)
		{
			return{ Sinh(v.x), Sinh(v.y) };
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Sinh(const Float2& v)
		{
			return{ Sinh(v.x), Sinh(v.y) };
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Sinh(const Float3& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z) };
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Sinh(const Float4& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z), Sinh(v.w) };
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Sinh(const Vec2& v)
		{
			return{ Sinh(v.x), Sinh(v.y) };
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Sinh(const Vec3& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z) };
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Sinh(const Vec4& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z), Sinh(v.w) };
		}
	}

	namespace detail
	{
		struct Sinh_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Sinh(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Sinh_impl();
			}
		};
	}

	constexpr auto Sinh = detail::Sinh_impl();

//////////////////////////////////////////////////
//
//	Tan
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline float Tan(float x)
		{
			return std::tan(x);
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline double Tan(double x)
		{
			return std::tan(x);
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Tan(Type x)
		{
			return Tan(static_cast<double>(x));
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Tan(const Point& v)
		{
			return{ Tan(v.x), Tan(v.y) };
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Tan(const Float2& v)
		{
			return{ Tan(v.x), Tan(v.y) };
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Tan(const Float3& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z) };
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Tan(const Float4& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z), Tan(v.w) };
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Tan(const Vec2& v)
		{
			return{ Tan(v.x), Tan(v.y) };
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Tan(const Vec3& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z) };
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Tan(const Vec4& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z), Tan(v.w) };
		}
	}

	namespace detail
	{
		struct Tan_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Tan(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Tan_impl();
			}
		};
	}

	constexpr auto Tan = detail::Tan_impl();

//////////////////////////////////////////////////
//
//	Tanh
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline float Tanh(float x)
		{
			return std::tanh(x);
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline double Tanh(double x)
		{
			return std::tanh(x);
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Tanh(Type x)
		{
			return Tanh(static_cast<double>(x));
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Tanh(const Point& v)
		{
			return{ Tanh(v.x), Tanh(v.y) };
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float2 Tanh(const Float2& v)
		{
			return{ Tanh(v.x), Tanh(v.y) };
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float3 Tanh(const Float3& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z) };
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Float4 Tanh(const Float4& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z), Tanh(v.w) };
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec2 Tanh(const Vec2& v)
		{
			return{ Tanh(v.x), Tanh(v.y) };
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec3 Tanh(const Vec3& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z) };
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] inline Vec4 Tanh(const Vec4& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z), Tanh(v.w) };
		}
	}

	namespace detail
	{
		struct Tanh_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Tanh(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Tanh_impl();
			}
		};
	}

	constexpr auto Tanh = detail::Tanh_impl();

//////////////////////////////////////////////////
//
//	Normalize
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline float Normalize(float x)
		{
			return x ? 1.0f : 0.0f;
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline double Normalize(double x)
		{
			return x ? 1.0 : 0.0;
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline double Normalize(Type x)
		{
			return Normalize(static_cast<double>(x));
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Normalize(const Point& v)
		{
			return Vec2(v).normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline Float2 Normalize(const Float2& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline Float3 Normalize(const Float3& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline Float4 Normalize(const Float4& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline Vec2 Normalize(const Vec2& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline Vec3 Normalize(const Vec3& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		[[nodiscard]] inline Vec4 Normalize(const Vec4& v)
		{
			return v.normalized();
		}
	}

	namespace detail
	{
		struct Normalize_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Normalize(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Normalize_impl();
			}
		};
	}

	constexpr auto Normalize = detail::Normalize_impl();

//////////////////////////////////////////////////
//
//	Smoothstep
//
//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		[[nodiscard]] inline constexpr float Smoothstep(float min, float max, float x) noexcept
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
		[[nodiscard]] inline constexpr double Smoothstep(double min, double max, double x) noexcept
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
		[[nodiscard]] inline constexpr float Smoothstep(float x) noexcept
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
		[[nodiscard]] inline constexpr double Smoothstep(double x) noexcept
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

	namespace detail
	{
		struct Smoothstep_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::Smoothstep(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::Smoothstep_impl();
			}
		};
	}

	constexpr auto Smoothstep = detail::Smoothstep_impl();
}
