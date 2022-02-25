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
	inline Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax)
	{
		return RandomPoint(xMinMax, yMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax, URBG&& urbg)
	{
		return{
			Random(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)),
			Random(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)) };
	}

	inline Point RandomPoint(const Rect& rect)
	{
		return RandomPoint(rect, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Point RandomPoint(const Rect& rect, URBG&& urbg)
	{
		return{
			Random(rect.x, (rect.x + rect.w - 1), std::forward<URBG>(urbg)),
			Random(rect.y, (rect.y + rect.h - 1), std::forward<URBG>(urbg)) };
	}

	inline Point RandomPoint(const int32 xMax, const int32 yMax)
	{
		return RandomPoint(xMax, yMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Point RandomPoint(const int32 xMax, const int32 yMax, URBG&& urbg)
	{
		return{
			Random(xMax, std::forward<URBG>(urbg)),
			Random(yMax, std::forward<URBG>(urbg)) };
	}
}
