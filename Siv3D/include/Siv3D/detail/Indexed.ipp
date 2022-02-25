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
	template <class Type, class It, class>
	inline constexpr auto IndexedRef(Type&& iterable)
	{
		// Reference: http://reedbeta.com/blog/python-like-enumerate-in-cpp17/

		struct Iterator
		{
			size_t index;
			It it;
			constexpr bool operator != (const Iterator& other) const { return it != other.it; }
			constexpr void operator ++() { ++index; ++it; }
			constexpr auto operator *() const { return std::tie(index, *it); }
		};

		struct IterableWrapper
		{
			Type iterable;
			constexpr auto begin() { return Iterator{ 0, std::begin(iterable) }; }
			constexpr auto end() { return Iterator{ 0, std::end(iterable) }; }
		};

		return IterableWrapper{ std::forward<Type>(iterable) };
	}

	template <class Type, class It, class>
	inline constexpr auto Indexed(Type&& iterable)
	{
		return IndexedRef<Type, It>(std::forward<Type>(iterable));
	}

	template <class Type, class It, class>
	inline constexpr auto ReverseIndexedRef(Type&& iterable)
	{
		struct Iterator
		{
			size_t index;
			It it;
			constexpr bool operator != (const Iterator& other) const { return it != other.it; }
			constexpr void operator ++() { --index; ++it; }
			constexpr auto operator *() const { return std::tie(index, *it); }
		};

		struct IterableWrapper
		{
			Type iterable;
			constexpr auto begin() { return Iterator{ std::size(iterable) - 1, std::rbegin(iterable) }; }
			constexpr auto end() { return Iterator{ 0, std::rend(iterable) }; }
		};

		return IterableWrapper{ std::forward<Type>(iterable) };
	}

	template <class Type, class It, class>
	inline constexpr auto ReverseIndexed(Type&& iterable)
	{
		return ReverseIndexedRef<Type, It>(std::forward<Type>(iterable));
	}
}
