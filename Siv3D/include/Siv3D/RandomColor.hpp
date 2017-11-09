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
# include "Color.hpp"
# include "HSV.hpp"
# include "NamedParameter.hpp"

namespace s3d
{
	inline Color RandomColor()
	{
		return HueToColor(Random(360.0));
	}

	inline Color RandomColor(
		const std::pair<uint32, uint32>& rMinMax,
		const std::pair<uint32, uint32>& gMinMax,
		const std::pair<uint32, uint32>& bMinMax
	)
	{
		Color c;
		c.r = Random(rMinMax.first, rMinMax.second);
		c.g = Random(gMinMax.first, gMinMax.second);
		c.b = Random(bMinMax.first, bMinMax.second);
		c.a = 255;
		return c;
	}

	inline Color RandomColorF()
	{
		return HueToColor(Random(360.0));
	}

	inline Color RandomColorF(
		const std::pair<double, double>& rMinMax,
		const std::pair<double, double>& gMinMax,
		const std::pair<double, double>& bMinMax
	)
	{
		ColorF c;
		c.r = Random(rMinMax.first, rMinMax.second);
		c.g = Random(gMinMax.first, gMinMax.second);
		c.b = Random(bMinMax.first, bMinMax.second);
		c.a = 255;
		return c;
	}

	inline HSV RandomHSV()
	{
		return{ Random(360.0), 1.0, 1.0 };
	}

	inline HSV RandomHSV(
		const std::pair<double, double>& hMinMax,
		const std::pair<double, double>& sMinMax,
		const std::pair<double, double>& vMinMax
	)
	{
		HSV hsv;
		hsv.h = Random(hMinMax.first, hMinMax.second);
		hsv.s = Random(sMinMax.first, sMinMax.second);
		hsv.v = Random(vMinMax.first, vMinMax.second);
		return hsv;
	}
}
