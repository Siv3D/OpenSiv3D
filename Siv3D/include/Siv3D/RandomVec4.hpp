//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "DiscreteDistribution.hpp"

namespace s3d
{
	[[nodiscard]]
	Vec4 RandomVec4(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax,
		const std::pair<double, double>& wMinMax);
	
	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	Vec4 RandomVec4(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax,
		const std::pair<double, double>& wMinMax, URBG&& urbg);

	[[nodiscard]]
	Vec4 RandomVec4(double xMax, double yMax, double zMax, double wMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	Vec4 RandomVec4(double xMax, double yMax, double zMax, double wMax, URBG&& urbg);
}

# include "detail/RandomVec4.ipp"
