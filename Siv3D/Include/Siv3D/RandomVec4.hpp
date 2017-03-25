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
	inline Vec4 RandomVec4(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax,
		const std::pair<double, double>& wMinMax
	)
	{
		Vec4 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		v.w = Random(wMinMax.first, wMinMax.second);
		return v;
	}

	inline Vec4 RandomVec4(double xMax, double yMax, double zMax, double wMax)
	{
		return RandomVec4({ 0.0, xMax }, { 0.0, yMax }, { 0.0, zMax }, { 0.0, wMax });
	}
}
