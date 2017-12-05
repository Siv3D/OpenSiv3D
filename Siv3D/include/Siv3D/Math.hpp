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
			[[nodiscard]] constexpr auto operator()(TypeX&& x) const
			{
				return Math::Fmod(std::forward<TypeX>(x), y);
			}
		};

		template <class TypeX>
		struct FmodY_impl
		{
			const TypeX& x;

			constexpr FmodY_impl(const TypeX& _x) noexcept
				: x(_x) {}

			template <class TypeY>
			[[nodiscard]] constexpr auto operator()(TypeY&& y) const
			{
				return Math::Fmod(x, std::forward<TypeY>(y));
			}
		};

		struct Fmod_impl
		{
			template <class TypeX, class TypeY>
			constexpr auto operator() (TypeX&& x, TypeY&& y) const
			{
				return Math::Fmod(std::forward<TypeX>(x), std::forward<TypeY>(y));
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
	[[nodiscard]] inline constexpr auto Fmod(TypeX&& x, TypeY&& y) noexcept
	{
		return detail::Fmod_impl()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Fmod(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::FmodX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Fmod(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::FmodY_impl<TypeX>(std::forward<TypeX>(x));
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
		template <class Type, std::enable_if_t<std::is_arithmetic<Type>::value>* = nullptr>
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
			[[nodiscard]] constexpr auto operator() (TypeX&& x) const noexcept
			{
				return Math::Fraction(std::forward<TypeX>(x));
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

	}

//////////////////////////////////////////////////
//
//	Ldexp
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Log
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Log2
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Log10
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Modf
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Pow
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Sign
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Radians
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Degrees
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Abs
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Square
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Exp
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Exp2
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Rsqrt
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Sqrt
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Ceil
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Floor
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Round
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Clamp
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Saturate
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Acos
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Asin
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Atan
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Atan2
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Cos
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Cosh
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Sin
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Sinh
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Tan
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Tanh
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Normalize
//
//////////////////////////////////////////////////

	namespace Math
	{

	}

//////////////////////////////////////////////////
//
//	Smoothstep
//
//////////////////////////////////////////////////

	namespace Math
	{

	}
}
