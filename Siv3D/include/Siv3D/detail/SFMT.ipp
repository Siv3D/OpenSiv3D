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
