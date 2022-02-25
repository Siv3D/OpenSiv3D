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
	inline Vec4 RandomVec4(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax,
		const std::pair<double, double>& wMinMax)
	{
		return RandomVec4(xMinMax, yMinMax, zMinMax, wMinMax, GetDefaultRNG());
	}
	
	SIV3D_CONCEPT_URBG_
	inline Vec4 RandomVec4(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax,
		const std::pair<double, double>& wMinMax, URBG&& urbg)
	{
		return{
			RandomClosed(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)),
			RandomClosed(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)),
			RandomClosed(zMinMax.first, zMinMax.second, std::forward<URBG>(urbg)),
			RandomClosed(wMinMax.first, wMinMax.second, std::forward<URBG>(urbg)),
		};
	}

	inline Vec4 RandomVec4(const double xMax, const double yMax, const double zMax, const double wMax)
	{
		return RandomVec4(xMax, yMax, zMax, wMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec4 RandomVec4(const double xMax, const double yMax, const double zMax, const double wMax, URBG&& urbg)
	{
		return{
			RandomClosed(0.0, xMax, std::forward<URBG>(urbg)),
			RandomClosed(0.0, yMax, std::forward<URBG>(urbg)),
			RandomClosed(0.0, zMax, std::forward<URBG>(urbg)),
			RandomClosed(0.0, wMax, std::forward<URBG>(urbg)),
		};
	}
}
