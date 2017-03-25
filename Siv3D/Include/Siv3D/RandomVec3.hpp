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
# include "Random.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	inline Vec3 RandomVec3()
	{
		const double theta = Random(Math::Pi);
		const double phi = Random(Math::TwoPi);
		const double s = std::sin(theta);
		return{ s * std::cos(phi), s * std::sin(phi), std::cos(theta) };
	}

	inline Vec3 RandomVec3(const double length)
	{
		return RandomVec3() * length;
	}

	inline Vec3 RandomVec3(
		const double x,
		const double y,
		const std::pair<double, double>& zMinMax
	)
	{
		Vec3 v;
		v.x = x;
		v.y = y;
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	inline Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const double z
	)
	{
		Vec3 v;
		v.x = x;
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = z;
		return v;
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const double z
	)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = y;
		v.z = z;
		return v;
	}

	inline Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax
	)
	{
		Vec3 v;
		v.x = x;
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const std::pair<double, double>& zMinMax
	)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = y;
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const double z
	)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = z;
		return v;
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax
	)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	inline Vec3 RandomVec3(const double xMax, const double yMax, const double zMax)
	{
		return RandomVec3({ 0.0, xMax }, { 0.0, yMax }, { 0.0, zMax });
	}
}
