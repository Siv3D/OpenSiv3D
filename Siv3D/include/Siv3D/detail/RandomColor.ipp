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
	inline Color RandomColor()
	{
		return RandomColor(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Color RandomColor(URBG&& urbg)
	{
		return HueToColor(Random(360.0, std::forward<URBG>(urbg)));
	}

	inline Color RandomColor(
		const std::pair<uint32, uint32>& rMinMax,
		const std::pair<uint32, uint32>& gMinMax,
		const std::pair<uint32, uint32>& bMinMax)
	{
		return RandomColor(rMinMax, gMinMax, bMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Color RandomColor(
		const std::pair<uint32, uint32>& rMinMax,
		const std::pair<uint32, uint32>& gMinMax,
		const std::pair<uint32, uint32>& bMinMax,
		URBG&& urbg)
	{
		return{ static_cast<uint8>(Random(rMinMax.first, rMinMax.second, std::forward<URBG>(urbg))),
				static_cast<uint8>(Random(gMinMax.first, gMinMax.second, std::forward<URBG>(urbg))),
				static_cast<uint8>(Random(bMinMax.first, bMinMax.second, std::forward<URBG>(urbg))) };
	}

	inline ColorF RandomColorF()
	{
		return RandomColorF(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline ColorF RandomColorF(URBG&& urbg)
	{
		return HueToColorF(Random(360.0, std::forward<URBG>(urbg)));
	}

	inline ColorF RandomColorF(
		const std::pair<double, double>& rMinMax,
		const std::pair<double, double>& gMinMax,
		const std::pair<double, double>& bMinMax)
	{
		return RandomColorF(rMinMax, gMinMax, bMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline ColorF RandomColorF(
		const std::pair<double, double>& rMinMax,
		const std::pair<double, double>& gMinMax,
		const std::pair<double, double>& bMinMax,
		URBG&& urbg)
	{
		return{ Random(rMinMax.first, rMinMax.second, std::forward<URBG>(urbg)),
				Random(gMinMax.first, gMinMax.second, std::forward<URBG>(urbg)),
				Random(bMinMax.first, bMinMax.second, std::forward<URBG>(urbg)) };
	}

	inline HSV RandomHSV()
	{
		return RandomHSV(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline HSV RandomHSV(URBG&& urbg)
	{
		return{ Random(360.0, std::forward<URBG>(urbg)), 1.0, 1.0 };
	}

	inline HSV RandomHSV(
		const std::pair<double, double>& hMinMax,
		const std::pair<double, double>& sMinMax,
		const std::pair<double, double>& vMinMax)
	{
		return RandomColorF(hMinMax, sMinMax, vMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline HSV RandomHSV(
		const std::pair<double, double>& hMinMax,
		const std::pair<double, double>& sMinMax,
		const std::pair<double, double>& vMinMax,
		URBG&& urbg)
	{
		return{ Random(hMinMax.first, hMinMax.second, std::forward<URBG>(urbg)),
				Random(sMinMax.first, sMinMax.second, std::forward<URBG>(urbg)),
				Random(vMinMax.first, vMinMax.second, std::forward<URBG>(urbg)) };
	}
}
