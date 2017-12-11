//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "SFMT.hpp"
# include "MersenneTwister.hpp"

namespace s3d
{
	using DefaultRNGType = SFMT19937_64;

	[[nodiscard]] inline DefaultRNGType& GetDefaultRNG()
	{
		static thread_local DefaultRNGType rng;
		return rng;
	}

	inline void Reseed(const DefaultRNGType::result_type seed)
	{
		GetDefaultRNG().seed(seed);
	}

	inline void Reseed(const std::array<DefaultRNGType::result_type, 8>& seeds)
	{
		GetDefaultRNG().seed(seeds);
	}
}
