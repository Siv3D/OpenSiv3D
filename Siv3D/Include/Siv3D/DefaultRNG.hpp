//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "MersenneTwister.hpp"

namespace s3d
{
	using DefaultRNGType = MT11213b;

	inline DefaultRNGType& GetDefaultRNG()
	{
		static thread_local DefaultRNGType rng;
		return rng;
	}

	inline void Reseed(DefaultRNGType::result_type seed)
	{
		GetDefaultRNG().seed(seed);
	}

	inline void Reseed(const std::array<DefaultRNGType::result_type, 8>& seeds)
	{
		GetDefaultRNG().seed(seeds);
	}
}
