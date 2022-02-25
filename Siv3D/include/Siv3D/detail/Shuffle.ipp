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
	template <class Container>
	inline void Shuffle(Container& c)
	{
		Shuffle(std::begin(c), std::end(c), GetDefaultRNG());
	}

	template <class Container, class URBG>
	inline void Shuffle(Container& c, URBG&& urbg)
	{
		Shuffle(std::begin(c), std::end(c), std::forward<URBG>(urbg));
	}

	template <class RandomIt>
	inline void Shuffle(RandomIt first, RandomIt last)
	{
		Shuffle(first, last, GetDefaultRNG());
	}

	template <class RandomIt, class URBG>
	inline void Shuffle(RandomIt first, RandomIt last, URBG&& urbg)
	{
		if (first == last)
		{
			return;
		}

		using difference_type = typename std::iterator_traits<RandomIt>::difference_type;

		for (RandomIt it = first + 1; it < last; ++it)
		{
			const uint64 n = static_cast<uint64>(it - first);
			std::iter_swap(it, first + static_cast<difference_type>(Random<uint64>(0, n, std::forward<URBG>(urbg))));
		}
	}
}
