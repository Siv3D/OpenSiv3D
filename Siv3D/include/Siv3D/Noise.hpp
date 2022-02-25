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
# include "Common.hpp"
# include "Concepts.hpp"
# include "PointVector.hpp"

namespace s3d
{
	namespace Noise
	{
		SIV3D_CONCEPT_FLOATING_POINT
		inline constexpr Float MaxAmplitude(size_t octaves, Float persistence = 0.5) noexcept;

		SIV3D_CONCEPT_FLOATING_POINT
		inline constexpr Float To01(Float x) noexcept;

		SIV3D_CONCEPT_FLOATING_POINT
		inline constexpr Float To01Clamp(Float x) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave1D(const Noise& noise, Float x, size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave2D(const Noise& noise, Float x, Float y, size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave3D(const Noise& noise, Float x, Float y, Float z, size_t octaves, Float persistence = 0.5) noexcept;
	}
}

# include "detail/Noise.ipp"
