//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Random.hpp>

namespace s3d
{
	DefaultRNG& GetDefaultRNG() noexcept
	{
		static thread_local DefaultRNG rng;
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
