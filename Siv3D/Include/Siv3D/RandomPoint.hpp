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
# include "Rectangle.hpp"

namespace s3d
{
	inline Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax)
	{
		Point p;
		p.x = Random(xMinMax.first, xMinMax.second);
		p.y = Random(yMinMax.first, yMinMax.second);
		return p;
	}

	inline Point RandomPoint(const Rect& rect)
	{
		Point p;
		p.x = Random(rect.x, rect.x + rect.w - 1);
		p.y = Random(rect.y, rect.y + rect.h - 1);
		return p;
	}

	inline Point RandomPoint(const int32 xMax, const int32 yMax)
	{
		return RandomPoint({ 0, xMax }, { 0, yMax });
	}
}
