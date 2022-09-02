﻿//-----------------------------------------------
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
	//////////////////////////////////////////////////
	//
	//	Max
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_SCALAR_
	inline constexpr Scalar Max(const Scalar a, const Scalar b) noexcept
	{
		return (a < b) ? b : a;
	}

	SIV3D_CONCEPT_NONSCALAR_
	inline constexpr const NonScalar& Max(const NonScalar& a, const NonScalar& b) noexcept(noexcept(a < b))
	{
		return (a < b) ? b : a;
	}
	
	template <class Type>
	inline constexpr Type Max(std::initializer_list<Type> ilist)
	{
		return *std::max_element(ilist.begin(), ilist.end());
	}

	//////////////////////////////////////////////////
	//
	//	Min
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_SCALAR_
	inline constexpr Scalar Min(const Scalar a, const Scalar b) noexcept
	{
		return (b < a) ? b : a;
	}

	SIV3D_CONCEPT_NONSCALAR_
	inline constexpr const NonScalar& Min(const NonScalar& a, const NonScalar& b) noexcept(noexcept(b < a))
	{
		return (b < a) ? b : a;
	}

	template <class Type>
	inline constexpr Type Min(std::initializer_list<Type> ilist)
	{
		return *std::min_element(ilist.begin(), ilist.end());
	}

	//////////////////////////////////////////////////
	//
	//	Clamp
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_SCALAR_
	inline constexpr Scalar Clamp(const Scalar v, const Scalar min, const Scalar max) noexcept
	{
		if (max < v)
		{
			return max;
		}

		if (v < min)
		{
			return min;
		}

		return v;
	}

	SIV3D_CONCEPT_NONSCALAR_
	inline constexpr const NonScalar& Clamp(const NonScalar& v, const NonScalar& min, const NonScalar& max) noexcept(noexcept(max < v) && noexcept(v < min))
	{
		if (max < v)
		{
			return max;
		}

		if (v < min)
		{
			return min;
		}

		return v;
	}

	//////////////////////////////////////////////////
	//
	//	InRange
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_SCALAR_
	inline constexpr bool InRange(const Scalar v, const Scalar min, const Scalar max) noexcept
	{
		return (min <= v) && (v <= max);
	}

	SIV3D_CONCEPT_NONSCALAR_
	inline constexpr bool InRange(const NonScalar& v, const NonScalar& min, const NonScalar& max) noexcept(noexcept(v < min))
	{
		return (min <= v) && (v <= max);
	}

	//////////////////////////////////////////////////
	//
	//	InOpenRange
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_SCALAR_
	inline constexpr bool InOpenRange(const Scalar v, const Scalar min, const Scalar max) noexcept
	{
		return (min < v) && (v < max);
	}

	SIV3D_CONCEPT_NONSCALAR_
	inline constexpr bool InOpenRange(const NonScalar& v, const NonScalar& min, const NonScalar& max) noexcept(noexcept(v < min))
	{
		return (min < v) && (v < max);
	}

	//////////////////////////////////////////////////
	//
	//	AbsDiff
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr auto AbsDiff(const Arithmetic a, const Arithmetic b) noexcept
	{
		if constexpr (std::is_integral_v<Arithmetic>)
		{
			using U = std::make_unsigned_t<Arithmetic>;
			return (a > b) ? (static_cast<U>(a) - static_cast<U>(b))
				: (static_cast<U>(b) - static_cast<U>(a));
		}
		else
		{
			return detail::Abs_impl{}(a - b);
		}
	}

	//////////////////////////////////////////////////
	//
	//	Utility
	//
	//////////////////////////////////////////////////

	template <class Container, class Pred>
	inline void Erase_if(Container& c, Pred pred)
	{
		c.erase(std::remove_if(std::begin(c), std::end(c), pred), std::end(c));
	}

	template <class Container, class Pred>
	inline void EraseNodes_if(Container& c, Pred pred)
	{
		auto first = c.begin();
		const auto last = c.end();
		while (first != last)
		{
			if (pred(*first))
			{
				first = c.erase(first);
			}
			else
			{
				++first;
			}
		}
	}

	template <class T, class U>
	[[nodiscard]]
	inline constexpr bool CmpEqual(const T lhs, const U rhs) noexcept
	{
		if constexpr (std::is_signed_v<T> == std::is_signed_v<U>)
		{
			return (lhs == rhs);
		}
		else if constexpr (std::is_signed_v<U>)
		{
			return (lhs == static_cast<std::make_unsigned_t<U>>(rhs)) && (0 <= rhs);
		}
		else
		{
			return (static_cast<std::make_unsigned_t<T>>(lhs) == rhs) && (0 <= lhs);
		}
	}

	template <class T, class U>
	[[nodiscard]]
	inline constexpr bool CmpNotEqual(const T lhs, const U rhs) noexcept
	{
		return (not CmpEqual(lhs, rhs));
	}

	template <class T, class U>
	[[nodiscard]]
	inline constexpr bool CmpLess(const T lhs, const U rhs) noexcept
	{
		if constexpr (std::is_signed_v<T> == std::is_signed_v<U>)
		{
			return (lhs < rhs);
		}
		else if constexpr (std::is_signed_v<U>)
		{
			return (0 < rhs) && (lhs < static_cast<std::make_unsigned_t<U>>(rhs));
		}
		else
		{
			return (lhs < 0) || (static_cast<std::make_unsigned_t<T>>(lhs) < rhs);
		}
	}
}
