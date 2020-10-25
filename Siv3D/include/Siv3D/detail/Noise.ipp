//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

		template <class Noise, class Float>
		inline auto Octave2D(const Noise& noise, const Vector2D<Float> xy, const size_t octaves, const Float persistence) noexcept
		{
			return Octave2D(noise, xy.x, xy.y, octaves, persistence);
		}

		template <class Noise, class Float>
		inline auto Octave3D(const Noise& noise, const Vector3D<Float> xyz, const size_t octaves, const Float persistence) noexcept
		{
			return Octave3D(noise, xyz.x, xyz.y, xyz.z, octaves, persistence);
		}

		template <class Noise, class Float>
		inline auto Octave1D0_1(const Noise& noise, const Float x, const size_t octaves) noexcept
		{
			return ((Octave1D(noise, x, octaves, 0.5) * 0.5) + 0.5);
		}

		template <class Noise, class Float>
		inline auto Octave2D0_1(const Noise& noise, const Float x, const Float y, const size_t octaves) noexcept
		{
			return ((Octave2D(noise, x, y, octaves, 0.5) * 0.5) + 0.5);
		}

		template <class Noise, class Float>
		inline auto Octave3D0_1(const Noise& noise, const Float x, const Float y, const Float z, const size_t octaves) noexcept
		{
			return ((Octave3D(noise, x, y, z, octaves, 0.5) * 0.5) + 0.5);
		}

		template <class Noise, class Float>
		inline auto Octave2D0_1(const Noise& noise, const Vector2D<Float> xy, const size_t octaves) noexcept
		{
			return Octave2D0_1(noise, xy.x, xy.y, octaves, 0.5);
		}

		template <class Noise, class Float>
		inline auto Octave3D0_1(const Noise& noise, const Vector3D<Float> xyz, const size_t octaves) noexcept
		{
			return Octave3D0_1(noise, xyz.x, xyz.y, xyz.z, octaves, 0.5);
		}
	}
}
