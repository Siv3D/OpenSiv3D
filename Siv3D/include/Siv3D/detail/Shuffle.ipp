//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
		auto it = first;

		for (difference_type targetIndex = 1; ++it != last; ++targetIndex)
		{
			difference_type offset
				= Random(static_cast<difference_type>(targetIndex), std::forward<URBG>(urbg));

			if (offset != targetIndex)
			{
				std::iter_swap(it, first + offset);
			}
		}
	}
}
