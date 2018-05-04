//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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

	inline void Reseed(const uint64 seed)
	{
		GetDefaultRNG().seed(seed);
	}

	inline void Reseed(const std::array<uint64, 16>& seeds)
	{
		GetDefaultRNG().seed(seeds);
	}
}
