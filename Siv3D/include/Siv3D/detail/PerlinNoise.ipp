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
	template <class Float>
	inline constexpr BasicPerlinNoise<Float>::BasicPerlinNoise() noexcept
		: m_perm{ 151,160,137,91,90,15,
				131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
				190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
				88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
				77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
				102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
				135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
				5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
				223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
				129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
				251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
				49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
				138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	} {}

	template <class Float>
	inline BasicPerlinNoise<Float>::BasicPerlinNoise(const uint64 seed)
	{
		reseed(seed);
	}

	template <class Float>
	SIV3D_CONCEPT_URBG_
	inline BasicPerlinNoise<Float>::BasicPerlinNoise(URBG&& urbg)
	{
		reseed(std::forward<URBG>(urbg));
	}

	template <class Float>
	inline void BasicPerlinNoise<Float>::reseed(const uint64 seed)
	{
		reseed(DefaultRNG{ seed });
	}

	template <class Float>
	SIV3D_CONCEPT_URBG_
	inline void BasicPerlinNoise<Float>::reseed(URBG&& urbg)
	{
		std::iota(m_perm.begin(), m_perm.end(), static_cast<std::uint8_t>(0));
		Shuffle(m_perm.begin(), m_perm.end(), std::forward<URBG>(urbg));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise1D(const value_type x) const noexcept
	{
		return noise3D(x,
			static_cast<value_type>(0.34567890123456789012),
			static_cast<value_type>(0.12345678901234567890)); // arbitrary number for entropy
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise2D(const value_type x, const value_type y) const noexcept
	{
		return noise3D(x,
			y,
			static_cast<value_type>(0.12345678901234567890)); // arbitrary number for entropy
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise2D(const Vector2D<value_type> xy) const noexcept
	{
		return noise2D(xy.x, xy.y);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise3D(const value_type x, const value_type y, const value_type z) const noexcept
	{
		const value_type _x = std::floor(x);
		const value_type _y = std::floor(y);
		const value_type _z = std::floor(z);

		const std::int32_t ix = static_cast<std::int32_t>(_x) & 255;
		const std::int32_t iy = static_cast<std::int32_t>(_y) & 255;
		const std::int32_t iz = static_cast<std::int32_t>(_z) & 255;

		const value_type fx = (x - _x);
		const value_type fy = (y - _y);
		const value_type fz = (z - _z);

		const value_type u = Fade(fx);
		const value_type v = Fade(fy);
		const value_type w = Fade(fz);

		const std::uint8_t A = (m_perm[ix & 255] + iy) & 255;
		const std::uint8_t B = (m_perm[(ix + 1) & 255] + iy) & 255;

		const std::uint8_t AA = (m_perm[A] + iz) & 255;
		const std::uint8_t AB = (m_perm[(A + 1) & 255] + iz) & 255;

		const std::uint8_t BA = (m_perm[B] + iz) & 255;
		const std::uint8_t BB = (m_perm[(B + 1) & 255] + iz) & 255;

		const value_type p0 = Grad(m_perm[AA], fx, fy, fz);
		const value_type p1 = Grad(m_perm[BA], fx - 1, fy, fz);
		const value_type p2 = Grad(m_perm[AB], fx, fy - 1, fz);
		const value_type p3 = Grad(m_perm[BB], fx - 1, fy - 1, fz);
		const value_type p4 = Grad(m_perm[(AA + 1) & 255], fx, fy, fz - 1);
		const value_type p5 = Grad(m_perm[(BA + 1) & 255], fx - 1, fy, fz - 1);
		const value_type p6 = Grad(m_perm[(AB + 1) & 255], fx, fy - 1, fz - 1);
		const value_type p7 = Grad(m_perm[(BB + 1) & 255], fx - 1, fy - 1, fz - 1);

		const value_type q0 = Lerp(p0, p1, u);
		const value_type q1 = Lerp(p2, p3, u);
		const value_type q2 = Lerp(p4, p5, u);
		const value_type q3 = Lerp(p6, p7, u);

		const value_type r0 = Lerp(q0, q1, v);
		const value_type r1 = Lerp(q2, q3, v);

		return Lerp(r0, r1, w);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise3D(const Vector3D<value_type> xyz) const noexcept
	{
		return noise3D(xyz.x, xyz.y, xyz.z);
	}


	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise1D0_1(const value_type x) const noexcept
	{
		return Noise::To01(noise1D(x));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise2D0_1(const value_type x, const value_type y) const noexcept
	{
		return Noise::To01(noise2D(x, y));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise2D0_1(const Vector2D<value_type> xy) const noexcept
	{
		return noise2D0_1(xy.x, xy.y);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise3D0_1(const value_type x, const value_type y, const value_type z) const noexcept
	{
		return Noise::To01(noise3D(x, y, z));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::noise3D0_1(const Vector3D<value_type> xyz) const noexcept
	{
		return noise3D0_1(xyz.x, xyz.y, xyz.z);
	}


	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave1D(const value_type x, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::Octave1D(*this, x, octaves, persistence);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave2D(const value_type x, const value_type y, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::Octave2D(*this, x, y, octaves, persistence);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave2D(const Vector2D<value_type> xy, const int32 octaves, const value_type persistence) const noexcept
	{
		return octave2D(xy.x, xy.y, octaves, persistence);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave3D(const value_type x, const value_type y, const value_type z, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::Octave3D(*this, x, y, z, octaves, persistence);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave3D(const Vector3D<value_type> xyz, const int32 octaves, const value_type persistence) const noexcept
	{
		return octave3D(xyz.x, xyz.y, xyz.z, octaves, persistence);
	}


	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave1D0_1(const value_type x, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::To01Clamp(octave1D(x, octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave2D0_1(const value_type x, const value_type y, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::To01Clamp(octave2D(x, y, octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave2D0_1(const Vector2D<value_type> xy, const int32 octaves, const value_type persistence) const noexcept
	{
		return octave2D0_1(xy.x, xy.y, octaves, persistence);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave3D0_1(const value_type x, const value_type y, const value_type z, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::To01Clamp(octave3D(x, y, z, octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::octave3D0_1(const Vector3D<value_type> xyz, const int32 octaves, const value_type persistence) const noexcept
	{
		return octave3D0_1(xyz.x, xyz.y, xyz.z, octaves, persistence);
	}


	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave1D(const value_type x, const int32 octaves, const value_type persistence) const noexcept
	{
		return (octave1D(x, octaves, persistence) / Noise::MaxAmplitude(octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave2D(const value_type x, const value_type y, const int32 octaves, const value_type persistence) const noexcept
	{
		return (octave2D(x, y, octaves, persistence) / Noise::MaxAmplitude(octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave2D(const Vector2D<value_type> xy, const int32 octaves, const value_type persistence) const noexcept
	{
		return normalizedOctave2D(xy.x, xy.y, octaves, persistence);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave3D(const value_type x, const value_type y, const value_type z, const int32 octaves, const value_type persistence) const noexcept
	{
		return (octave3D(x, y, z, octaves, persistence) / Noise::MaxAmplitude(octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave3D(const Vector3D<value_type> xyz, const int32 octaves, const value_type persistence) const noexcept
	{
		return normalizedOctave3D(xyz.x, xyz.y, xyz.z, octaves, persistence);
	}


	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave1D0_1(const value_type x, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::To01(normalizedOctave1D(x, octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave2D0_1(const value_type x, const value_type y, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::To01(normalizedOctave2D(x, y, octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave2D0_1(const Vector2D<value_type> xy, const int32 octaves, const value_type persistence) const noexcept
	{
		return normalizedOctave2D0_1(xy.x, xy.y, octaves, persistence);
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave3D0_1(const value_type x, const value_type y, const value_type z, const int32 octaves, const value_type persistence) const noexcept
	{
		return Noise::To01(normalizedOctave3D(x, y, z, octaves, persistence));
	}

	template <class Float>
	inline typename BasicPerlinNoise<Float>::value_type BasicPerlinNoise<Float>::normalizedOctave3D0_1(const Vector3D<value_type> xyz, const int32 octaves, const value_type persistence) const noexcept
	{
		return normalizedOctave3D0_1(xyz.x, xyz.y, xyz.z, octaves, persistence);
	}


	template <class Float>
	inline constexpr const typename BasicPerlinNoise<Float>::state_type& BasicPerlinNoise<Float>::serialize() const noexcept
	{
		return m_perm;
	}

	template <class Float>
	inline constexpr void BasicPerlinNoise<Float>::deserialize(const state_type& state) noexcept
	{
		m_perm = state;
	}

	template <class Float>
	inline constexpr Float BasicPerlinNoise<Float>::Fade(const Float t) noexcept
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	template <class Float>
	inline constexpr Float BasicPerlinNoise<Float>::Lerp(const Float a, const Float b, const Float t) noexcept
	{
		return a + (b - a) * t;
	}

	template <class Float>
	inline constexpr Float BasicPerlinNoise<Float>::Grad(const uint8 hash, const Float x, const Float y, const Float z) noexcept
	{
		const uint8 h = hash & 15;
		const Float u = h < 8 ? x : y;
		const Float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}
}
