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
# include <random>
# include "Fwd.hpp"
# include "Distribution.hpp"
# include "MersenneTwister.hpp"

namespace s3d
{
	// 仮の実装
	inline auto& GetDefaultRBG()
	{
        static std::mt19937_64 rng{ std::random_device{}() };
        return rng;
	}

	using DefaultRNGType = MT11213b;

	inline DefaultRNGType& DefaultRNG()
	{
		static thread_local DefaultRNGType rng;

		return rng;
	}

	inline void Reseed(uint32 seed)
	{
		DefaultRNG().seed(seed);
	}
}
