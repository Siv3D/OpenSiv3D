//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// Perlin Noise | パーリンノイズ
	/// </summary>
	class PerlinNoise
	{
	private:

		int32 p[512];

	public:

		explicit PerlinNoise(uint32 seed = 0)
		{
			reseed(seed);
		}

		void reseed(uint32 seed);

		[[nodiscard]] double noise(double x) const;

		[[nodiscard]] double noise(double x, double y) const;

		[[nodiscard]] double noise(double x, double y, double z) const;

		[[nodiscard]] double noise(const Vec2& xy) const
		{
			return noise(xy.x, xy.y);
		}

		[[nodiscard]] double noise(const Vec3& xyz) const
		{
			return noise(xyz.x, xyz.y, xyz.z);
		}

		[[nodiscard]] double octaveNoise(double x, int32 octaves) const;

		[[nodiscard]] double octaveNoise(double x, double y, int32 octaves) const;

		[[nodiscard]] double octaveNoise(double x, double y, double z, int32 octaves) const;

		[[nodiscard]] double octaveNoise(const Vec2& xy, int32 octaves) const
		{
			return octaveNoise(xy.x, xy.y, octaves);
		}

		[[nodiscard]] double octaveNoise(const Vec3& xyz, int32 octaves) const
		{
			return octaveNoise(xyz.x, xyz.y, xyz.z, octaves);
		}

		[[nodiscard]] double noise0_1(double x) const
		{
			return noise(x) * 0.5 + 0.5;
		}

		[[nodiscard]] double noise0_1(double x, double y) const
		{
			return noise(x, y) * 0.5 + 0.5;
		}

		[[nodiscard]] double noise0_1(double x, double y, double z) const
		{
			return noise(x, y, z) * 0.5 + 0.5;
		}

		[[nodiscard]] double noise0_1(const Vec2& xy) const
		{
			return noise0_1(xy.x, xy.y);
		}

		[[nodiscard]] double noise0_1(const Vec3& xyz) const
		{
			return noise0_1(xyz.x, xyz.y, xyz.z);
		}

		[[nodiscard]] double octaveNoise0_1(double x, int32 octaves) const
		{
			return octaveNoise(x, octaves) * 0.5 + 0.5;
		}

		[[nodiscard]] double octaveNoise0_1(double x, double y, int32 octaves) const
		{
			return octaveNoise(x, y, octaves) * 0.5 + 0.5;
		}

		[[nodiscard]] double octaveNoise0_1(double x, double y, double z, int32 octaves) const
		{
			return octaveNoise(x, y, z, octaves) * 0.5 + 0.5;
		}

		[[nodiscard]] double octaveNoise0_1(const Vec2& xy, int32 octaves) const
		{
			return octaveNoise0_1(xy.x, xy.y, octaves);
		}

		[[nodiscard]] double octaveNoise0_1(const Vec3& xyz, int32 octaves) const
		{
			return octaveNoise0_1(xyz.x, xyz.y, xyz.z, octaves);
		}
	};
}
