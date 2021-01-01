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
# include "Common.hpp"
# include "Random.hpp"

namespace s3d
{
	/// @brief 
	/// @tparam Container 
	/// @param c 
	template <class Container>
	inline void Shuffle(Container& c);

	template <class Container, class URBG>
	inline void Shuffle(Container& c, URBG&& urbg);

	/// @brief 
	/// @tparam RandomIt 
	/// @param first 
	/// @param last 
	template <class RandomIt>
	inline void Shuffle(RandomIt first, RandomIt last);

	template <class RandomIt, class URBG>
	inline void Shuffle(RandomIt first, RandomIt last, URBG&& urbg);
}

# include "detail/Shuffle.ipp"
