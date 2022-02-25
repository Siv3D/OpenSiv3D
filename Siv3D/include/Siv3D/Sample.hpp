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
# include "Common.hpp"
# include "Array.hpp"
# include "Random.hpp"

namespace s3d
{
	/// @brief 指定した範囲から 1 つの要素をランダムに返します。
	/// @tparam Iterator イテレータの型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param begin 範囲の開始位置を指すイテレータ
	/// @param end 範囲の終端位置を指すイテレータ
	/// @param urbg 乱数エンジン
	/// @return 指定した範囲内のランダムな要素 1 つ
	template <class Iterator, class URBG>
	[[nodiscard]]
	inline auto Sample(Iterator begin, Iterator end, URBG&& urbg);

	/// @brief 指定した範囲から 1 つの要素をランダムに返します。
	/// @tparam Iterator イテレータの型
	/// @param begin 範囲の開始位置を指すイテレータ
	/// @param end 範囲の終端位置を指すイテレータ
	/// @return 指定した範囲内のランダムな要素 1 つ
	template <class Iterator>
	[[nodiscard]]
	inline auto Sample(Iterator begin, Iterator end);

	/// @brief 範囲から指定した個数の要素を重複無くランダムに選択して返します。
	/// @tparam Iterator イテレータの型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param n 取得する要素数
	/// @param begin 範囲の開始位置を指すイテレータ
	/// @param end 範囲の終端位置を指すイテレータ
	/// @param urbg 乱数エンジン
	/// @remark n が範囲内に存在する要素数を超える場合、すべての要素を返します。
	/// @remark 戻り値に含まれる要素の順序は、範囲内に存在していたときと同じ順序です
	/// @return 範囲から選択した要素の配列
	template <class Iterator, class URBG>
	[[nodiscard]]
	inline auto Sample(size_t n, Iterator begin, Iterator end, URBG&& urbg);

	/// @brief 範囲から指定した個数の要素を重複無くランダムに選択して返します。
	/// @tparam Iterator イテレータの型
	/// @param n 取得する要素数
	/// @param begin 範囲の開始位置を指すイテレータ
	/// @param end 範囲の終端位置を指すイテレータ
	/// @remark n が範囲内に存在する要素数を超える場合、すべての要素を返します。
	/// @remark 戻り値に含まれる要素の順序は、範囲内に存在していたときと同じ順序です
	/// @return  範囲から選択した要素の配列
	template <class Iterator>
	[[nodiscard]]
	inline auto Sample(size_t n, Iterator begin, Iterator end);

	/// @brief コンテナから 1 つの要素をランダムに返します。
	/// @tparam Container コンテナの型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param c コンテナ
	/// @param urbg 乱数エンジン
	/// @return コンテナ内のランダムな要素 1 つ
	template <class Container, class URBG>
	[[nodiscard]]
	inline auto Sample(const Container& c, URBG&& urbg);

	/// @brief コンテナから 1 つの要素をランダムに返します。
	/// @tparam Container コンテナの型
	/// @param c コンテナ
	/// @return コンテナ内のランダムな要素 1 つ
	template <class Container>
	[[nodiscard]]
	inline auto Sample(const Container& c);

	/// @brief コンテナから指定した個数の要素を重複無くランダムに選択して返します。
	/// @tparam Container コンテナの型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param n 取得する要素数
	/// @param c コンテナ
	/// @param urbg 乱数エンジン
	/// @remark n が範囲内に存在する要素数を超える場合、すべての要素を返します。
	/// @remark 戻り値に含まれる要素の順序は、範囲内に存在していたときと同じ順序です
	/// @return コンテナから選択した要素の配列
	template <class Container, class URBG>
	[[nodiscard]]
	inline Array<typename Container::value_type> Sample(size_t n, const Container& c, URBG&& urbg);

	/// @brief コンテナから指定した個数の要素を重複無くランダムに選択して返します。
	/// @tparam Container コンテナの型
	/// @param n 取得する要素数
	/// @param c コンテナ
	/// @remark n が範囲内に存在する要素数を超える場合、すべての要素を返します。
	/// @remark 戻り値に含まれる要素の順序は、範囲内に存在していたときと同じ順序です
	/// @return コンテナから選択した要素の配列
	template <class Container>
	[[nodiscard]]
	inline Array<typename Container::value_type> Sample(size_t n, const Container& c);

	/// @brief initializer_list から 1 つの要素をランダムに返します。
	/// @tparam Type initializer_list の要素の型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param ilist initializer_list
	/// @param urbg 乱数エンジン
	/// @return initializer_list 内のランダムな要素 1 つ
	template <class Type, class URBG>
	[[nodiscard]]
	inline auto Sample(std::initializer_list<Type> ilist, URBG&& urbg);

	/// @brief initializer_list から 1 つの要素をランダムに返します。
	/// @tparam Type initializer_list の要素の型
	/// @param ilist initializer_list
	/// @return initializer_list 内のランダムな要素 1 つ
	template <class Type>
	[[nodiscard]]
	inline auto Sample(std::initializer_list<Type> ilist);

	/// @brief initializer_list から指定した個数の要素を重複無くランダムに選択して返します。
	/// @tparam Type initializer_list の要素の型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param n 取得する要素数
	/// @param ilist initializer_list
	/// @param urbg 乱数エンジン
	/// @remark n が initializer_list 内に存在する要素数を超える場合、すべての要素を返します。
	/// @remark 戻り値に含まれる要素の順序は、initializer_list 内に存在していたときと同じ順序です
	/// @return initializer_list から選択した要素の配列
	template <class Type, class URBG>
	[[nodiscard]]
	inline Array<Type> Sample(size_t n, std::initializer_list<Type> ilist, URBG&& urbg);

	/// @brief initializer_list から指定した個数の要素を重複無くランダムに選択して返します。
	/// @tparam Type initializer_list の要素の型
	/// @param n 取得する要素数
	/// @param ilist initializer_list
	/// @remark n が initializer_list 内に存在する要素数を超える場合、すべての要素を返します。
	/// @remark 戻り値に含まれる要素の順序は、initializer_list 内に存在していたときと同じ順序です
	/// @return initializer_list から選択した要素の配列
	template <class Type>
	[[nodiscard]]
	inline Array<Type> Sample(size_t n, std::initializer_list<Type> ilist);
}

# include "detail/Sample.ipp"
