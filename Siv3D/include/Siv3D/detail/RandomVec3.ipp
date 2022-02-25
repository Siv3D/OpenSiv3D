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
	inline Vec3 RandomVec3()
	{
		return RandomVec3(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(URBG&& urbg)
	{
		return RandomVec3onUnitSphere(std::forward<URBG>(urbg));
	}

	inline Vec3 RandomVec3onUnitSphere()
	{
		return RandomVec3onUnitSphere(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3onUnitSphere(URBG&& urbg)
	{
		const double theta = Random(Math::Constants::Pi, std::forward<URBG>(urbg));
		const double phi = Random(Math::Constants::TwoPi, std::forward<URBG>(urbg));
		const double s = std::sin(theta);
		return{ (s * std::cos(phi)), (s * std::sin(phi)), std::cos(theta) };
	}

	inline Vec3 RandomVec3insideUnitSphere()
	{
		return RandomVec3insideUnitSphere(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3insideUnitSphere(URBG&& urbg)
	{
		for (;;)
		{
			Vec3 v;
			v.x = 2.0 * Random(std::forward<URBG>(urbg)) - 1.0;
			v.y = 2.0 * Random(std::forward<URBG>(urbg)) - 1.0;
			v.z = 2.0 * Random(std::forward<URBG>(urbg)) - 1.0;

			if (v.lengthSq() < 1.0)
			{
				return v;
			}
		}
	}

	inline Vec3 RandomVec3(const double length)
	{
		return RandomVec3(length, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(const double length, URBG&& urbg)
	{
		return (RandomVec3onUnitSphere(std::forward<URBG>(urbg)) * length);
	}

	inline Vec3 RandomVec3(
		const double x,
		const double y,
		const std::pair<double, double>& zMinMax)
	{
		return RandomVec3(x, y, zMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(
		const double x,
		const double y,
		const std::pair<double, double>& zMinMax, URBG&& urbg)
	{
		return{
			x,
			y,
			RandomClosed(zMinMax.first, zMinMax.second, std::forward<URBG>(urbg))
		};
	}

	inline Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const double z)
	{
		return RandomVec3(x, yMinMax, z, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const double z, URBG&& urbg)
	{
		return{
			x,
			RandomClosed(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)),
			z
		};
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const double z)
	{
		return RandomVec3(xMinMax, y, z, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const double z, URBG&& urbg)
	{
		return{
			RandomClosed(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)),
			y,
			z
		};
	}

	inline Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax)
	{
		return RandomVec3(x, yMinMax, zMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax, URBG&& urbg)
	{
		return{
			x,
			RandomClosed(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)),
			RandomClosed(zMinMax.first, zMinMax.second, std::forward<URBG>(urbg)),
		};
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const std::pair<double, double>& zMinMax)
	{
		return RandomVec3(xMinMax, y, zMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const std::pair<double, double>& zMinMax, URBG&& urbg)
	{
		return{
			RandomClosed(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)),
			y,
			RandomClosed(zMinMax.first, zMinMax.second, std::forward<URBG>(urbg)),
		};
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const double z)
	{
		return RandomVec3(xMinMax, yMinMax, z, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const double z, URBG&& urbg)
	{
		return{
			RandomClosed(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)),
			RandomClosed(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)),
			z,
		};
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax)
	{
		return RandomVec3(xMinMax, yMinMax, zMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax, URBG&& urbg)
	{
		return{
			RandomClosed(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)),
			RandomClosed(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)),
			RandomClosed(zMinMax.first, zMinMax.second, std::forward<URBG>(urbg)),
		};
	}

	inline Vec3 RandomVec3(const double xMax, const double yMax, const double zMax)
	{
		return RandomVec3(xMax, yMax, zMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(const double xMax, const double yMax, const double zMax, URBG&& urbg)
	{
		return{
			RandomClosed(0.0, xMax, std::forward<URBG>(urbg)),
			RandomClosed(0.0, yMax, std::forward<URBG>(urbg)),
			RandomClosed(0.0, zMax, std::forward<URBG>(urbg)),
		};
	}

	inline Vec3 RandomVec3(const Box& box)
	{
		return RandomVec3(box, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(const Box& box, URBG&& urbg)
	{
		return RandomVec3(
			{ (box.center.x - box.size.x * 0.5), (box.center.x + box.size.x * 0.5) },
			{ (box.center.y - box.size.y * 0.5), (box.center.y + box.size.y * 0.5) },
			{ (box.center.z - box.size.z * 0.5), (box.center.z + box.size.z * 0.5) },
			std::forward<URBG>(urbg)
		);
	}

	inline Vec3 RandomVec3(const Sphere& sphere)
	{
		return RandomVec3(sphere, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3(const Sphere& sphere, URBG&& urbg)
	{
		return (RandomVec3insideUnitSphere(std::forward<URBG>(urbg)) * sphere.r)
			+ sphere.center;
	}

	inline Vec3 RandomVec3on(const Sphere& sphere)
	{
		return RandomVec3on(sphere, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec3 RandomVec3on(const Sphere& sphere, URBG&& urbg)
	{
		return (RandomVec3onUnitSphere(std::forward<URBG>(urbg)) * sphere.r)
			+ sphere.center;
	}
}
