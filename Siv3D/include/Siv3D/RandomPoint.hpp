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
# include "PointVector.hpp"

namespace s3d
{
	Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax);

	Point RandomPoint(const Rect& rect);

	Point RandomPoint(int32 xMax, int32 yMax);
}
