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
# include <functional>
# include <iterator>
# include <tuple>
# include <type_traits>

namespace s3d
{
	template <class Type, class It = decltype(std::begin(std::declval<Type>())), class = decltype(std::end(std::declval<Type>()))>
	[[nodiscard]]
	inline constexpr auto IndexedRef(Type&& iterable);

	/// @brief インデックスと組で各要素にアクセスできるループを作成するユーティリティ関数 
	/// @tparam Type 
	/// @tparam It 
	/// @tparam  
	/// @param iterable 
	/// @return 
	template <class Type, class It = decltype(std::cbegin(std::declval<Type>())), class = decltype(std::cend(std::declval<Type>()))>
	[[nodiscard]]
	inline constexpr auto Indexed(Type&& iterable);

	template <class Type, class It = decltype(std::rbegin(std::declval<Type>())), class = decltype(std::rend(std::declval<Type>()))>
	[[nodiscard]]
	inline constexpr auto ReverseIndexedRef(Type&& iterable);

	template <class Type, class It = decltype(std::crbegin(std::declval<Type>())), class = decltype(std::crend(std::declval<Type>()))>
	[[nodiscard]]
	inline constexpr auto ReverseIndexed(Type&& iterable);
}

# include "detail/Indexed.ipp"
