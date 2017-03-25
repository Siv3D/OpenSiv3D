//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/PerlinNoise.hpp>
# include <Siv3D/Random.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr double Fade(double t)
		{
			return t * t * t * (t * (t * 6 - 15) + 10);
		}

		static constexpr double Lerp(double t, double a, double b)
		{
			return a + t * (b - a);
		}

		static constexpr double Grad(int32 hash, double x, double y, double z)
		{
			const int32 h = hash & 15;
			const double u = h < 8 ? x : y;
			const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}
	}

	void PerlinNoise::reseed(const uint32 seed)
	{
		for (int32 i = 0; i < 256; ++i)
		{
			p[i] = i;
		}

		std::shuffle(std::begin(p), std::begin(p) + 256, DefaultRNGType(seed));

		for (size_t i = 0; i < 256; ++i)
		{
			p[256 + i] = p[i];
		}
	}

	double PerlinNoise::noise(const double x) const
	{
		return noise(x, 0.0, 0.0);
	}

	double PerlinNoise::noise(const double x, const double y) const
	{
		return noise(x, y, 0.0);
	}

	double PerlinNoise::noise(double x, double y, double z) const
	{
			const int32 X = static_cast<int32>(std::floor(x)) & 255;
			const int32 Y = static_cast<int32>(std::floor(y)) & 255;
			const int32 Z = static_cast<int32>(std::floor(z)) & 255;

			x -= std::floor(x);
			y -= std::floor(y);
			z -= std::floor(z);

			const double u = detail::Fade(x);
			const double v = detail::Fade(y);
			const double w = detail::Fade(z);

			const int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
			const int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

			return detail::Lerp(w, detail::Lerp(v, detail::Lerp(u, detail::Grad(p[AA], x, y, z),
				detail::Grad(p[BA], x - 1, y, z)),
				detail::Lerp(u, detail::Grad(p[AB], x, y - 1, z),
				detail::Grad(p[BB], x - 1, y - 1, z))),
				detail::Lerp(v, detail::Lerp(u, detail::Grad(p[AA + 1], x, y, z - 1),
				detail::Grad(p[BA + 1], x - 1, y, z - 1)),
				detail::Lerp(u, detail::Grad(p[AB + 1], x, y - 1, z - 1),
				detail::Grad(p[BB + 1], x - 1, y - 1, z - 1))));
	}

	double PerlinNoise::octaveNoise(double x, const int32 octaves) const
	{
		double result = 0.0;
		double amp = 1.0;

		for (int32 i = 0; i < octaves; ++i)
		{
			result += noise(x) * amp;
			x *= 2.0;
			amp *= 0.5;
		}

		return result;
	}

	double PerlinNoise::octaveNoise(double x, double y, const int32 octaves) const
	{
		double result = 0.0;
		double amp = 1.0;

		for (int32 i = 0; i < octaves; ++i)
		{
			result += noise(x, y) * amp;
			x *= 2.0;
			y *= 2.0;
			amp *= 0.5;
		}

		return result;
	}

	double PerlinNoise::octaveNoise(double x, double y, double z, const int32 octaves) const
	{
		double result = 0.0;
		double amp = 1.0;

		for (int32 i = 0; i < octaves; ++i)
		{
			result += noise(x, y, z) * amp;
			x *= 2.0;
			y *= 2.0;
			z *= 2.0;
			amp *= 0.5;
		}

		return result;
	}
}
