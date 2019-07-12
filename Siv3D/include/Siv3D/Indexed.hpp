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
# include <type_traits>
# include <functional>
# include <tuple>

namespace s3d
{
	template <class Type, class It = decltype(std::begin(std::declval<Type>())), class = decltype(std::end(std::declval<Type>()))>
	inline constexpr auto IndexedRef(Type&& iterable)
	{
		// Reference: http://reedbeta.com/blog/python-like-enumerate-in-cpp17/

		struct Iterator
		{
			size_t index;
			It it;
			bool operator != (const Iterator& other) const { return it != other.it; }
			void operator ++() { ++index; ++it; }
			auto operator *() const { return std::tie(index, *it); }
		};

		struct IterableWrapper
		{
			Type iterable;
			auto begin() { return Iterator{ 0, std::begin(iterable) }; }
			auto end() { return Iterator{ 0, std::end(iterable) }; }
		};

		return IterableWrapper{ std::forward<Type>(iterable) };
	}

	template <class Type, class It = decltype(std::cbegin(std::declval<Type>())), class = decltype(std::cend(std::declval<Type>()))>
	inline constexpr auto Indexed(Type&& iterable)
	{
		return IndexedRef<Type, It>(std::forward<Type>(iterable));
	}

	template <class Type, class It = decltype(std::rbegin(std::declval<Type>())), class = decltype(std::rend(std::declval<Type>()))>
	inline constexpr auto IndexedRefReversed(Type&& iterable)
	{
		struct Iterator
		{
			size_t index;
			It it;
			bool operator != (const Iterator& other) const { return it != other.it; }
			void operator ++() { --index; ++it; }
			auto operator *() const { return std::tie(index, *it); }
		};

		struct IterableWrapper
		{
			Type iterable;
			auto begin() { return Iterator{ std::size(iterable) - 1, std::rbegin(iterable) }; }
			auto end() { return Iterator{ 0, std::rend(iterable) }; }
		};

		return IterableWrapper{ std::forward<Type>(iterable) };
	}

	template <class Type, class It = decltype(std::crbegin(std::declval<Type>())), class = decltype(std::crend(std::declval<Type>()))>
	inline constexpr auto IndexedReversed(Type&& iterable)
	{
		return IndexedRefReversed<Type, It>(std::forward<Type>(iterable));
	}
}
