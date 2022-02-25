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
# include "Color.hpp"
# include "ColorF.hpp"
# include "HSV.hpp"

namespace s3d
{
	[[nodiscard]]
	inline Color RandomColor();

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Color RandomColor(URBG&& urbg);

	[[nodiscard]]
	inline Color RandomColor(
		const std::pair<uint32, uint32>& rMinMax,
		const std::pair<uint32, uint32>& gMinMax,
		const std::pair<uint32, uint32>& bMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Color RandomColor(
		const std::pair<uint32, uint32>& rMinMax,
		const std::pair<uint32, uint32>& gMinMax,
		const std::pair<uint32, uint32>& bMinMax,
		URBG&& urbg);

	[[nodiscard]]
	inline ColorF RandomColorF();

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline ColorF RandomColorF(URBG&& urbg);

	[[nodiscard]]
	inline ColorF RandomColorF(
		const std::pair<double, double>& rMinMax,
		const std::pair<double, double>& gMinMax,
		const std::pair<double, double>& bMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline ColorF RandomColorF(
		const std::pair<double, double>& rMinMax,
		const std::pair<double, double>& gMinMax,
		const std::pair<double, double>& bMinMax,
		URBG&& urbg);

	[[nodiscard]]
	inline HSV RandomHSV();

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline HSV RandomHSV(URBG&& urbg);

	[[nodiscard]]
	inline HSV RandomHSV(
		const std::pair<double, double>& hMinMax,
		const std::pair<double, double>& sMinMax,
		const std::pair<double, double>& vMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline HSV RandomHSV(
		const std::pair<double, double>& hMinMax,
		const std::pair<double, double>& sMinMax,
		const std::pair<double, double>& vMinMax,
		URBG&& urbg);
}

# include "detail/RandomColor.ipp"
