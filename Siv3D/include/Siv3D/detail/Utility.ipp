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

namespace s3d
{
	//////////////////////////////////////////////////
	//
	//	Max
	//
	//////////////////////////////////////////////////

	template <class Type>
	inline constexpr auto Max(const Type& a, PlaceHolder_t) noexcept
	{
		return detail::Max1_impl<Type>(a);
	}

	template <class Type>
	inline constexpr auto Max(PlaceHolder_t, const Type& b) noexcept
	{
		return detail::Max1_impl<Type>(b);
	}

	inline constexpr auto Max(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Max2_impl{};
	}

	SIV3D_CONCEPT_SCALAR_
	inline constexpr Scalar Max(const Scalar a, const Scalar b) noexcept
	{
		return (a < b) ? b : a;
	}

# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>*>
# endif
	inline constexpr const Type& Max(const Type& a, const Type& b) noexcept(noexcept(a < b))
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

	template <class Type>
	inline constexpr auto Min(const Type& a, PlaceHolder_t) noexcept
	{
		return detail::Min1_impl<Type>(a);
	}

	template <class Type>
	inline constexpr auto Min(PlaceHolder_t, const Type& b) noexcept
	{
		return detail::Min1_impl<Type>(b);
	}

	inline constexpr auto Min(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Min2_impl{};
	}

	SIV3D_CONCEPT_SCALAR_
	inline constexpr Scalar Min(const Scalar a, const Scalar b) noexcept
	{
		return (b < a) ? b : a;
	}

# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>*>
# endif
	inline constexpr const Type& Min(const Type& a, const Type& b) noexcept(noexcept(b < a))
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

	template <class Type>
	constexpr auto Clamp(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::Clamp_impl<Type>(min, max);
	}

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

# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>*>
# endif
	inline constexpr const Type& Clamp(const Type& v, const Type& min, const Type& max) noexcept(noexcept(max < v) && noexcept(v < min))
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

	template <class Type>
	inline constexpr auto InRange(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::InRange_impl<Type>(min, max);
	}

	SIV3D_CONCEPT_SCALAR_
	inline constexpr bool InRange(const Scalar v, const Scalar min, const Scalar max) noexcept
	{
		return (min <= v) && (v <= max);
	}

# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>*>
# endif
	inline constexpr bool InRange(const Type& v, const Type& min, const Type& max) noexcept(noexcept(v < min))
	{
		return (min <= v) && (v <= max);
	}

	//////////////////////////////////////////////////
	//
	//	InOpenRange
	//
	//////////////////////////////////////////////////

	template <class Type>
	inline constexpr auto InOpenRange(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::InOpenRange_impl<Type>(min, max);
	}

	SIV3D_CONCEPT_SCALAR_
	inline constexpr bool InOpenRange(const Scalar v, const Scalar min, const Scalar max) noexcept
	{
		return (min < v) && (v < max);
	}

# if __cpp_lib_concepts
	template <class Type> requires (not std::is_scalar_v<Type>)
# else
	template <class Type, std::enable_if_t<not std::is_scalar_v<Type>>*>
# endif
	inline constexpr bool InOpenRange(const Type& v, const Type& min, const Type& max) noexcept(noexcept(v < min))
	{
		return (min < v) && (v < max);
	}

	//////////////////////////////////////////////////
	//
	//	AbsDiff
	//
	//////////////////////////////////////////////////

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr auto AbsDiff(const Arithmetic a, PlaceHolder_t) noexcept
	{
		return detail::AbsDiff1_impl<Arithmetic>(a);
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr auto AbsDiff(PlaceHolder_t, const Arithmetic b) noexcept
	{
		return detail::AbsDiff1_impl<Arithmetic>(b);
	}

	inline constexpr auto AbsDiff(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::AbsDiff2_impl{};
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline constexpr auto AbsDiff(const Arithmetic a, const Arithmetic b) noexcept
	{
		return detail::AbsDiff2_impl{}(a, b);
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
