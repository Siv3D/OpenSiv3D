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

# pragma once
# include <cfloat>
# include <emmintrin.h>
# include <numeric>
# include "Utility.hpp"
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
		[[nodiscard]] Float2 Fmod(const Float2& v1, const Float2& v2);

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] Float3 Fmod(const Float3& v1, const Float3& v2);

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] Float4 Fmod(const Float4& v1, const Float4& v2);

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Fmod(const Vec2& v1, const Vec2& v2);

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Fmod(const Vec3& v1, const Vec3& v2);

		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Fmod(const Vec4& v1, const Vec4& v2);

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
		[[nodiscard]] Float2 Fraction(const Float2& v);

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] Float3 Fraction(const Float3& v);

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] Float4 Fraction(const Float4& v);

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] Vec2 Fraction(const Vec2& v);

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] Vec3 Fraction(const Vec3& v);

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		[[nodiscard]] Vec4 Fraction(const Vec4& v);
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
		Float2 Frexp(const Float2& x, Float2& exp);

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		Float3 Frexp(const Float3& x, Float3& exp);

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		Float4 Frexp(const Float4& x, Float4& exp);

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		Vec2 Frexp(const Vec2& x, Vec2& exp);

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		Vec3 Frexp(const Vec3& x, Vec3& exp);

		/// <summary>
		/// 仮数部と指数部を取得します。
		/// </summary>
		Vec4 Frexp(const Vec4& x, Vec4& exp);
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
		[[nodiscard]] Float2 Ldexp(const Float2& x, const Float2& exp);

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] Float3 Ldexp(const Float3& x, const Float3& exp);

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] Float4 Ldexp(const Float4& x, const Float4& exp);

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Ldexp(const Vec2& x, const Vec2& exp);

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Ldexp(const Vec3& x, const Vec3& exp);

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Ldexp(const Vec4& x, const Vec4& exp);

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
		[[nodiscard]] Vec2 Log(const Point& v);

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float2 Log(const Float2& v);

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float3 Log(const Float3& v);

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float4 Log(const Float4& v);

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Log(const Vec2& v);

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Log(const Vec3& v);

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Log(const Vec4& v);
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
		[[nodiscard]] Vec2 Log2(const Point& v);

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float2 Log2(const Float2& v);

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float3 Log2(const Float3& v);

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float4 Log2(const Float4& v);

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Log2(const Vec2& v);

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Log2(const Vec3& v);

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Log2(const Vec4& v);
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
		[[nodiscard]] Vec2 Log10(const Point& v);

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float2 Log10(const Float2& v);

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float3 Log10(const Float3& v);

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Float4 Log10(const Float4& v);

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Log10(const Vec2& v);

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Log10(const Vec3& v);

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Log10(const Vec4& v);
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
		Float2 Modf(const Float2& x, Float2& i);

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		Float3 Modf(const Float3& x, Float3& i);

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		Float4 Modf(const Float4& x, Float4& i);

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		Vec2 Modf(const Vec2& x, Vec2& i);

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		Vec3 Modf(const Vec3& x, Vec3& i);

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		Vec4 Modf(const Vec4& x, Vec4& i);
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
		Vec2 Sign(const Point& v) noexcept;

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		Float2 Sign(const Float2& v) noexcept;

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		Float3 Sign(const Float3& v) noexcept;

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		Float4 Sign(const Float4& v) noexcept;

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		Vec2 Sign(const Vec2& v) noexcept;

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		Vec3 Sign(const Vec3& v) noexcept;

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		Vec4 Sign(const Vec4& v) noexcept;
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
	//	ToRadians
	//
	//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr float ToRadians(float x) noexcept
		{
			return x * (PiF / 180.0f);
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] inline constexpr double ToRadians(double x) noexcept
		{
			return x * (Pi / 180.0);
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr double ToRadians(Type x) noexcept
		{
			return ToRadians(static_cast<double>(x));
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] Vec2 ToRadians(const Point& v) noexcept;

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] Float2 ToRadians(const Float2& v) noexcept;

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] Float3 ToRadians(const Float3& v) noexcept;

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] Float4 ToRadians(const Float4& v) noexcept;

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] Vec2 ToRadians(const Vec2& v) noexcept;

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] Vec3 ToRadians(const Vec3& v) noexcept;

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		[[nodiscard]] Vec4 ToRadians(const Vec4& v) noexcept;
	}

	namespace detail
	{
		struct ToRadians_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::ToRadians(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::ToRadians_impl();
			}
		};
	}

	constexpr auto ToRadians = detail::ToRadians_impl();

	//////////////////////////////////////////////////
	//
	//	ToDegrees
	//
	//////////////////////////////////////////////////

	namespace Math
	{
		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr float ToDegrees(float x) noexcept
		{
			return x * (180.0f / PiF);
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] inline constexpr double ToDegrees(double x) noexcept
		{
			return x * (180.0 / Pi);
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		template <class Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr double ToDegrees(Type x) noexcept
		{
			return ToDegrees(static_cast<double>(x));
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] Vec2 ToDegrees(const Point& v) noexcept;

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] Float2 ToDegrees(const Float2& v) noexcept;

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] Float3 ToDegrees(const Float3& v) noexcept;

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] Float4 ToDegrees(const Float4& v) noexcept;

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] Vec2 ToDegrees(const Vec2& v) noexcept;

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] Vec3 ToDegrees(const Vec3& v) noexcept;

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		[[nodiscard]] Vec4 ToDegrees(const Vec4& v) noexcept;
	}

	namespace detail
	{
		struct ToDegrees_impl
		{
			template <class TypeX>
			[[nodiscard]] constexpr auto operator() (const TypeX& x) const noexcept
			{
				return Math::ToDegrees(x);
			}

			template <class Type = void>
			[[nodiscard]] constexpr auto operator ()(PlaceHolder_t) const noexcept
			{
				return detail::ToDegrees_impl();
			}
		};
	}

	constexpr auto ToDegrees = detail::ToDegrees_impl();

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
		template <class Type, std::enable_if_t<std::is_unsigned_v<Type>>* = nullptr>
		[[nodiscard]] inline constexpr Type Abs(Type x) noexcept
		{
			return x;
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] Point Abs(const Point& v) noexcept;

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] Float2 Abs(const Float2& v) noexcept;

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] Float3 Abs(const Float3& v) noexcept;

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] Float4 Abs(const Float4& v) noexcept;

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] Vec2 Abs(const Vec2& v) noexcept;

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] Vec3 Abs(const Vec3& v) noexcept;

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		[[nodiscard]] Vec4 Abs(const Vec4& v) noexcept;
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
	//	AbsDiff
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
		[[nodiscard]] Float2 AbsDiff(const Float2& v1, const Float2& v2);

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] Float3 AbsDiff(const Float3& v1, const Float3& v2);

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] Float4 AbsDiff(const Float4& v1, const Float4& v2);

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] Vec2 AbsDiff(const Vec2& v1, const Vec2& v2);

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] Vec3 AbsDiff(const Vec3& v1, const Vec3& v2);

		/// <summary>
		/// 差の絶対値を計算します。
		/// </summary>
		[[nodiscard]] Vec4 AbsDiff(const Vec4& v1, const Vec4& v2);

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
		[[nodiscard]] Vec2 Exp(const Point& v);

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] Float2 Exp(const Float2& v);

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] Float3 Exp(const Float3& v);

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] Float4 Exp(const Float4& v);

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Exp(const Vec2& v);

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Exp(const Vec3& v);

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Exp(const Vec4& v);
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
		[[nodiscard]] Vec2 Exp2(const Point& v);

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] Float2 Exp2(const Float2& v);

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] Float3 Exp2(const Float3& v);

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] Float4 Exp2(const Float4& v);

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Exp2(const Vec2& v);

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Exp2(const Vec3& v);

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Exp2(const Vec4& v);
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
		[[nodiscard]] Vec2 Rsqrt(const Point& v);

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] Float2 Rsqrt(const Float2& v);

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] Float3 Rsqrt(const Float3& v);

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] Float4 Rsqrt(const Float4& v);

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Rsqrt(const Vec2& v);

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Rsqrt(const Vec3& v);

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Rsqrt(const Vec4& v);
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
		[[nodiscard]] Vec2 Sqrt(const Point& v);

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] Float2 Sqrt(const Float2& v);

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] Float3 Sqrt(const Float3& v);

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] Float4 Sqrt(const Float4& v);

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] Vec2 Sqrt(const Vec2& v);

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] Vec3 Sqrt(const Vec3& v);

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		[[nodiscard]] Vec4 Sqrt(const Vec4& v);
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
		[[nodiscard]] inline constexpr Vec2 Ceil(const Point& v)
		{
			return{ v.x, v.y };
		}

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] Float2 Ceil(const Float2& v);

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] Float3 Ceil(const Float3& v);

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] Float4 Ceil(const Float4& v);

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] Vec2 Ceil(const Vec2& v);

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] Vec3 Ceil(const Vec3& v);

		/// <summary>
		/// 現在の値以上の最小の整数を返します。
		/// </summary>
		[[nodiscard]] Vec4 Ceil(const Vec4& v);
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
		[[nodiscard]] inline constexpr Vec2 Floor(const Point& v)
		{
			return{ v.x, v.y };
		}

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] Float2 Floor(const Float2& v);

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] Float3 Floor(const Float3& v);

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] Float4 Floor(const Float4& v);

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] Vec2 Floor(const Vec2& v);

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] Vec3 Floor(const Vec3& v);

		/// <summary>
		/// 現在の値以下の最大の整数を返します。
		/// </summary>
		[[nodiscard]] Vec4 Floor(const Vec4& v);
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
		[[nodiscard]] inline constexpr Vec2 Round(const Point& v)
		{
			return{ v.x, v.y };
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] Float2 Round(const Float2& v);

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] Float3 Round(const Float3& v);

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] Float4 Round(const Float4& v);

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] Vec2 Round(const Vec2& v);

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] Vec3 Round(const Vec3& v);

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		[[nodiscard]] Vec4 Round(const Vec4& v);
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
		[[nodiscard]] Point Clamp(const Point& v, int32 min, int32 max);

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Float2 Clamp(const Float2& v, float min, float max);

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Float3 Clamp(const Float3& v, float min, float max);

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Float4 Clamp(const Float4& v, float min, float max);

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Vec2 Clamp(const Vec2& v, double min, double max);

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Vec3 Clamp(const Vec3& v, double min, double max);

		/// <summary>
		/// 最小値と最大値の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Vec4 Clamp(const Vec4& v, double min, double max);
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
		[[nodiscard]] Vec2 Saturate(const Point& v);

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Float2 Saturate(const Float2& v);

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Float3 Saturate(const Float3& v);

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Float4 Saturate(const Float4& v);

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Vec2 Saturate(const Vec2& v);

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Vec3 Saturate(const Vec3& v);

		/// <summary>
		/// 成分を [0, 1] の範囲にクランプした値を返します。
		/// </summary>
		[[nodiscard]] Vec4 Saturate(const Vec4& v);
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
		[[nodiscard]] Vec2 Acos(const Point& v);

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] Float2 Acos(const Float2& v);

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] Float3 Acos(const Float3& v);

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] Float4 Acos(const Float4& v);

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Acos(const Vec2& v);

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Acos(const Vec3& v);

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Acos(const Vec4& v);
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
		[[nodiscard]] Vec2 Asin(const Point& v);

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] Float2 Asin(const Float2& v);

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] Float3 Asin(const Float3& v);

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] Float4 Asin(const Float4& v);

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Asin(const Vec2& v);

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Asin(const Vec3& v);

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Asin(const Vec4& v);
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
		[[nodiscard]] Vec2 Atan(const Point& v);

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float2 Atan(const Float2& v);

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float3 Atan(const Float3& v);

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float4 Atan(const Float4& v);

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Atan(const Vec2& v);

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Atan(const Vec3& v);

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Atan(const Vec4& v);
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
		[[nodiscard]] Vec2 Cos(const Point& v);

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] Float2 Cos(const Float2& v);

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] Float3 Cos(const Float3& v);

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] Float4 Cos(const Float4& v);

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Cos(const Vec2& v);

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Cos(const Vec3& v);

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Cos(const Vec4& v);
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
		[[nodiscard]] Vec2 Cosh(const Point& v);

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] Float2 Cosh(const Float2& v);

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] Float3 Cosh(const Float3& v);

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] Float4 Cosh(const Float4& v);

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Cosh(const Vec2& v);

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Cosh(const Vec3& v);

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Cosh(const Vec4& v);
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
		[[nodiscard]] Vec2 Sin(const Point& v);

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] Float2 Sin(const Float2& v);

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] Float3 Sin(const Float3& v);

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] Float4 Sin(const Float4& v);

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Sin(const Vec2& v);

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Sin(const Vec3& v);

		/// <summary>
		/// サインを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Sin(const Vec4& v);
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
		[[nodiscard]] Vec2 Sinh(const Point& v);

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] Float2 Sinh(const Float2& v);

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] Float3 Sinh(const Float3& v);

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] Float4 Sinh(const Float4& v);

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Sinh(const Vec2& v);

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Sinh(const Vec3& v);

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Sinh(const Vec4& v);
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
		[[nodiscard]] Vec2 Tan(const Point& v);

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float2 Tan(const Float2& v);

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float3 Tan(const Float3& v);

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float4 Tan(const Float4& v);

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Tan(const Vec2& v);

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Tan(const Vec3& v);

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Tan(const Vec4& v);
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
		[[nodiscard]] Vec2 Tanh(const Point& v);

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float2 Tanh(const Float2& v);

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float3 Tanh(const Float3& v);

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Float4 Tanh(const Float4& v);

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec2 Tanh(const Vec2& v);

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec3 Tanh(const Vec3& v);

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		[[nodiscard]] Vec4 Tanh(const Vec4& v);
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

	namespace Math
	{
		template <class T, class U, std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<U>>* = nullptr>
		[[nodiscard]] inline constexpr auto GCD(T x, U y) noexcept
		{
			return std::gcd(x, y);
		}

		template <class T, class U, std::enable_if_t<std::is_integral_v<T> && std::is_integral_v<U>>* = nullptr>
		[[nodiscard]] inline constexpr auto LCM(T x, U y) noexcept
		{
			return std::lcm(x, y);
		}
	}
}
