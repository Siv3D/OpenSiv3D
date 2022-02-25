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

namespace s3d
{
	inline constexpr HardwareRNG::result_type HardwareRNG::min() noexcept
	{
		return engine_type::min();
	}

	inline constexpr HardwareRNG::result_type HardwareRNG::max() noexcept
	{
		return engine_type::max();
	}

	inline HardwareRNG::result_type HardwareRNG::operator()()
	{
		return m_engine();
	}

	template <size_t N>
	inline std::array<HardwareRNG::result_type, N> HardwareRNG::generateSeeds() noexcept
	{
		std::array<result_type, N> seeds;

		for (auto& seed : seeds)
		{
			seed = m_engine();
		}

		return seeds;
	}
}
