//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Random.hpp>

namespace s3d
{
	DefaultRNG_t& GetDefaultRNG() noexcept
	{
		static thread_local DefaultRNG_t rng;
		return rng;
	}

	void Reseed(const uint64 seed) noexcept
	{
		GetDefaultRNG().seed(seed);
	}

	void Reseed(const std::array<uint64, 16>& seeds) noexcept
	{
		GetDefaultRNG().seed(seeds);
	}

	double Random() noexcept
	{
		return GetDefaultRNG().generateReal();
	}
}
