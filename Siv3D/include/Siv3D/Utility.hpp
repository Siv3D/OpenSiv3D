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
	[[nodiscard]] constexpr auto Max(const Type& x, PlaceHolder_t) noexcept
	{
		return detail::Max1_impl<Type>(x);
	}

	template <class Type>
	[[nodiscard]] constexpr auto Max(PlaceHolder_t, const Type& y) noexcept
	{
		return detail::Max1_impl<Type>(y);
	}

	[[nodiscard]] constexpr auto Max(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Max2_impl();
	}

	/// <summary>
	/// 2 つの値のうち大きい方の値を返します。
	/// Returns the greater of the two.
	/// </summary>
	/// <param name="x">
	/// 比較する値
	/// A value to compare
	/// </param>
	/// <param name="y">
	/// 比較する値
	/// Another value to compare
	/// </param>
	/// <returns>
	/// 2 つの値のうち大きい方の値。等しい場合は x
	/// The greater of x and y. If they are equivalent, returns x
	/// </returns>
	template <class Type>
	[[nodiscard]] inline constexpr const Type& Max(const Type& x, const Type& y) noexcept(noexcept(x < y))
	{
		return (x < y) ? y : x;
	}

	/// <summary>
	/// 渡された初期化リストの中で最大の値を返します。
	/// Returns the greatest of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト
	/// Initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最大の値。複数が等しい場合はその中で最も左の値
	/// The greatest value in ilist. If several values are equivalent to the greatest, returns the leftmost one
	/// </returns>
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
	[[nodiscard]] constexpr auto Min(const Type& x, PlaceHolder_t) noexcept
	{
		return detail::Min1_impl<Type>(x);
	}

	template <class Type>
	[[nodiscard]] constexpr auto Min(PlaceHolder_t, const Type& y) noexcept
	{
		return detail::Min1_impl<Type>(y);
	}

	[[nodiscard]] constexpr detail::Min2_impl Min(PlaceHolder_t, PlaceHolder_t) noexcept
	{
		return detail::Min2_impl();
	}

	/// <summary>
	/// 2 つの値のうち小さい方の値を返します。
	/// Returns the lesser of the two.
	/// </summary>
	/// <param name="x">
	/// 比較する値
	/// A value to compare
	/// </param>
	/// <param name="y">
	/// 比較する値
	/// Another value to compare
	/// </param>
	/// <returns>
	/// 2 つの値のうち小さい方の値。等しい場合は x
	/// The greater of x and y. If they are equivalent, returns x
	/// </returns>
	template <class Type>
	[[nodiscard]] inline constexpr const Type& Min(const Type& x, const Type& y) noexcept(noexcept(y < x))
	{
		return (y < x) ? y : x;
	}

	/// <summary>
	/// 渡された初期化リストの中で最小の値を返します。
	/// Returns the least of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト
	/// Initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最小大の値。複数が等しい場合はその中で最も左の値
	/// The least value in ilist. If several values are equivalent to the least, returns the leftmost one
	/// </returns>
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

			[[nodiscard]] constexpr const Type& operator()(const Type& x) const noexcept(noexcept(x < min) && noexcept(max < x))
			{
				return (x < min) ? min : ((max < x) ? max : x);
			}
		};
	}

	template <class Type>
	[[nodiscard]] constexpr auto Clamp(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::Clamp_impl<Type>(min, max);
	}

	/// <summary>
	/// 最小値と最大値の範囲にクランプした値を返します。
	/// Clamps the value to the specified minimum and maximum range
	/// </summary>
	/// <param name="x">
	/// クランプする値
	/// A value to clamp
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// x をクランプした値
	/// The clamped value for the x
	/// </returns>
	template <class Type>
	[[nodiscard]] inline constexpr const Type& Clamp(const Type& x, const Type& min, const Type& max) noexcept(noexcept(x < min) && noexcept(max < x))
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

			[[nodiscard]] constexpr bool operator()(const Type& x) const noexcept(noexcept(min <= x) && noexcept(x <= max))
			{
				return (min <= x) && (x <= max);
			}
		};
	}

	template <class Type>
	[[nodiscard]] inline constexpr auto InRange(PlaceHolder_t, const Type& min, const Type& max) noexcept
	{
		return detail::InRange_impl<Type>(min, max);
	}

	/// <summary>
	/// 値が範囲内にあるかを返します。
	/// Checks if the value is within the specified minimum and maximum range
	/// </summary>
	/// <param name="x">
	/// 調べる値
	/// A value
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// The specified minimum range
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// The specified maximum range
	/// </param>
	/// <returns>
	/// 範囲内にある場合 true, それ以外の場合は false
	/// True if the value is within the range, false otherwise
	/// </returns>
	template <class Type>
	[[nodiscard]] inline constexpr bool InRange(const Type& x, const Type& min, const Type& max) noexcept(noexcept(x < min))
	{
		return (min <= x) && (x <= max);
	}

	/// <summary>
	/// コンテナから条件を満たす要素を削除します。
	/// </summary>
	/// <param name="c">
	/// コンテナ
	/// </param>
	/// <param name="pred">
	/// 条件
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
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
