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
# include "PointVector.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	[[nodiscard]]
	inline Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax, URBG&& urbg);

	[[nodiscard]]
	inline Point RandomPoint(const Rect& rect);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Point RandomPoint(const Rect& rect, URBG&& urbg);

	[[nodiscard]]
	inline Point RandomPoint(int32 xMax, int32 yMax);

	SIV3D_CONCEPT_URBG
	[[nodiscard]]
	inline Point RandomPoint(int32 xMax, int32 yMax, URBG&& urbg);
}

# include "detail/RandomPoint.ipp"
