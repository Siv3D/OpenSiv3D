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
	template <class Iterator, class URBG>
	inline auto Sample(Iterator begin, Iterator end, URBG&& urbg)
	{
		assert(begin != end);
		
		std::advance(begin, Random<uint64>(std::distance(begin, end) - 1, std::forward<URBG>(urbg)));
		return *begin;
	}

	template <class Iterator>
	inline auto Sample(Iterator begin, Iterator end)
	{
		return Sample(begin, end, GetDefaultRNG());
	}

	template <class Iterator, class URBG>
	inline auto Sample(size_t n, Iterator begin, Iterator end, URBG&& urbg)
	{
		Array<typename std::iterator_traits<Iterator>::value_type> result;
		result.reserve(std::min<size_t>(n, std::distance(begin, end)));

		std::sample(begin, end, std::back_inserter(result), n, std::forward<URBG>(urbg));
		return result;
	}

	template <class Iterator>
	inline auto Sample(const size_t n, Iterator begin, Iterator end)
	{
		return Sample(n, begin, end, GetDefaultRNG());
	}

	template <class Container, class URBG>
	inline auto Sample(const Container& c, URBG&& urbg)
	{
		assert(std::size(c) != 0);

		auto it = std::begin(c);
		std::advance(it, Random<uint64>(std::size(c) - 1, std::forward<URBG>(urbg)));
		return *it;
	}

	template <class Container>
	inline auto Sample(const Container& c)
	{
		return Sample(c, GetDefaultRNG());
	}

	template <class Container, class URBG>
	inline Array<typename Container::value_type> Sample(size_t n, const Container& c, URBG&& urbg)
	{
		Array<typename Container::value_type> result;
		result.reserve(Min(n, std::size(c)));

		std::sample(std::begin(c), std::end(c), std::back_inserter(result), n, std::forward<URBG>(urbg));
		return result;
	}

	template <class Container>
	inline Array<typename Container::value_type> Sample(const size_t n, const Container& c)
	{
		return Sample(n, c, GetDefaultRNG());
	}

	template <class Type, class URBG>
	inline auto Sample(std::initializer_list<Type> ilist, URBG&& urbg)
	{
		assert(ilist.size() != 0);

		return *(ilist.begin() + Random<uint64>(ilist.size() - 1, std::forward<URBG>(urbg)));
	}

	template <class Type>
	inline auto Sample(std::initializer_list<Type> ilist)
	{
		return Sample(ilist, GetDefaultRNG());
	}

	template <class Type, class URBG>
	inline Array<Type> Sample(size_t n, std::initializer_list<Type> ilist, URBG&& urbg)
	{
		Array<Type> result;
		result.reserve(Min(n, ilist.size()));

		std::sample(ilist.begin(), ilist.end(), std::back_inserter(result), n, std::forward<URBG>(urbg));
		return result;
	}

	template <class Type>
	inline Array<Type> Sample(const size_t n, std::initializer_list<Type> ilist)
	{
		return Sample(n, ilist, GetDefaultRNG());
	}
}
