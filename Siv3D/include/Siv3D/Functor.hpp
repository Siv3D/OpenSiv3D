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
# include <functional>
# include <cmath>
# include "Fwd.hpp"
# include "PlaceHolder.hpp"
# include "Meta.hpp"
# include "Functor.ipp"

namespace s3d
{
	//////////////////////////////////////////////////
	//
	//	==
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Equal() noexcept
	{
		return std::equal_to<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Equal(const TypeX& x) noexcept
	{
		return detail::BinaryEqualY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Equal(TypeX&& x, TypeY&& y) noexcept(noexcept(std::equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Equal(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Equal(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Equal(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::equal_to<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator ==(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator ==(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator ==(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::equal_to<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	!=
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto NotEqual() noexcept
	{
		return std::not_equal_to<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto NotEqual(const TypeX& x) noexcept
	{
		return detail::BinaryNotEqualY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto NotEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::not_equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::not_equal_to<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto NotEqual(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryNotEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto NotEqual(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryNotEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto NotEqual(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::not_equal_to<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator !=(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryNotEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator !=(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryNotEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator !=(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::not_equal_to<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	<
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThan() noexcept
	{
		return std::less<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThan(const TypeX& x) noexcept
	{
		return LessThan(Arg::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto LessThan(TypeX&& x, TypeY&& y) noexcept(noexcept(std::less<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::less<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto LessThan(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThan(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryLessThanY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThan(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::less<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator <(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator <(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryLessThanY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator <(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::less<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	<=
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThanEqual() noexcept
	{
		return std::less_equal<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThanEqual(const TypeX& x) noexcept
	{
		return LessThanEqual(Arg::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto LessThanEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::less_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::less_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto LessThanEqual(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto LessThanEqual(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryLessThanEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto LessThanEqual(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::less_equal<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator <=(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryLessThanEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator <=(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryLessThanEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator <=(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::less_equal<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	>
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThan() noexcept
	{
		return std::greater<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThan(const TypeX& x) noexcept
	{
		return GreaterThan(Arg::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThan(TypeX&& x, TypeY&& y) noexcept(noexcept(std::greater<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::greater<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThan(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThan(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryGreaterThanY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThan(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::greater<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator >(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator >(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryGreaterThanY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator >(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::greater<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	>=
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThanEqual() noexcept
	{
		return std::greater_equal<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(const TypeX& x) noexcept
	{
		return GreaterThanEqual(Arg::_, x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(TypeX&& x, TypeY&& y) noexcept(noexcept(std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::greater_equal<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryGreaterThanEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto GreaterThanEqual(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::greater_equal<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator >=(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryGreaterThanEqualX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator >=(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryGreaterThanEqualY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator >=(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::greater_equal<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	+()
	//
	//////////////////////////////////////////////////

	constexpr auto UnaryPlus = detail::UnaryPlus_impl();

	[[nodiscard]] inline constexpr auto operator +(PlaceHolder_t) noexcept
	{
		return detail::UnaryPlus_impl();
	}

	//////////////////////////////////////////////////
	//
	//	-()
	//
	//////////////////////////////////////////////////

	constexpr auto Negate = detail::Negate_impl();

	[[nodiscard]] inline constexpr auto operator -(PlaceHolder_t) noexcept
	{
		return detail::Negate_impl();
	}

	//////////////////////////////////////////////////
	//
	//	+
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Plus() noexcept
	{
		return std::plus<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Plus(const TypeX& x) noexcept
	{
		return detail::BinaryPlusY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Plus(TypeX&& x, TypeY&& y) noexcept(noexcept(std::plus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::plus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Plus(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryPlusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Plus(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryPlusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Plus(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::plus<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator +(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryPlusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator +(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryPlusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator +(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::plus<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	-
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Minus() noexcept
	{
		return std::minus<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Minus(const TypeX& x) noexcept
	{
		return detail::BinaryMinusY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Minus(TypeX&& x, TypeY&& y) noexcept(noexcept(std::minus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::minus<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Minus(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryMinusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Minus(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryMinusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Minus(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::minus<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator -(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryMinusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator -(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryMinusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator -(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::minus<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	*
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Multiplies() noexcept
	{
		return std::multiplies<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Multiplies(const TypeX& x) noexcept
	{
		return detail::BinaryMultipliesY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Multiplies(TypeX&& x, TypeY&& y) noexcept(noexcept(std::multiplies<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::multiplies<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Multiplies(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryMultipliesX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Multiplies(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryMultipliesY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Multiplies(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::multiplies<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator *(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryMultipliesX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator *(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryMultipliesY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator *(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::multiplies<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	/
	//
	//////////////////////////////////////////////////

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Divides() noexcept
	{
		return std::divides<Type>();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Divides(const TypeX& x) noexcept
	{
		return detail::BinaryDividesY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Divides(TypeX&& x, TypeY&& y) noexcept(noexcept(std::divides<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return std::divides<Type>()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Divides(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryDividesX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Divides(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryDividesY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Divides(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::divides<Type>();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator /(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryDividesX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator /(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryDividesY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator /(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return std::divides<Type>();
	}

	//////////////////////////////////////////////////
	//
	//	%
	//
	//////////////////////////////////////////////////

	[[nodiscard]] inline constexpr auto Modulus() noexcept
	{
		return detail::ModulusF_impl();
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Modulus(const TypeX& x) noexcept
	{
		return detail::BinaryModulusY_impl<TypeX>(x);
	}

	template <class Type = void, class TypeX, class TypeY>
	[[nodiscard]] inline constexpr auto Modulus(TypeX&& x, TypeY&& y) noexcept(noexcept(detail::ModulusF_impl()(std::forward<TypeX>(x), std::forward<TypeY>(y))))
	{
		return detail::ModulusF_impl()(std::forward<TypeX>(x), std::forward<TypeY>(y));
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto Modulus(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryModulusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto Modulus(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryModulusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto Modulus(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::ModulusF_impl();
	}

	template <class TypeY>
	[[nodiscard]] inline constexpr auto operator %(PlaceHolder_t, TypeY&& y) noexcept
	{
		return detail::BinaryModulusX_impl<TypeY>(std::forward<TypeY>(y));
	}

	template <class TypeX>
	[[nodiscard]] inline constexpr auto operator %(TypeX&& x, PlaceHolder_t) noexcept
	{
		return detail::BinaryModulusY_impl<TypeX>(std::forward<TypeX>(x));
	}

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator %(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::ModulusF_impl();
	}

	//////////////////////////////////////////////////
	//
	//	!()
	//
	//////////////////////////////////////////////////

	inline constexpr auto Not = detail::UnaryNot_impl();

	template <class Type = void>
	[[nodiscard]] inline constexpr auto operator !(PlaceHolder_t) noexcept
	{
		return detail::UnaryNot_impl();
	}

	//////////////////////////////////////////////////
	//
	//	IsOdd
	//
	//////////////////////////////////////////////////

	inline constexpr auto IsOdd = detail::Odd_impl();

	//////////////////////////////////////////////////
	//
	//	IsEven
	//
	//////////////////////////////////////////////////

	inline constexpr auto IsEven = detail::Even_impl();

	//////////////////////////////////////////////////
	//
	//	Id
	//
	//////////////////////////////////////////////////

	inline constexpr auto Id = detail::Id_impl();

	//////////////////////////////////////////////////
	//
	//	FromEnum
	//
	//////////////////////////////////////////////////

	inline constexpr auto FromEnum = detail::FromEnum_impl();

	//////////////////////////////////////////////////
	//
	//	ToEnum
	//
	//////////////////////////////////////////////////

	template <class Enum>
	inline constexpr auto ToEnum = detail::ToEnum_impl<Enum>();
}
