//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <ThirdParty/Xoshiro-cpp/XoshiroCpp.hpp>
# include <Siv3D/SFMT.hpp>
# include <Siv3D/HardwareRNG.hpp>

namespace s3d::PRNG
{
	SFMT19937_64::SFMT19937_64()
	{
		HardwareRNG rng;

		uint32 keys[SeedSequencCount * 2];

		for (auto& key : keys)
		{
			key = rng();
		}

		detail::sfmt_init_by_array(&m_state, keys, static_cast<int32>(SeedSequencCount * 2));
	}

	SFMT19937_64::SFMT19937_64(const uint64 seed) noexcept
	{
		this->seed(seed);
	}

	SFMT19937_64::SFMT19937_64(const std::array<uint64, SeedSequencCount>& seeds) noexcept
	{
		this->seed(seeds);
	}

	void SFMT19937_64::seed(const uint64 seed) noexcept
	{
		XoshiroCpp::SplitMix64 splitmix64(seed);

		uint32 keys[SeedSequencCount * 2];

		for (auto& key : keys)
		{
			key = static_cast<uint32>(splitmix64());
		}

		detail::sfmt_init_by_array(&m_state, keys, static_cast<int32>(SeedSequencCount * 2));
	}

	void SFMT19937_64::seed(const std::array<uint64, SeedSequencCount>& seeds) noexcept
	{
		uint32 keys[SeedSequencCount * 2];

		for (size_t i = 0; i < 16; ++i)
		{
			keys[i * 2] = static_cast<uint32>(seeds[i] >> 32);
			keys[i * 2 + 1] = static_cast<uint32>(seeds[i] & 0xffFFffFF);
		}

		detail::sfmt_init_by_array(&m_state, keys, static_cast<int32>(SeedSequencCount * 2));
	}
}
