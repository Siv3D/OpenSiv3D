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

# pragma once

namespace s3d::PRNG
{
	inline SFMT19937_64::SFMT19937_64()
	{
		HardwareRNG rng;

		uint32 keys[SeedSequencCount * 2];

		for (auto& key : keys)
		{
			key = rng();
		}

		detail::sfmt_init_by_array(&m_state, keys, static_cast<int32>(SeedSequencCount * 2));
	}

	inline SFMT19937_64::SFMT19937_64(const uint64 seed) noexcept
	{
		this->seed(seed);
	}

	inline SFMT19937_64::SFMT19937_64(const std::array<uint64, SeedSequencCount>& seeds) noexcept
	{
		this->seed(seeds);
	}

	inline void SFMT19937_64::seed(const uint64 seed) noexcept
	{
		XoshiroCpp::SplitMix64 splitmix64(seed);

		uint32 keys[SeedSequencCount * 2];

		for (auto& key : keys)
		{
			key = static_cast<uint32>(splitmix64());
		}

		detail::sfmt_init_by_array(&m_state, keys, static_cast<int32>(SeedSequencCount * 2));
	}

	inline void SFMT19937_64::seed(const std::array<uint64, SeedSequencCount>& seeds) noexcept
	{
		uint32 keys[SeedSequencCount * 2];

		for (size_t i = 0; i < 16; ++i)
		{
			keys[i * 2] = static_cast<uint32>(seeds[i] >> 32);
			keys[i * 2 + 1] = static_cast<uint32>(seeds[i] & 0xffFFffFF);
		}

		detail::sfmt_init_by_array(&m_state, keys, static_cast<int32>(SeedSequencCount * 2));
	}

	[[nodiscard]]
	inline constexpr SFMT19937_64::result_type SFMT19937_64::min() noexcept
	{
		return Smallest<result_type>;
	}

	[[nodiscard]]
	inline constexpr SFMT19937_64::result_type SFMT19937_64::max() noexcept
	{
		return Largest<result_type>;
	}

	inline SFMT19937_64::result_type SFMT19937_64::operator()() noexcept
	{
		return detail::sfmt_genrand_uint64(&m_state);
	}

	inline double SFMT19937_64::generateReal() noexcept
	{
		return detail::sfmt_genrand_res53(&m_state);
	}

	inline constexpr const SFMT19937_64::State_t& SFMT19937_64::serialize() const noexcept
	{
		return m_state;
	}

	inline constexpr void SFMT19937_64::deserialize(const State_t& data) noexcept
	{
		m_state = data;
	}
}
