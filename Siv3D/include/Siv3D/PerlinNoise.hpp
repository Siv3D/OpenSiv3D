//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include "Common.hpp"
# include "Concepts.hpp"
# include "PointVector.hpp"
# include "Random.hpp"

namespace s3d
{
	template <class Float>
	class BasicPerlinNoise
	{
	public:

		using state_type = std::array<uint8, 256>;
		using value_type = Float;

		SIV3D_NODISCARD_CXX20
		explicit constexpr BasicPerlinNoise() noexcept;

		SIV3D_NODISCARD_CXX20
		explicit BasicPerlinNoise(uint64 seed);

		SIV3D_CONCEPT_URBG
		SIV3D_NODISCARD_CXX20
		explicit BasicPerlinNoise(URBG&& urbg);

		void reseed(uint64 seed);

		SIV3D_CONCEPT_URBG
		void reseed(URBG&& urbg);

		[[nodiscard]]
		value_type noise1D(value_type x) const noexcept;

		[[nodiscard]]
		value_type noise2D(value_type x, value_type y) const noexcept;

		[[nodiscard]]
		value_type noise3D(value_type x, value_type y, value_type z) const noexcept;

		[[nodiscard]]
		constexpr const state_type& serialize() const noexcept;

		constexpr void deserialize(const state_type& state) noexcept;

	private:

		state_type m_perm;

		static constexpr Float Fade(Float t) noexcept;

		static constexpr Float Lerp(Float a, Float b, Float t) noexcept;

		static constexpr Float Grad(uint8 hash, Float x, Float y, Float z) noexcept;
	};

	using PerlinNoiseF	= BasicPerlinNoise<float>;
	using PerlinNoise	= BasicPerlinNoise<double>;
}

# include "detail/PerlinNoise.ipp"
