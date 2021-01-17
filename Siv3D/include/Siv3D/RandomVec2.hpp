//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "2DShapes.hpp"
# include "DiscreteDistribution.hpp"

namespace s3d
{
	[[nodiscard]]
	inline Vec2 RandomVec2();

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(double length);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(double length, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(double x, const std::pair<double, double>& yMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(double x, const std::pair<double, double>& yMinMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, double y);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, double y, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(double xMax, double yMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(double xMax, double yMax, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(const Line& line);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Line& line, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(const Circle& circle);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Circle& circle, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(const RectF& rect);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const RectF& rect, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(const Triangle& triangle);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Triangle& triangle, URBG&& urbg);

	[[nodiscard]]
	inline Vec2 RandomVec2(const Quad& quad);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Vec2 RandomVec2(const Quad& quad, URBG&& urbg);
}

# include "detail/RandomVec2.ipp"
