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
# include "Random.hpp"

namespace s3d
{
	/// @brief コンテナ内の要素をランダムにシャッフルします。
	/// @tparam Container コンテナの型
	/// @param c コンテナ
	template <class Container>
	inline void Shuffle(Container& c);

	/// @brief コンテナ内の要素をランダムにシャッフルします。
	/// @tparam Container コンテナの型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param c コンテナ
	/// @param urbg 乱数エンジン
	template <class Container, class URBG>
	inline void Shuffle(Container& c, URBG&& urbg);

	/// @brief 指定した範囲の要素をランダムにシャッフルします。
	/// @tparam RandomIt イテレータの型
	/// @param first 範囲の開始位置を指すイテレータ
	/// @param last 範囲の終端位置を指すイテレータ
	template <class RandomIt>
	inline void Shuffle(RandomIt first, RandomIt last);

	/// @brief 指定した範囲の要素をランダムにシャッフルします。
	/// @tparam RandomIt イテレータの型
	/// @tparam URBG 使用する乱数エンジンの型
	/// @param first 範囲の開始位置を指すイテレータ
	/// @param last 範囲の終端位置を指すイテレータ
	/// @param urbg 乱数エンジン
	template <class RandomIt, class URBG>
	inline void Shuffle(RandomIt first, RandomIt last, URBG&& urbg);
}

# include "detail/Shuffle.ipp"
