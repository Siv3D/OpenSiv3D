//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>*>
# endif
	inline constexpr Type Max(const Type a, const Type b) noexcept
	{
		return (a < b) ? b : a;
	}

# if __cpp_lib_concepts
	template <class Type>
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

# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>*>
# endif
	inline constexpr Type Min(const Type a, const Type b) noexcept
	{
		return (b < a) ? b : a;
	}

# if __cpp_lib_concepts
	template <class Type>
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

# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>*>
# endif
	inline constexpr Type Clamp(const Type v, const Type min, const Type max) noexcept
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
	template <class Type>
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

# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>*>
# endif
	inline constexpr bool InRange(const Type v, const Type min, const Type max) noexcept
	{
		return (min <= v) && (v <= max);
	}

# if __cpp_lib_concepts
	template <class Type>
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

# if __cpp_lib_concepts
	template <Concept::Scalar Type>
# else
	template <class Type, std::enable_if_t<std::is_scalar_v<Type>>*>
# endif
	inline constexpr bool InOpenRange(const Type v, const Type min, const Type max) noexcept
	{
		return (min < v) && (v < max);
	}

# if __cpp_lib_concepts
	template <class Type>
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
}
