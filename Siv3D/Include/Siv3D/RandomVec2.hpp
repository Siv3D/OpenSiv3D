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
	inline Vec2 RandomVec2()
	{
		const double theta = Random(Math::TwoPi);
		return{ std::cos(theta), std::sin(theta) };
	}

	inline Vec2 RandomVec2(const double length)
	{
		return RandomVec2() * length;
	}

	inline Vec2 RandomVec2(const double x, const std::pair<double, double>& yMinMax)
	{
		return{ x, Random(yMinMax.first, yMinMax.second) };
	}

	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const double y)
	{
		return{ Random(xMinMax.first, xMinMax.second), y };
	}

	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax)
	{
		Vec2 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		return v;
	}

	inline Vec2 RandomVec2(const double xMax, const double yMax)
	{
		return RandomVec2({ 0.0, xMax }, { 0.0, yMax });
	}

	//inline Vec2 RandomVec2(const Circle& circle)
	//{
	//	const double r = sqrt(Random()) * circle.r;
	//	const double theta = Random(Math::TwoPi);
	//	return circle.center.movedBy(std::cos(theta)*r, std::sin(theta)*r);
	//}

	inline Vec2 RandomVec2(const RectF& rect)
	{
		Vec2 p;
		p.x = Random(rect.x, rect.x + rect.w);
		p.y = Random(rect.y, rect.y + rect.h);
		return p;
	}
}
