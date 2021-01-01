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
		std::shuffle(std::begin(c), std::end(c), GetDefaultRNG());
	}

	template <class Container, class URBG>
	inline void Shuffle(Container& c, URBG&& urbg)
	{
		std::shuffle(std::begin(c), std::end(c), std::forward<URBG>(urbg));
	}

	template <class RandomIt>
	inline void Shuffle(RandomIt first, RandomIt last)
	{
		std::shuffle(first, last, GetDefaultRNG());
	}

	template <class RandomIt, class URBG>
	inline void Shuffle(RandomIt first, RandomIt last, URBG&& urbg)
	{
		std::shuffle(first, last, std::forward<URBG>(urbg));
	}
}
