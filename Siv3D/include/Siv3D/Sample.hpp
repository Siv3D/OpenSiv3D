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
# include "Random.hpp"

namespace s3d
{
	/// <summary>
	/// イテレータの範囲からランダムに値を選択します。
	/// </summary>
	/// <param name="begin">
	/// 開始位置
	/// </param>
	/// <param name="end">
	/// 終了位置
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// イテレータの範囲からランダムに選択された値
	/// </returns>
	template <class Iterator>
	inline auto Sample(Iterator begin, Iterator end)
	{
		assert(begin != end);
		
		std::advance(begin, Random(std::distance(begin, end) - 1));
		
		return *begin;
	}

	/// <summary>
	/// イテレータの範囲からランダムにいくつかの値を選択します。
	/// </summary>
	/// <param name="n">
	/// 個数
	/// </param>
	/// <param name="begin">
	/// 開始位置
	/// </param>
	/// <param name="end">
	/// 終了位置
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// イテレータの範囲からランダムに選択された値
	/// </returns>
	template <class Iterator>
	inline auto Sample(size_t n, Iterator begin, Iterator end)
	{
		Array<typename std::iterator_traits<Iterator>::value_type> result;

		result.reserve(std::min(n, std::distance(begin, end)));

		std::sample(begin(), end(), std::back_inserter(result), n, GetDefaultRNG());

		return result;
	}

	/// <summary>
	/// コンテナの中からランダムに値を選択します。
	/// </summary>
	/// <param name="c">
	/// コンテナ
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// コンテナの中からランダムに選択された値
	/// </returns>
	template <class Container>
	inline auto Sample(const Container& c)
	{
		assert(std::size(c) != 0);

		auto it = std::begin(c);

		std::advance(it, Random(std::size(c) - 1));

		return *it;
	}

	template <class Container>
	inline auto Sample(size_t n, const Container& c)
	{
		Array<typename Container::value_type> result;

		result.reserve(std::min(n, std::size(c)));

		std::sample(std::begin(c), std::end(c), std::back_inserter(result), n, GetDefaultRNG());

		return result;
	}

	/// <summary>
	/// リストの中からランダムに値を選択します。
	/// </summary>
	/// <param name="ilist">
	/// 値のリスト
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// リストの中からランダムに選択された値
	/// </returns>
	template <class Type>
	inline auto Sample(std::initializer_list<Type> ilist)
	{
		assert(ilist.size() != 0);

		return *(ilist.begin() + Random(ilist.size() - 1));
	}

	template <class Type>
	inline auto Sample(size_t n, std::initializer_list<Type> ilist)
	{
		Array<Type> result;

		result.reserve(std::min(n, ilist.size()));

		std::sample(ilist.begin(), ilist.end(), std::back_inserter(result), n, GetDefaultRNG());

		return result;
	}
}
