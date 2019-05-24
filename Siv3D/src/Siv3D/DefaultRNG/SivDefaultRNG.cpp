//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/DefaultRNG.hpp>

namespace s3d
{
	DefaultRNGType& GetDefaultRNG()
	{
		static thread_local DefaultRNGType rng;
		return rng;
	}

	void Reseed(const uint64 seed)
	{
		GetDefaultRNG().seed(seed);
	}

	void Reseed(const std::array<uint64, 16>& seeds)
	{
		GetDefaultRNG().seed(seeds);
	}
}
