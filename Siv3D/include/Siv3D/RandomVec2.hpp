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
	Vec2 RandomVec2();

	Vec2 RandomVec2(double length);

	Vec2 RandomVec2(double x, const std::pair<double, double>& yMinMax);

	Vec2 RandomVec2(const std::pair<double, double>& xMinMax, double y);

	Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax);

	Vec2 RandomVec2(double xMax, double yMax);

	Vec2 RandomVec2(const Circle& circle);

	Vec2 RandomVec2(const RectF& rect);

	Vec2 RandomVec2(const Triangle& triangle);
}
