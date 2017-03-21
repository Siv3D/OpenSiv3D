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
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct Triangle
	{
		using position_type = Vec2;

		using value_type = position_type::value_type;

		Vec2 p0, p1, p2;

		Triangle() = default;

		constexpr Triangle(double x0, double y0, double x1, double y1, double x2, double y2) noexcept
			: p0(x0, y0)
			, p1(x1, y1)
			, p2(x2, y2) {}
	};
}
