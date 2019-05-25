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
# include "Color.hpp"
# include "HSV.hpp"

namespace s3d
{
	Color RandomColor();

	Color RandomColor(
		const std::pair<uint32, uint32>& rMinMax,
		const std::pair<uint32, uint32>& gMinMax,
		const std::pair<uint32, uint32>& bMinMax);

	ColorF RandomColorF();

	ColorF RandomColorF(
		const std::pair<double, double>& rMinMax,
		const std::pair<double, double>& gMinMax,
		const std::pair<double, double>& bMinMax);

	HSV RandomHSV();

	HSV RandomHSV(
		const std::pair<double, double>& hMinMax,
		const std::pair<double, double>& sMinMax,
		const std::pair<double, double>& vMinMax);
}
