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
	namespace Noise
	{
		SIV3D_CONCEPT_FLOATING_POINT_
		inline constexpr Float MaxAmplitude(const size_t octaves, const Float persistence) noexcept
		{
			using value_type = Float;
			value_type result = 0;
			value_type amplitude = 1;

			for (size_t i = 0; i < octaves; ++i)
			{
				result += amplitude;
				amplitude *= persistence;
			}

			return result;
		}

		SIV3D_CONCEPT_FLOATING_POINT_
		inline constexpr Float To01(const Float x) noexcept
		{
			return (x * Float(0.5) + Float(0.5));
		}

		SIV3D_CONCEPT_FLOATING_POINT_
		inline constexpr Float To01Clamp(const Float x) noexcept
		{
			if (x <= Float(-1.0))
			{
				return Float(0.0);
			}
			else if (Float(1.0) <= x)
			{
				return Float(1.0);
			}

			return (x * Float(0.5) + Float(0.5));
		}

		template <class Noise, class Float>
		inline auto Octave1D(const Noise& noise, Float x, const size_t octaves, const Float persistence) noexcept
		{
			using value_type = Float;
			value_type result = 0;
			value_type amplitude = 1;

			for (size_t i = 0; i < octaves; ++i)
			{
				result += (noise.noise1D(x) * amplitude);
				x *= 2;
				amplitude *= persistence;
			}

			return result;
		}

		template <class Noise, class Float>
		inline auto Octave2D(const Noise& noise, Float x, Float y, const size_t octaves, const Float persistence) noexcept
		{
			using value_type = Float;
			value_type result = 0;
			value_type amplitude = 1;

			for (size_t i = 0; i < octaves; ++i)
			{
				result += (noise.noise2D(x, y) * amplitude);
				x *= 2;
				y *= 2;
				amplitude *= persistence;
			}

			return result;
		}

		template <class Noise, class Float>
		inline auto Octave3D(const Noise& noise, Float x, Float y, Float z, const size_t octaves, const Float persistence) noexcept
		{
			using value_type = Float;
			value_type result = 0;
			value_type amplitude = 1;

			for (size_t i = 0; i < octaves; ++i)
			{
				result += (noise.noise3D(x, y, z) * amplitude);
				x *= 2;
				y *= 2;
				z *= 2;
				amplitude *= persistence;
			}

			return result;
		}
	}
}
