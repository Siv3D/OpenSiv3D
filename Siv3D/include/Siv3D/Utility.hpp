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
# include <initializer_list>
# include <algorithm>
# include "PlaceHolder.hpp"

namespace s3d
{
//////////////////////////////////////////////////
//
//	Max
//
//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		class Max1_impl
		{
		private:

			const Type& x;

		public:

			constexpr Max1_impl(const Type& _x) noexcept
				: x(_x) {}

			[[nodiscard]] constexpr const Type& operator()(const Type& y) const noexcept(noexcept(x < y))
			{
				return (x < y) ? y : x;
			}
		};

		class Max2_impl
		{
		public:

			template <class Type>
			[[nodiscard]] constexpr const Type& operator()(const Type& x, const Type& y) const noexcept(noexcept(x < y))
			{
				return (x < y) ? y : x;
			}
		};
	}

	template <class Type>
	[[nodiscard]] constexpr detail::Max1_impl<Type> Max(const Type& x, PlaceHolder_t) noexcept
	{
		return detail::Max1_impl<Type>(x);
	}

	template <class Type>
	[[nodiscard]] constexpr detail::Max1_impl<Type> Max(PlaceHolder_t, const Type& y) noexcept
	{
		return detail::Max1_impl<Type>(y);
	}

	[[nodiscard]] constexpr detail::Max2_impl Max(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Max2_impl();
	}

	template <class Type>
	[[nodiscard]] inline constexpr const Type& Max(const Type& x, const Type& y) noexcept(noexcept(x < y))
	{
		return (x < y) ? y : x;
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

	namespace detail
	{
		template <class Type>
		class Min1_impl
		{
		private:

			const Type& x;

		public:

			constexpr Min1_impl(const Type& _x) noexcept
				: x(_x) {}

			[[nodiscard]] constexpr const Type& operator()(const Type& y) const noexcept(noexcept(y < x))
			{
				return (y < x) ? y : x;
			}
		};

		class Min2_impl
		{
		public:

			template <class Type>
			[[nodiscard]] constexpr const Type& operator()(const Type& x, const Type& y) const noexcept(noexcept(y < x))
			{
				return (y < x) ? y : x;
			}
		};
	}

	template <class Type>
	[[nodiscard]] constexpr detail::Min1_impl<Type> Min(const Type& x, PlaceHolder_t) noexcept
	{
		return detail::Min1_impl<Type>(x);
	}

	template <class Type>
	[[nodiscard]] constexpr detail::Min1_impl<Type> Min(PlaceHolder_t, const Type& y) noexcept
	{
		return detail::Min1_impl<Type>(y);
	}

	[[nodiscard]] constexpr detail::Min2_impl Min(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Min2_impl();
	}

	template <class Type>
	[[nodiscard]] inline constexpr const Type& Min(const Type& x, const Type& y) noexcept(noexcept(y < x))
	{
		return (y < x) ? y : x;
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

	namespace detail
	{
		template <class Type>
		class Clamp_impl
		{
		private:

			const Type& min;

			const Type& max;

		public:

			constexpr Clamp_impl(const Type& _min, const Type& _max) noexcept
				: min(_min)
				, max(_max) {}

			[[nodiscard]] constexpr const Type& operator()(const Type& x) const noexcept(noexcept(x < min))
			{
				return (x < min) ? min : ((max < x) ? max : x);
			}
		};
	}

	template <class Type>
	[[nodiscard]] constexpr detail::Clamp_impl<Type> Clamp(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::Clamp_impl<Type>(min, max);
	}

	template <class Type>
	[[nodiscard]] inline constexpr const Type& Clamp(const Type& x, const Type& min, const Type& max) noexcept(noexcept(x < min))
	{
		return (x < min) ? min : ((max < x) ? max : x);
	}


//////////////////////////////////////////////////
//
//	InRange
//
//////////////////////////////////////////////////

	namespace detail
	{
		template <class Type>
		class InRange_impl
		{
		private:

			const Type& min;

			const Type& max;

		public:

			constexpr InRange_impl(const Type& _min, const Type& _max) noexcept
				: min(_min)
				, max(_max) {}

			[[nodiscard]] constexpr const Type& operator()(const Type& x) const noexcept(noexcept(x < min))
			{
				return (min <= x) && (x <= max);
			}
		};
	}

	template <class Type>
	[[nodiscard]] inline constexpr bool InRange(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::InRange_impl<Type>(min, max);
	}

	template <class Type>
	[[nodiscard]] inline constexpr bool InRange(const Type& x, const Type& min, const Type& max) noexcept(noexcept(x < min))
	{
		return (min <= x) && (x <= max);
	}
}
