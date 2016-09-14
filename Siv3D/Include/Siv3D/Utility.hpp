//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <initializer_list>
# include <algorithm>
# include <cassert>
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// 2 つの値のうち大きい方の値を返します。 | Returns the greater of the two.
	/// </summary>
	/// <param name="a">
	/// 比較する値 | an argument
	/// </param>
	/// <param name="b">
	/// 比較する値 | another argument
	/// </param>
	/// <returns>
	/// 2 つの値のうち大きい方の値。等しい場合は a | The greater of a and b. If they are equivalent, returns a
	/// </returns>
	template <class Type>
	inline constexpr const Type& Max(const Type& a, const Type& b)
	{
		return (a < b) ? b : a;
	}

	/// <summary>
	/// 渡された初期化リストの中で最大の値を返します。 | Returns the greatest of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト | initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最大の値。複数が等しい場合はその中で最も左の値 | The greatest value in ilist. If several values are equivalent to the greatest, returns the leftmost one
	/// </returns>
	template <class Type>
	inline S3D_CONSTEXPR_CPP14 Type Max(std::initializer_list<Type> ilist)
	{
		return *std::max_element(ilist.begin(), ilist.end());
	}

	/// <summary>
	/// 2 つの値のうち小さい方の値を返します。 | Returns the lesser of the two.
	/// </summary>
	/// <param name="a">
	/// 比較する値 | an argument
	/// </param>
	/// <param name="b">
	/// 比較する値 | another argument
	/// </param>
	/// <returns>
	/// 2 つの値のうち小さい方の値。等しい場合は a | The greater of a and b. If they are equivalent, returns a
	/// </returns>
	template <class Type>
	inline constexpr const Type& Min(const Type& a, const Type& b)
	{
		return (b < a) ? b : a;
	}

	/// <summary>
	/// 渡された初期化リストの中で最小の値を返します。 | Returns the least of the values in initializer list.
	/// </summary>
	/// <param name="ilist">
	/// 比較する値の初期化リスト | initializer list with the values to compare 
	/// </param>
	/// <returns>
	/// 初期化リストの中で最小大の値。複数が等しい場合はその中で最も左の値 | The least value in ilist. If several values are equivalent to the least, returns the leftmost one
	/// </returns>
	template <class Type>
	inline S3D_CONSTEXPR_CPP14 Type Min(std::initializer_list<Type> ilist)
	{
		return *std::min_element(ilist.begin(), ilist.end());
	}

	/// <summary>
	/// 最小値と最大値の範囲にクランプした値を返します。
	/// </summary>
	/// <param name="x">
	/// クランプする値
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// </param>
	/// <returns>
	/// x をクランプした値
	/// </returns>
	template <class Type>
	inline constexpr const Type& Clamp(const Type& x, const Type& min, const Type& max)
	{
		return (x < min) ? min : ((max < x) ? max : x);
	}

	/// <summary>
	/// 値が範囲内にあるかを返します。
	/// </summary>
	/// <param name="x">
	/// 調べる値
	/// </param>
	/// <param name="min">
	/// 範囲の最小値
	/// </param>
	/// <param name="max">
	/// 範囲の最大値
	/// </param>
	/// <returns>
	/// 範囲内にある場合 true, それ以外の場合は false
	/// </returns>
	template <class Type>
	inline constexpr bool InRange(const Type& x, const Type& min, const Type& max)
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
	template <class Container, class Fty>
	inline void Erase_if(Container& c, Fty f)
	{
		c.erase(std::remove_if(std::begin(c), std::end(c), f), std::end(c));
	}

	/// <summary>
	/// コンテナから指定した値の要素を削除します。
	/// </summary>
	/// <param name="c">
	/// コンテナ
	/// </param>
	/// <param name="val">
	/// 削除する要素の値
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	template <class Container, class Type>
	inline void Erase(Container& c, const Type& val)
	{
		c.erase(std::remove(std::begin(c), std::end(c), val), std::end(c));
	}

	/// <summary>
	/// コンテナのすべての要素が条件を満たすかを返します。
	/// </summary>
	/// <param name="c">
	/// コンテナ
	/// </param>
	/// <param name="pred">
	/// 条件
	/// </param>
	/// <returns>
	/// すべての要素が条件を満たす場合 true, それ以外の場合は false
	/// </returns>
	template <class Container, class Fty>
	inline bool AllOf(const Container& c, Fty f)
	{
		return std::all_of(std::begin(c), std::end(c), f);
	}

	/// <summary>
	/// コンテナのいずれかの要素が条件を満たすかを返します。
	/// </summary>
	/// <param name="c">
	/// コンテナ
	/// </param>
	/// <param name="pred">
	/// 条件
	/// </param>
	/// <returns>
	/// いずれかの要素が条件を満たす場合 true, それ以外の場合は false
	/// </returns>
	template <class Container, class Fty>
	inline bool AnyOf(const Container& c, Fty f)
	{
		return std::any_of(std::begin(c), std::end(c), f);
	}

	/// <summary>
	/// コンテナのすべての要素が条件を満たさないかを返します。
	/// </summary>
	/// <param name="c">
	/// コンテナ
	/// </param>
	/// <param name="pred">
	/// 条件
	/// </param>
	/// <returns>
	/// すべての要素が条件を満たさない場合 true, それ以外の場合は false
	/// </returns>
	template <class Container, class Fty>
	inline bool NoneOf(const Container& c, Fty f)
	{
		return std::none_of(std::begin(c), std::end(c), f);
	}

	namespace detail
	{
		template <class PopulationIterator, class SampleIterator, class Distance, class URNG>
		inline SampleIterator Sample_impl(PopulationIterator first, PopulationIterator last, SampleIterator out, Distance n, URNG& rng, std::input_iterator_tag)
		{
			Distance k = 0;

			for (; first != last && k < n; ++first, ++k)
			{
				out[k] = *first;
			}

			Distance sz = k;

			for (; first != last; ++first, ++k)
			{
				Distance r = std::uniform_int_distribution<Distance>(0, k)(rng);

				if (r < sz)
				{
					out[r] = *first;
				}
			}

			return out + std::min(n, k);
		}

		template <class PopulationIterator, class SampleIterator, class Distance, class URNG>
		inline SampleIterator Sample_impl(PopulationIterator first, PopulationIterator last, SampleIterator out, Distance n, URNG& rng, std::forward_iterator_tag)
		{
			Distance unsampled_sz = std::distance(first, last);

			for (n = std::min(n, unsampled_sz); n != 0; ++first)
			{
				Distance r = std::uniform_int_distribution<Distance>(0, --unsampled_sz)(rng);

				if (r < n)
				{
					*out++ = *first;
					--n;
				}
			}

			return out;
		}

		template <class PopulationIterator, class SampleIterator, class Distance, class URNG>
		inline SampleIterator Sample_impl(PopulationIterator first, PopulationIterator last, SampleIterator out, Distance n, URNG& rng)
		{
			using PopCategory = typename std::iterator_traits<PopulationIterator>::iterator_category;
			using Difference = typename std::iterator_traits<PopulationIterator>::difference_type;
			using CommonType = typename std::common_type<Distance, Difference>::type;
			assert(n >= 0);
			return Sample_impl(first, last, out, CommonType(n), rng, PopCategory());
		}
	}

	template <class PopulationIterator, class SampleIterator, class Distance, class URNG>
	inline SampleIterator Sample(PopulationIterator first, PopulationIterator last, SampleIterator out, Distance n, URNG&& rng)
	{
		return detail::Sample_impl(first, last, out, n, rng);
	}
}
