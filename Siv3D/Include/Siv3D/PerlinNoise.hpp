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

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
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

		double noise(double x) const;

		double noise(double x, double y) const;

		double noise(double x, double y, double z) const;

		double noise(const Vec2& xy) const
		{
			return noise(xy.x, xy.y);
		}

		double noise(const Vec3& xyz) const
		{
			return noise(xyz.x, xyz.y, xyz.z);
		}

		double octaveNoise(double x, int32 octaves) const;

		double octaveNoise(double x, double y, int32 octaves) const;

		double octaveNoise(double x, double y, double z, int32 octaves) const;

		double octaveNoise(const Vec2& xy, int32 octaves) const
		{
			return octaveNoise(xy.x, xy.y, octaves);
		}

		double octaveNoise(const Vec3& xyz, int32 octaves) const
		{
			return octaveNoise(xyz.x, xyz.y, xyz.z, octaves);
		}

		double noise0_1(double x) const
		{
			return noise(x) * 0.5 + 0.5;
		}

		double noise0_1(double x, double y) const
		{
			return noise(x, y) * 0.5 + 0.5;
		}

		double noise0_1(double x, double y, double z) const
		{
			return noise(x, y, z) * 0.5 + 0.5;
		}

		double noise0_1(const Vec2& xy) const
		{
			return noise0_1(xy.x, xy.y);
		}

		double noise0_1(const Vec3& xyz) const
		{
			return noise0_1(xyz.x, xyz.y, xyz.z);
		}

		double octaveNoise0_1(double x, int32 octaves) const
		{
			return octaveNoise(x, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(double x, double y, int32 octaves) const
		{
			return octaveNoise(x, y, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(double x, double y, double z, int32 octaves) const
		{
			return octaveNoise(x, y, z, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(const Vec2& xy, int32 octaves) const
		{
			return octaveNoise0_1(xy.x, xy.y, octaves);
		}

		double octaveNoise0_1(const Vec3& xyz, int32 octaves) const
		{
			return octaveNoise0_1(xyz.x, xyz.y, xyz.z, octaves);
		}
	};
}
