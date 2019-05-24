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

# include <Siv3D/RNG.hpp>
# include <Siv3D/HardwareRNG.hpp>

namespace s3d
{
	Xoroshiro128Plus::Xoroshiro128Plus()
	{
		HardwareRNG rng;
		std::uniform_int_distribution<uint64> dist(Smallest<uint64>, Largest<uint64>);
		for (auto& value : s)
		{
			value = dist(rng);
		}
	}

	Xoroshiro128Plus::Xoroshiro128Plus(const uint64 seed) noexcept
	{
		this->seed(seed);
	}

	Xoroshiro128Plus::Xoroshiro128Plus(const uint64 seed0, const uint64 seed1) noexcept
	{
		this->seed(seed0, seed1);
	}

	Xoroshiro128Plus::Xoroshiro128Plus(const std::array<uint64, 2>& seeds) noexcept
	{
		this->seed(seeds);
	}

	Xoshiro256StarStar::Xoshiro256StarStar()
	{
		HardwareRNG rng;
		std::uniform_int_distribution<uint64> dist(Smallest<uint64>, Largest<uint64>);
		for (auto& value : s)
		{
			value = dist(rng);
		}
	}

	Xoshiro256StarStar::Xoshiro256StarStar(const uint64 seed) noexcept
	{
		this->seed(seed);
	}

	Xoshiro256StarStar::Xoshiro256StarStar(const uint64 seed0, const uint64 seed1, const uint64 seed2, const uint64 seed3) noexcept
	{
		this->seed(seed0, seed1, seed2, seed3);
	}

	Xoshiro256StarStar::Xoshiro256StarStar(const std::array<uint64, 4>& seeds) noexcept
	{
		this->seed(seeds);
	}
}
