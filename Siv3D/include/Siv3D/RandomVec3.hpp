//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <utility>
# include "PointVector.hpp"

namespace s3d
{
	Vec3 RandomVec3onUnitSphere();

	Vec3 RandomVec3insideUnitSphere();

	Vec3 RandomVec3();

	Vec3 RandomVec3(double length);

	Vec3 RandomVec3(
		double x,
		double y,
		const std::pair<double, double>& zMinMax);

	Vec3 RandomVec3(
		double x,
		const std::pair<double, double>& yMinMax,
		double z);

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		double y,
		double z);

	Vec3 RandomVec3(
		double x,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax);

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		double y,
		const std::pair<double, double>& zMinMax);

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		double z);

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax);

	Vec3 RandomVec3(double xMax, double yMax, double zMax);
}
