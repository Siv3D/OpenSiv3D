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
# include "Common.hpp"
# include "PointVector.hpp"
# include "Sphere.hpp"
# include "Box.hpp"
# include "DiscreteDistribution.hpp"

namespace s3d
{
	[[nodiscard]]
	inline Vec3 RandomVec3();

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(URBG&& urbg);
	
	[[nodiscard]]
	inline Vec3 RandomVec3onUnitSphere();

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3onUnitSphere(URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3insideUnitSphere();

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3insideUnitSphere(URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(double length);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(double length, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(
		double x,
		double y,
		const std::pair<double, double>& zMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(
		double x,
		double y,
		const std::pair<double, double>& zMinMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(
		double x,
		const std::pair<double, double>& yMinMax,
		double z);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(
		double x,
		const std::pair<double, double>& yMinMax,
		double z, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		double y,
		double z);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		double y,
		double z, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(
		double x,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(
		double x,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		double y,
		const std::pair<double, double>& zMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		double y,
		const std::pair<double, double>& zMinMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		double z);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		double z, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(double xMax, double yMax, double zMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(double xMax, double yMax, double zMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(const Box& box);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(const Box& box, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3(const Sphere& sphere);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3(const Sphere& sphere, URBG&& urbg);

	[[nodiscard]]
	inline Vec3 RandomVec3on(const Sphere& sphere);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec3 RandomVec3on(const Sphere& sphere, URBG&& urbg);
}

# include "detail/RandomVec3.ipp"
