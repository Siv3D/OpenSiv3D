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
# include "Common.hpp"
# include "Concepts.hpp"
# include "PointVector.hpp"

namespace s3d
{
	namespace Noise
	{
		SIV3D_CONCEPT_FLOATING_POINT
		inline constexpr Float MaxAmplitude(size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave1D(const Noise& noise, Float x, size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave2D(const Noise& noise, Float x, Float y, size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave3D(const Noise& noise, Float x, Float y, Float z, size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave2D(const Noise& noise, Vector2D<Float> xy, size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave3D(const Noise& noise, Vector3D<Float> xyz, size_t octaves, Float persistence = 0.5) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave1D0_1(const Noise& noise, Float x, size_t octaves) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave2D0_1(const Noise& noise, Float x, Float y, size_t octaves) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave3D0_1(const Noise& noise, Float x, Float y, Float z, size_t octaves) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave2D0_1(const Noise& noise, Vector2D<Float> xy, size_t octaves) noexcept;

		template <class Noise, class Float = typename Noise::value_type>
		inline auto Octave3D0_1(const Noise& noise, Vector3D<Float> xyz, size_t octaves) noexcept;
	}
}

# include "detail/Noise.ipp"
